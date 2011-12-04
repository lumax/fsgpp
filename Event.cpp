/*
fsgEvent.c
Bastian Ruppert
03.12.2010
*/


#include "Event.h"

namespace EuMax01
{
 
  EvtTarget::EvtTarget():LL()
  {
    PrivateShow = NULL;
    bHide = false;
    bMouseOver = false;
    bPaintRequest = false;

    pTSource = NULL;
    PosDimRect.x = 0;
    PosDimRect.y = 0;
    PosDimRect.w = 0;
    PosDimRect.h = 0;
    fnkMouseOverEvt=NULL;
    fnkMouseNotOverEvt=NULL;
    PrivateMouseOver=NULL;
    
    fnkKeyboardUp=NULL;
    fnkKeyboardDown=NULL;
    fnkMouseMotion=0;
    fnkMouseOver=NULL;
    fnkLeftMouseButtonDown=NULL;
    fnkLeftMouseButtonUp=NULL;
    
  }

  EvtTarget::~EvtTarget()
  {
    //EuMax01::LL::~LL();
  }

  void EvtTarget::hide(bool hide)
  {
    if(hide)
      this->bHide = true;
    else
      this->bHide = false;
  }

  void EvtTarget::setPrivateMouseOver(void (*fnk)(void * b,bool selected))
  {
    this->PrivateMouseOver = fnk;
  }

  void EvtTarget::setMouseOverEvtHandler(void (*pfnkEvtHandler)(void * src,SDL_Event *))
  {
    this->fnkMouseOver = pfnkEvtHandler;
  }

  void EvtTarget::setLMButtonDownEvtHandler(void (*pfnkEvtHandler)(void * src,SDL_Event *))
  {
    this->fnkLeftMouseButtonDown = pfnkEvtHandler;
  }

  void EvtTarget::setLMButtonUpEvtHandler(void (*pfnkEvtHandler)(void * src,SDL_Event *))
  {
    this->fnkLeftMouseButtonUp = pfnkEvtHandler;
  }

  void EvtTarget::setKeyboardDownEvtHandler(void (*pfnk)(void * src,SDL_Event *))
  {
    this->fnkKeyboardDown = pfnk;
  }

  void EvtTarget::setKeyboardUpEvtHandler(void (*pfnk)(void * src,SDL_Event *))
  {
    this->fnkKeyboardUp = pfnk;
  }

  void EvtTarget::addEvtTarget(EvtTarget * t)
  {
    this->addLL(t);
  }

  /*  void EvtTarget::removeSingleEvtTarget(EvtTarget * t)
  {
    this->removeSingleLL(t);
    }*/

  void EvtTarget::processTargets(SDL_Event * pSDL_Event,EvtTarget * t)
{
  EvtTarget* pTmp = (EvtTarget*)t->Next;
  while(pTmp)
    {
      pTmp->processEvtTarget(pSDL_Event);
      pTmp = (EvtTarget*)pTmp->Next;
    }
}

int EvtTarget::paintRequested(EvtTarget * t)
{
  int ret = 0;
  EvtTarget * pTmp = (EvtTarget*)t->Next;
  while(pTmp)
    {
      if(pTmp->bPaintRequest==1){
	ret = 1;
	pTmp->bPaintRequest=0;
      }
      pTmp = (EvtTarget*)pTmp->Next;
    }
  return ret;
}

  void EvtTarget::processEvtTarget(SDL_Event * evt)
  {
    int tmpx,tmpy;
    SDL_Rect pRect;
    
    tmpx = evt->motion.x;
    tmpy = evt->motion.y;
    pRect.x = this->PosDimRect.x;
    pRect.y = this->PosDimRect.y;
    pRect.w = this->PosDimRect.w;
    pRect.h = this->PosDimRect.h;
    
    if(evt->type==SDL_MOUSEMOTION)
      {
	if( (tmpx>=pRect.x)&&						\
	    (tmpx<pRect.x+pRect.w) &&					\
	    (tmpy>=pRect.y)&&(tmpy<pRect.y+pRect.h) )// Mouse is over !
	  {
	    if(this->fnkMouseMotion!=0){
	      (*this->fnkMouseMotion)(this->pTSource,evt);//execFnk
	    }
	    if(!this->bMouseOver){
	      this->bMouseOver = true;                    //set bSelected bit
	      if(this->PrivateMouseOver){//there is a funktion to call
		(*this->PrivateMouseOver)((void*)this,true);
	      }
	      
	      if(this->fnkMouseOver!=0){//there is a funktion to call
		(*this->fnkMouseOver)(this->pTSource,evt);//execFnk 
		return;
	      }
	    }
	  }
	else//Mouse is not over
	  {
	    if(this->bMouseOver)// Selected is set
	      {
		this->bMouseOver = false;          //unset Selected
		if(this->PrivateMouseOver){//there is a funktion to call
		  (*this->PrivateMouseOver)((void*)this,false);
		}
	      }
	  }    
      }
    
    if(evt->type==SDL_MOUSEBUTTONDOWN)
      {
	if(evt->button.button==SDL_BUTTON_LEFT)
	  {
	    if( (tmpx>=pRect.x)&&					\
		(tmpx<pRect.x+pRect.w) &&				\
		(tmpy>=pRect.y)&&(tmpy<pRect.y+pRect.h) )// Mouse is over !
	      {
		if(this->fnkLeftMouseButtonDown/*&&this->bSelected*/)
		  {
		  (*this->fnkLeftMouseButtonDown)(this->pTSource,evt);
		  }
		return;
	      }
	  }
      }
    
    if(evt->type==SDL_MOUSEBUTTONUP)
      {
      if(evt->button.button==SDL_BUTTON_LEFT)
	{
	  
#ifdef TARGET_ARM
	  if( (tmpx>=pRect.x)&&						\
	      (tmpx<pRect.x+pRect.w) &&					\
	      (tmpy>=pRect.y)&&(tmpy<pRect.y+pRect.h) )// Mouse is over !
	    {  
	      if(this->fnkLeftMouseButtonUp)//&&pBtn->bSelected)
		{
		  (*this->fnkLeftMouseButtonUp)(this->pTSource,evt);
		}
	    }
	  if(this->bMouseOver)
	    {
	      this->bMouseOver=false;
	      if(this->PrivateMouseOver){//there is a fnk to call
		(*this->PrivateMouseOver)((void*)this,false);
	      }
	    }
#else
	  if(this->bMouseOver)
	    {
	      if(this->fnkLeftMouseButtonUp)//&&pBtn->bSelected)
		{
		  (*this->fnkLeftMouseButtonUp)(this->pTSource,evt);
		}
	    }
#endif
	}
      }

    if(evt->type == SDL_KEYDOWN)
      {
	if(this->fnkKeyboardDown)
	  {
	    (*this->fnkKeyboardDown)(this->pTSource,evt);//execFnk
	    return;
	  }
      }
    else if(evt->type == SDL_KEYUP)
      {
	if(this->fnkKeyboardUp)
	  {
	    (*this->fnkKeyboardUp)(this->pTSource,evt);//execFnk
	    return;
	  }
      }
  }
}//namespace
