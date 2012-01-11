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
    isVisible = false;
    bMouseOver = false;
    bSelectedByMouseDown = false;
    bPaintRequest = false;
    EvtTargetID=0;

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
      this->isVisible = false;
    else
      this->isVisible = true;
  }

  int EvtTarget::show(SDL_Surface * pSurface)
  {
    return 0;
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

  void EvtTarget::setLMButtonUpEvtHandler(void (*pfnkEvtHandler)(void * src,SDL_Event *), \
					  void * source)
  {
    this->setLMButtonUpEvtHandler(pfnkEvtHandler);
    this->pTSource = source;
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

  bool EvtTarget::processTargets(SDL_Event * pSDL_Event,EvtTarget * t)
  {
    EvtTarget* pTmp = (EvtTarget*)t->Next;
    bool paintRequest = false;
    while(pTmp)
      {
	if(pTmp->processEvtTarget(pSDL_Event))
	  paintRequest = true;
	pTmp = (EvtTarget*)pTmp->Next;
      }
    return paintRequest;
  }

bool EvtTarget::paintRequested(EvtTarget * t)
{
  bool ret = false;
  EvtTarget * pTmp = (EvtTarget*)t->Next;
  while(pTmp)
    {
      if(pTmp->bPaintRequest){
	ret = true;
	pTmp->bPaintRequest=false;
      }
      pTmp = (EvtTarget*)pTmp->Next;
    }
  return ret;
}

  void EvtTarget::repaint()
  {
    this->bPaintRequest = true;
  }

  bool EvtTarget::processEvtTarget(SDL_Event * evt)
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
		(*this->PrivateMouseOver)(this->pTSource,true);
	      }
	      
	      if(this->fnkMouseOver!=0){//there is a funktion to call
		(*this->fnkMouseOver)(this->pTSource,evt);//execFnk 
		goto function_out;
	      }
	    }
	  }
	else//Mouse is not over
	  {
	    if(this->bMouseOver)// Selected is set
	      {
		this->bMouseOver = false;          //unset Selected
		if(this->PrivateMouseOver){//there is a funktion to call
		  (*this->PrivateMouseOver)(this->pTSource,false);
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
		this->bSelectedByMouseDown = true;
		this->bPaintRequest = true;
		if(this->fnkLeftMouseButtonDown/*&&this->bSelected*/)
		  {
		  (*this->fnkLeftMouseButtonDown)(this->pTSource,evt);
		  }
		goto function_out;
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
		(*this->PrivateMouseOver)(this->pTSource,false);
	      }
	    }
#else
	  if( (tmpx>=pRect.x)&&						\
	      (tmpx<pRect.x+pRect.w) &&					\
	      (tmpy>=pRect.y)&&(tmpy<pRect.y+pRect.h) )// Mouse is over !
	    {
	      if(this->fnkLeftMouseButtonUp)//&&pBtn->bSelected)
		{
		  (*this->fnkLeftMouseButtonUp)(this->pTSource,evt);
		}
	    }
	  if(this->bSelectedByMouseDown)
	    {
	      this->bSelectedByMouseDown = false;
	      this->bPaintRequest = true;
	    }
#endif
	}
      }

    if(evt->type == SDL_KEYDOWN)
      {
	if(this->fnkKeyboardDown)
	  {
	    (*this->fnkKeyboardDown)(this->pTSource,evt);//execFnk
	    goto function_out;
	  }
      }
    else if(evt->type == SDL_KEYUP)
      {
	if(this->fnkKeyboardUp)
	  {
	    (*this->fnkKeyboardUp)(this->pTSource,evt);//execFnk
	    goto function_out;
	  }
      }
  function_out:
    return this->bPaintRequest;
  }
}//namespace
