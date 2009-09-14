/*
fsgEvent.c
Bastian Ruppert
08.05.2009
*/

#include "fsgEvent.h"
#include "fsgButton.h"






_pTfsgEvtTargetContainer fsgEventEvtTargetContainerConstructor(int MaxEvtTargets)
{
  int i;
  _pTfsgEvtTargetContainer con=(_pTfsgEvtTargetContainer)malloc(sizeof(_TfsgEvtTargetContainer)); 
  if(con == NULL)
    return NULL;
  
  if(MaxEvtTargets < 0)
    return NULL;

  con->apEvtTargets = (_pTfsgEvtTarget*)malloc(sizeof(_TfsgEvtTarget)*MaxEvtTargets);
  if(con->apEvtTargets==NULL) 
   goto ContainerReady; 
  
  for(i=0;i<MaxEvtTargets;i++)
    {
      con->apEvtTargets[i]=0;
    }
 
  con->CounterTargets=0;
  con->MaxTargets = MaxEvtTargets;
  return con;           //alles gut

 ContainerReady:
  free(con);

  return NULL;  
}


int fsgEventAddEvtTarget(_pTfsgEvtTargetContainer z,_pTfsgEvtTarget t)
{
  int i;
  if(z->CounterTargets<z->MaxTargets)
    {
      for(i=0;i<z->MaxTargets;i++)
	{  
	  if(z->apEvtTargets[i]==0)
	    {
	      z->apEvtTargets[i]=t;
	      //btn->pvEventContainer = (void *)tar; //dem Button den EventContainer bekanntgeben
	      z->CounterTargets++;
	      return 0;
	    }
	}
      return -2;
    }
 return -1; 
}

/*! \brief process the  fsgEvtTarget  Event Handler 
 */
static void fsgEventProcessEvtTarget(SDL_Event * evt,_pTfsgEvtTarget tar);

void fsgEventProcessTargets(SDL_Event * pSDL_Event, _pTfsgEvtTargetContainer t)
{
  int i;
  for(i=0;i<t->CounterTargets;i++){     //alle EventTargets durchlaufen
    fsgEventProcessEvtTarget(pSDL_Event,t->apEvtTargets[i]);
  }
}

int fsgEventPaintRequested(_pTfsgEvtTargetContainer t)
{
  int ret = 0;
  int i;
  for(i=0;i<t->CounterTargets;i++){     //alle EventTargets durchlaufen
    if(t->apEvtTargets[i]->bPaintRequest==1){
      ret = 1;
      t->apEvtTargets[i]->bPaintRequest=0;
    }
  }
  return ret;
}

/* switch(t->apEvtTargets[i]->type)
      {
      case FSG_BUTTON:{
	fsgButtonProcess(pSDL_Event,t->apEvtTargets[i]);
	break;
      }
      case FSG_LABEL:{
	break;
      }
      default:{
	break;
      }
    }
*/
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
	    if(tar->Private_fnkSelectable){//there is a funktion to call
	      (*tar->Private_fnkSelectable)((void*)tar,1);
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
	      if(tar->Private_fnkSelectable){//there is a funktion to call
		(*tar->Private_fnkSelectable)((void*)tar,0);
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
