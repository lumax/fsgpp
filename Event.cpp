/*
fsgEvent.c
Bastian Ruppert
03.12.2010
*/

namespace EuMax01
{

#include "fsgEvent.h"
#include "fsgButton.h"
  

  static void EvtTarget::fsgEventAddEvtTarget(_pTfsgLL z,_pTfsgEvtTarget t)
  {
    fsgLLAdd(z,(_pTfsgLL)t);
  }

/*! \brief process the  fsgEvtTarget  Event Handler 
 */
static void fsgEventProcessEvtTarget(SDL_Event * evt,_pTfsgEvtTarget tar);

void fsgEventProcessTargets(SDL_Event * pSDL_Event, _pTfsgLL t)
{
  _pTfsgEvtTarget pTmp = (_pTfsgEvtTarget)t->Next;
  while(pTmp)
    {
      fsgEventProcessEvtTarget(pSDL_Event,pTmp);
      pTmp = (_pTfsgEvtTarget)pTmp->TfsgLL.Next;
    }
}

int fsgEventPaintRequested(_pTfsgLL t)
{
  int ret = 0;
  _pTfsgEvtTarget pTmp = (_pTfsgEvtTarget)t->Next;
  while(pTmp)
    {
      if(pTmp->bPaintRequest==1){
	ret = 1;
	pTmp->bPaintRequest=0;
      }
      pTmp = (_pTfsgEvtTarget)pTmp->TfsgLL.Next;
    }
  return ret;
}

void fsgEventProcessEvtTarget(SDL_Event * evt,_pTfsgEvtTarget tar)
{
  int tmpx,tmpy;
  SDL_Rect pRect;

  if(evt->type==SDL_MOUSEMOTION)
    {
      SDL_GetMouseState(&tmpx,&tmpy);
      pRect.x = tar->pPosDimRect->x;
      pRect.y = tar->pPosDimRect->y;
      pRect.w = tar->pPosDimRect->w;
      pRect.h = tar->pPosDimRect->h;
      
      if( (tmpx>=pRect.x)&&					\
	  (tmpx<pRect.x+pRect.w) &&					\
	  (tmpy>=pRect.y)&&(tmpy<pRect.y+pRect.h) )// Mouse is over !
	{
	  if(!tar->bSelected){//Selected in not set
	    tar->bSelected = 1;                    //set bSelected bit
	    if(tar->PrivateSelectable){//there is a funktion to call
	      (*tar->PrivateSelectable)((void*)tar,1);
	    }
	    if(tar->fnkMouseOver!=0){//there is a funktion to call
	      (*tar->fnkMouseOver)(evt,tar->pTSource);//execFnk 
	      return;
	    }
	  }
	}
      else//Mouse is not over
	{
	  if(tar->bSelected)// Selected is set
	    {
	      tar->bSelected = 0;          //unset Selected
	      if(tar->PrivateSelectable){//there is a funktion to call
		(*tar->PrivateSelectable)((void*)tar,0);
	      }
	    }
	}    
    }
  
  if(evt->type==SDL_MOUSEBUTTONDOWN)
    {
      if(evt->button.button==SDL_BUTTON_LEFT)
	{
	  SDL_GetMouseState(&tmpx,&tmpy);
	  pRect.x = tar->pPosDimRect->x;
	  pRect.y = tar->pPosDimRect->y;
	  pRect.w = tar->pPosDimRect->w;
	  pRect.h = tar->pPosDimRect->h;
	  if( (tmpx>=pRect.x)&&					\
	      (tmpx<pRect.x+pRect.w) &&					\
	      (tmpy>=pRect.y)&&(tmpy<pRect.y+pRect.h) )// Mouse is over !
	    {
	      if(tar->fnkLeftMouseButtonDown&&tar->bSelected)
		{
		  (*tar->fnkLeftMouseButtonDown)(evt,tar->pTSource);
		}
	      return;
	    }
	}
    }
  
  if(evt->type==SDL_MOUSEBUTTONUP)
    {
      if(evt->button.button==SDL_BUTTON_LEFT)
	{
	  if(tar->bSelected)
	    {
	      if(tar->fnkLeftMouseButtonUp)//&&pBtn->bSelected)
		{
		  (*tar->fnkLeftMouseButtonUp)(evt,tar->pTSource);
		}
	      return;
	    }
	}
    }
}
}//namespace
