/*
Bastian Ruppert
*/

#include <SDL/SDL_ttf.h>
#include <SDL/SDL.h>
#include <tslib.h>
#include "LL.h"
  #include "Globals.h"
  #include "Event.h"

#include "Button.h"
//#include "fsgLabel.h"
#include "Poll.h"
#include "Screen.h"
  #include "Main.h"

#include <iostream>
#include <stdio.h>

namespace EuMax01
{
  GUI* GUI::pGUI = NULL;
  
  GUI::GUI()
  {
    pActiveScreen = 0;
    fnkSecondaryEvtHandler = 0;
    pMainSurface = 0;
  }

  GUI* GUI::getInstance(GUI_Properties * pProps,void (*fnkSecondaryEvtHandling)(SDL_Event * theEvent))
  {
    if(pGUI)
      return pGUI;

    pGUI = new GUI();
    pGUI->fnkSecondaryEvtHandler = fnkSecondaryEvtHandling;
      
      if(SDL_Init(SDL_INIT_VIDEO)==-1){
	return NULL;
      }
      else{
	atexit(SDL_Quit);
      }
      
      if(TTF_Init()==0){
	atexit(TTF_Quit);
      }
      else{
	return NULL;
      }
      
      pGUI->pMainSurface = SDL_SetVideoMode(pProps->width,	\
					    pProps->height,	\
					    pProps->bpp,	\
					    pProps->flags);
      if(!pGUI->pMainSurface)
	return NULL;

      Globals* pGlobals = Globals::getInstance();
      if(!pGlobals)
	{
	  SDL_FreeSurface(pGUI->pMainSurface);
	  return NULL;
	}

      return pGUI;
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
    
    EvtTarget *pTmpEvtTarget = (EvtTarget*)s->EvtTargets.Next;
    while(pTmpEvtTarget)
      {     //alle EventTargets durchlaufen und Selected = false setzen
	pTmpEvtTarget->bSelected = false;
	pTmpEvtTarget = (EvtTarget*)pTmpEvtTarget->Next;
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
      return &pGUI->pActiveScreen->EvtTargets;
    }else{
      return 0;
    }
  }

  void GUI::activateScreen(Screen * s)
  {
    this->setActiveScreen(s); //die EventListener umschalten
    s->show(pGUI->pMainSurface);
    SDL_Flip(pGUI->pMainSurface);
  }

  static void theTsPollReaderFnk(PollSource * ps);

  int GUI::initTsPolling()
  {
    //struct tsdev *ts_open(const char *name, int nonblock)
    this->ts_dev = ts_open(SDL_getenv("TSLIB_TSDEVICE"), 0);
    if ((ts_dev != 0) && (ts_config(ts_dev) >= 0)) 
      {
	if(!pr_ts.setReadSource(ts_fd(ts_dev),theTsPollReaderFnk))
	  return -2;
	pm_ts.addSource(ps_ts);
	return 0;
      }
    else
      {
	return -1;
      }
  }  

  static void theTsPollReaderFnk(PollSource * ps)
  {
    struct ts_sample sample;
    int button;
    
    while (ts_read(ts_dev, &sample, 1) > 0) {
      button = (sample.pressure > 0) ? 1 : 0;
      button <<= 2;	/* must report it as button 3 */
      //FB_vgamousecallback(button, 0, sample.x, sample.y);
      printf("FB_vgamousecallback\n");
      printf("button : %i, relative: %i, dx: %i, dy: %i\n",button,0,sample.x,sample.y);
    }
    return;
}

  int GUI::eventLoop(void)
  {
    SDL_Event theEvent;

    if(initTsPolling())
      {
	std::cout << "initTsPolling returned witch error"<<std::endl;
      }
    else
      {
	if(call_poll())
	  {
	    std::cout << "pollMAnager returned witch error"<<std::endl;
	  }
      }

    for(;;){
      if(SDL_WaitEvent(&theEvent)==0){
	//printf("error while waiting for event\n");
	return -1; 
      }
      if(pGUI->pActiveScreen){
	if(pGUI->pActiveScreen->EvtTargets.Next){                            //EvtTargets Ausführen
	  EvtTarget::processTargets(&theEvent,&pGUI->pActiveScreen->EvtTargets);
	}
	if(EvtTarget::paintRequested(&pGUI->pActiveScreen->EvtTargets)){     //alle EventTargets auf bPaintRequest untersuchen
	  pGUI->pActiveScreen->show(pGUI->pMainSurface);
	  SDL_Flip(pGUI->pMainSurface);                                   //show buffer
	  //if(theGUI.pSurface==theGUI.pDoubleBuf0)                      //point to next DoubleBuf
	  // theGUI.pSurface = theGUI.pDoubleBuf1;
	  //else
	  //theGUI.pSurface = theGUI.pDoubleBuf0;
	}
      }
      //if(pGUI->fnkSecondaryEvtHandler){ 
      //(*theGUI.fnkSecondaryEvtHandler)(&theEvent);                 //zweite EventhandlerFunktion ausfuehren
      //	}
      if(theEvent.type==SDL_QUIT){
	return 0;
      }
    }
  }
  

}//end namespace
