/*
Bastian Ruppert
*/

#include <sys/time.h>


#include <SDL/SDL_ttf.h>
#include <SDL/SDL.h>
#include <signal.h>
#include <tslib.h>
#include "LL.h"
#include "Globals.h"
#include "Event.h"
#include "Button.h"
#include "Poll.h"
#include "Screen.h"

#include "Main.h"

//#include <iostream>
//#include <stdio.h>
#include <stdio.h>

namespace EuMax01
{
  GUI* GUI::pGUI = NULL;
  
  GUI::GUI()
  {
    pActiveScreen = 0;
    fnkSecondaryEvtHandler = 0;
    pMainSurface = 0;
    pr_ts = new PollReader(this);
    pm_ts = new PollManager();
  }

  static void catch_sig(int i)
  {
    printf("signal!!!\n");//std::cout<< "signal!!!"<<std::endl;
     exit(2);
  }

  GUI* GUI::getInstance(GUI_Properties * pProps,void (*fnkSecondaryEvtHandling)(SDL_Event * theEvent))
  {
    if(pGUI)
      return pGUI;

    pGUI = new GUI();
    pGUI->fnkSecondaryEvtHandler = fnkSecondaryEvtHandling;
    
    signal (SIGINT, catch_sig);
    signal (SIGTERM, catch_sig);

      if(SDL_Init(SDL_INIT_VIDEO)==-1){
	printf("Couldn't initialize SDL: %s\n", SDL_GetError());
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

  void GUI::pollReadEvent(PollSource * ps)
  {
    struct ts_sample sample;
    static bool buttonup=true;
    //SDL_Event * tmpEvent = &this->theSDL_Event;
     for(int i = 0;i < 2; i++)
     {
    if (ts_read(ts_dev, &sample, 1) > 0) 
      {
	//printf("pressure : %i\n",sample.pressure);
	if(0==sample.pressure)
	  {
	    buttonup = true;
	    
	    this->theSDL_Event.button.type = SDL_MOUSEBUTTONUP;
	    this->theSDL_Event.button.state = SDL_RELEASED;
	    this->theSDL_Event.button.button = SDL_BUTTON_LEFT;
	    this->theSDL_Event.button.x = sample.x;
	    this->theSDL_Event.button.y = sample.y;
	  }
	else
	  {  
	    if(buttonup)
	      {
		this->theSDL_Event.button.type = SDL_MOUSEBUTTONDOWN;
		this->theSDL_Event.button.state = SDL_PRESSED;
		this->theSDL_Event.button.button = SDL_BUTTON_LEFT;
		this->theSDL_Event.button.x = sample.x;
		this->theSDL_Event.button.y = sample.y;
	      }
	    else
	      {
		this->theSDL_Event.motion.type = SDL_MOUSEMOTION;
		this->theSDL_Event.motion.state = SDL_PRESSED;
		this->theSDL_Event.motion.x = sample.x;
		this->theSDL_Event.motion.y = sample.y;
	      }	   
	    buttonup = false;	  
	  }
	//printf("pressure : %i, relative: %i, dx: %i, dy: %i\n",sample.pressure,0,sample.x,sample.y);
	processEvent(&this->theSDL_Event);
      }//end if
    else
      {
	return;
      }
      }//end for
    return;
  }

  int GUI::processEvent(SDL_Event * theEvent)
  {
    if(pGUI->pActiveScreen)
      {
	if(pGUI->pActiveScreen->EvtTargets.Next)
	  {                            //EvtTargets Ausführen
	    EvtTarget::processTargets(theEvent,&pGUI->pActiveScreen->EvtTargets);
	  }
	if(EvtTarget::paintRequested(&pGUI->pActiveScreen->EvtTargets))
	  {     //alle EventTargets auf bPaintRequest untersuchen
	    pGUI->pActiveScreen->show(pGUI->pMainSurface);
#ifndef FSGPP_SHOW_IMMEDIATELY
	    SDL_Flip(pGUI->pMainSurface);                                   //show buffer
#endif
	  }
      }
    if(pGUI->fnkSecondaryEvtHandler)
      (*pGUI->fnkSecondaryEvtHandler)(theEvent);
    return 0;
  }
#ifdef TARGET_ARM 
  void GUI::pollTimerExpired(long us)
  {
    printf("timerExp %li \n",us);//std::cout << "timerExp:" << us << std::endl;
  }
#else
  void GUI::pollTimerExpired(long us)
  {
    SDL_Event * theEvent = &this->theSDL_Event;
    while(SDL_PollEvent(theEvent))
      {
	if(theEvent->type==SDL_QUIT)
	  {
	    pm_ts->stopPolling();
	  }
	processEvent(theEvent);
      }
  }
#endif
    
  int GUI::eventLoop(void)
  {
#ifdef TARGET_ARM   
    //struct tsdev *ts_open(const char *name, int nonblock)
    this->ts_dev = ts_open(/*SDL_getenv("TSLIB_TSDEVICE")*/"/dev/input/event0", 0);
    if ((ts_dev != 0) && (ts_config(ts_dev) >= 0)) 
      {
	if(pr_ts->setReadSource(ts_fd(ts_dev)))
	  return -2;
	pm_ts->addSource(pr_ts);
      }
    else
      {
	return -1;
      }
    //PollTimer pt = PollTimer(500,this);
    //pm_ts->addTimer(&pt);

    if(pm_ts->call_poll())
      {
	printf("pollManager returned witch error\n");//std::cout << "pollManager returned witch error"<<std::endl;
      }
#else

    PollTimer pt = PollTimer(30,this);
    pm_ts->addTimer(&pt);
     if(pm_ts->call_poll())
      {
	printf("pollManager returned witch error\n");//std::cout << "pollManager returned witch error"<<std::endl;
      }  
    
    /*     SDL_Event * theEvent = &this->theSDL_Event;
    for(;;)
      {
	if(SDL_WaitEvent(theEvent)==0)
	  {
	    return -1; 
	  }
	processEvent(theEvent);
	
	if(theEvent->type==SDL_QUIT)
	  {
	    return 0;
	  }
	  }*/
#endif
    return 0;
  }
  
  
  void GUI::stopEventLoop()
  {
    if(pm_ts)
      {
	pm_ts->stopPolling();
      }
  }
  
  SDL_Surface *GUI:: getMainSurface()
  {
    if(pGUI)
      return pGUI->pMainSurface;
    else
      return 0;
  }
  
  void GUI::addPollTimer(PollTimer * p_pt)
  {
    pm_ts->addTimer(p_pt);
  }
  
  int GUI::addPollReader(PollReader * p_pr)
  {
    return pm_ts->addSource(p_pr);
  }
}//end namespace
