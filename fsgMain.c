/*
Bastian Ruppert
*/
#include <SDL/SDL_ttf.h>
#include <SDL/SDL.h>
#include "fsgLL.h"
#include "fsgGlobals.h"
#include "fsgEvent.h"

#include "fsgButton.h"
#include "fsgLabel.h"
#include "fsgCheckBox.h"
#include "fsgScreen.h"
#include "fsgScreen.h"
#include "fsgMain.h"

static _TfsgGUI theGUI = {.pActiveScreen = NULL,			\
		   .fnkSecondaryEvtHandler = NULL,		\
			  .pMainSurface = NULL,
			  //.pDoubleBuf0 =NULL,
			  //.pDoubleBuf1=NULL,
			  //.pSurface = NULL,
};

int fsgMainInit(_TfsgGUI_Properties * pProps,void (*fnkSecondaryEvtHandling)(SDL_Event * theEvent))
{
  if(!fsgGlobalGetDefaultFont()){
    
    theGUI.fnkSecondaryEvtHandler = fnkSecondaryEvtHandling;
    
    if(SDL_Init(SDL_INIT_VIDEO)==-1){
      return -1;
    }
    else{
      atexit(SDL_Quit);
    }
    
    if(TTF_Init()==0){
      atexit(TTF_Quit);
    }
    else{
      return -1;
    }
    
    theGUI.pMainSurface = SDL_SetVideoMode(pProps->width,	\
					   pProps->height,	\
					   pProps->bpp,		\
					   pProps->flags);
    if(!theGUI.pMainSurface)
      return -1;
    if(fsgGlobalsInit()){
      goto MainSurfaceReady;
    }
    return 0;
    
  MainSurfaceReady:
    SDL_FreeSurface(theGUI.pMainSurface);
  }
  return -1;
}

void fsgMainSetActiveScreen(_TfsgScreen * s)//TODO static function
{
  if(theGUI.pActiveScreen)
    {
      if(theGUI.pActiveScreen->OnDeactivate)
	{
	  theGUI.pActiveScreen->OnDeactivate();
	}
    }

  _pTfsgEvtTarget pTmpEvtTarget = (_pTfsgEvtTarget)s->EvtTargets.Next;
  while(pTmpEvtTarget)
    {     //alle EventTargets durchlaufen und Selected = false setzen
      pTmpEvtTarget->bSelected = 0;
      pTmpEvtTarget = (_pTfsgEvtTarget)pTmpEvtTarget->TfsgLL.Next;
    }

  theGUI.pActiveScreen = s;
  if(theGUI.pActiveScreen->OnActivate)
    {
      theGUI.pActiveScreen->OnActivate();
    }   
}

_pTfsgLL fsgMainGetActiveEvtTargets(void)
{
  if(theGUI.pActiveScreen){
    return &theGUI.pActiveScreen->EvtTargets;
  }else{
    return 0;
  }
}

void fsgMainActivateScreen(_TfsgScreen * s)
{
  fsgMainSetActiveScreen(s); //die EventListener umschalten
  fsgScreenShow(s,theGUI.pMainSurface);
  SDL_Flip(theGUI.pMainSurface);
}


int fsgMainEventLoop(void)
{
  SDL_Event theEvent;
  for(;;){
    if(SDL_WaitEvent(&theEvent)==0){
      //printf("error while waiting for event\n");
      return -1; 
    }
    if(theGUI.pActiveScreen){
      if(theGUI.pActiveScreen->EvtTargets.Next){                            //EvtTargets Ausführen
	fsgEventProcessTargets(&theEvent,&theGUI.pActiveScreen->EvtTargets);
     }
      if(fsgEventPaintRequested(&theGUI.pActiveScreen->EvtTargets)){     //alle EventTargets auf bPaintRequest untersuchen
	fsgScreenShow(theGUI.pActiveScreen,theGUI.pMainSurface);
	SDL_Flip(theGUI.pMainSurface);                                   //show buffer
	/*if(theGUI.pSurface==theGUI.pDoubleBuf0)                      //point to next DoubleBuf
	  theGUI.pSurface = theGUI.pDoubleBuf1;
	  else
	  theGUI.pSurface = theGUI.pDoubleBuf0;*/
      }
    }
    if(theGUI.fnkSecondaryEvtHandler){ 
      (*theGUI.fnkSecondaryEvtHandler)(&theEvent);                 //zweite EventhandlerFunktion ausfuehren
    }
    if(theEvent.type==SDL_QUIT){
      return 0;
    }
  }
}



