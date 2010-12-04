/*
fsgEvent.c
Bastian Ruppert
03.12.2010
*/


#include "Event.h"
  //#include "fsgButton.h"
 namespace EuMax01
{
 
  EvtTarget::EvtTarget():LL()
  {
    PrivateShow = NULL;
    bHide = false;
    bSelected = false;
    bPaintRequest = false;

    pTSource = NULL;
    pPosDimRect = NULL;
    fnkSelect=NULL;
    fnkUnSelect=NULL;
    PrivateSelectable=NULL;
    
    fnkKeyboardUp=NULL;
    fnkMouseOver=NULL;
    fnkLeftMouseButtonDown=NULL;
    fnkLeftMouseButtonUp=NULL;
    
  }

  void EvtTarget::addEvtTarget(EvtTarget * t)
  {
    this->addLL(t);
  }



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

  if(evt->type==SDL_MOUSEMOTION)
    {
      SDL_GetMouseState(&tmpx,&tmpy);
      pRect.x = this->pPosDimRect->x;
      pRect.y = this->pPosDimRect->y;
      pRect.w = this->pPosDimRect->w;
      pRect.h = this->pPosDimRect->h;
      
      if( (tmpx>=pRect.x)&&					\
	  (tmpx<pRect.x+pRect.w) &&					\
	  (tmpy>=pRect.y)&&(tmpy<pRect.y+pRect.h) )// Mouse is over !
	{
	  if(!this->bSelected){//Selected in not set
	    this->bSelected = 1;                    //set bSelected bit
	    if(this->PrivateSelectable){//there is a funktion to call
	      (*this->PrivateSelectable)((void*)this,1);
	    }
	    if(this->fnkMouseOver!=0){//there is a funktion to call
	      (*this->fnkMouseOver)(evt,this->pTSource);//execFnk 
	      return;
	    }
	  }
	}
      else//Mouse is not over
	{
	  if(this->bSelected)// Selected is set
	    {
	      this->bSelected = 0;          //unset Selected
	      if(this->PrivateSelectable){//there is a funktion to call
		(*this->PrivateSelectable)((void*)this,0);
	      }
	    }
	}    
    }
  
  if(evt->type==SDL_MOUSEBUTTONDOWN)
    {
      if(evt->button.button==SDL_BUTTON_LEFT)
	{
	  SDL_GetMouseState(&tmpx,&tmpy);
	  pRect.x = this->pPosDimRect->x;
	  pRect.y = this->pPosDimRect->y;
	  pRect.w = this->pPosDimRect->w;
	  pRect.h = this->pPosDimRect->h;
	  if( (tmpx>=pRect.x)&&					\
	      (tmpx<pRect.x+pRect.w) &&					\
	      (tmpy>=pRect.y)&&(tmpy<pRect.y+pRect.h) )// Mouse is over !
	    {
	      if(this->fnkLeftMouseButtonDown&&this->bSelected)
		{
		  (*this->fnkLeftMouseButtonDown)(evt,this->pTSource);
		}
	      return;
	    }
	}
    }
  
  if(evt->type==SDL_MOUSEBUTTONUP)
    {
      if(evt->button.button==SDL_BUTTON_LEFT)
	{
	  if(this->bSelected)
	    {
	      if(this->fnkLeftMouseButtonUp)//&&pBtn->bSelected)
		{
		  (*this->fnkLeftMouseButtonUp)(evt,this->pTSource);
		}
	      return;
	    }
	}
    }
}
}//namespace