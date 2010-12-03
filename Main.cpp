/*
Bastian Ruppert
*/

namespace EuMax01
{

#include <SDL/SDL_ttf.h>
#include <SDL/SDL.h>
#include "LL.h"
  //#include "fsgGlobals.h"
  //#include "fsgEvent.h"

//#include "fsgButton.h"
//#include "fsgLabel.h"
//#include "fsgCheckBox.h"
//#include "fsgScreen.h"
//#include "fsgScreen.h"
//#include "fsgMain.h"

  static GUI * pGUI;

  GUI::GUI(GUI_Properties * p_properties		\
	   ,void (*fnkSecondaryEvtHandling)		\
	   (SDL_Event * theEvent))
  {
    //if(!fsgGlobalGetDefaultFont()){
      
      pGUI->fnkSecondaryEvtHandler = fnkSecondaryEvtHandling;
      
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
      
      pGUI->pMainSurface = SDL_SetVideoMode(pProps->width,	\
					    pProps->height,	\
					    pProps->bpp,	\
					    pProps->flags);
      if(!theGUI.pMainSurface)
	return -1;
      //if(fsgGlobalsInit()){
      //goto MainSurfaceReady;
      //}
      return 0;
      
      //MainSurfaceReady:
      //SDL_FreeSurface(theGUI.pMainSurface);
      //}
      //return -1;
  }  

  void GUI::setActiveScreen(Screen * s)//TODO static function
  {
    if(pGUI->pActiveScreen)
      {
	if(pGUI->pActiveScreen->OnDeactivate)
	  {
	    pGUI->pActiveScreen->OnDeactivate();
	}
      }
    
    EvtTarget pTmpEvtTarget = (EvtTarget*)s->EvtTargets.Next;
    while(pTmpEvtTarget)
      {     //alle EventTargets durchlaufen und Selected = false setzen
	pTmpEvtTarget->bSelected = 0;
	pTmpEvtTarget = (EvtTarget*)pTmpEvtTarget->LL.Next;
      }
    
    pGUI->pActiveScreen = s;
    if(pGUI->pActiveScreen->OnActivate)
      {
	pGUI->pActiveScreen->OnActivate();
      }   
  }

  LL* GUI::getActiveEvtTargets(void)
  {
    if(pGUI->pActiveScreen){
      return pGUI->pActiveScreen->EvtTargets;
    }else{
      return 0;
    }
  }

  void GUI::activateScreen(Screen * s)
  {
    this->setActiveScreen(s); //die EventListener umschalten
    s->screenShow(pGUI->pMainSurface);
    SDL_Flip(pGUI->pMainSurface);
  }


  int GUI::eventLoop(void)
  {
    SDL_Event theEvent;
    for(;;){
      if(SDL_WaitEvent(&theEvent)==0){
	//printf("error while waiting for event\n");
	return -1; 
      }
      if(pGUI->pActiveScreen){
	if(pGUI->pActiveScreen->EvtTargets.Next){                            //EvtTargets Ausführen
	  fsgEventProcessTargets(&theEvent,&pGUI->pActiveScreen->EvtTargets);
	}
	if(fsgEventPaintRequested(&pGUI->pActiveScreen->EvtTargets)){     //alle EventTargets auf bPaintRequest untersuchen
	  pGUI->pActiveScreen(pGUI->pMainSurface);
	  SDL_Flip(pGUI->pMainSurface);                                   //show buffer
	  /*if(theGUI.pSurface==theGUI.pDoubleBuf0)                      //point to next DoubleBuf
	    theGUI.pSurface = theGUI.pDoubleBuf1;
	  else
	  theGUI.pSurface = theGUI.pDoubleBuf0;*/
	}
      }
      /*if(pGUI->fnkSecondaryEvtHandler){ 
	(*theGUI.fnkSecondaryEvtHandler)(&theEvent);                 //zweite EventhandlerFunktion ausfuehren
	}*/
      if(theEvent.type==SDL_QUIT){
	return 0;
      }
    }
  }
  

}//end namespace
