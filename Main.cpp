/*
Bastian Ruppert
*/

#include <sys/time.h>


#include <SDL/SDL_ttf.h>
#include <SDL/SDL.h>
#include <signal.h>
#ifdef TARGET_ARM
#include <tslib.h>
#endif
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
    return GUI::getInstance(pProps,fnkSecondaryEvtHandling,false);
  }

  GUI* GUI::getInstance(GUI_Properties * pProps,void (*fnkSecondaryEvtHandling)(SDL_Event * theEvent),bool useCurWandH)
  {
    const SDL_VideoInfo *info;
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
	printf("Couldn't initialize TTF_Init\n");
	return NULL;
      }

      if(useCurWandH)
	{
	  info = SDL_GetVideoInfo();
	  if(info)
	    {
	      printf("SDL_SetVideoMode Width:%i Height:%i\n",info->current_w,info->current_h);
	      pGUI->pMainSurface = SDL_SetVideoMode(info->current_w ,	\
						    info->current_h,	\
						    pProps->bpp,	\
						    pProps->flags);
	    }
	  else
	    {
	      printf("SDL_SetVideoMode GetVideoInfo failed: Width:%i Height:%i\n",pProps->width,pProps->height);
	      pGUI->pMainSurface = SDL_SetVideoMode(pProps->width,	\
						    pProps->height,	\
						    pProps->bpp,	\
						    pProps->flags);
	    }
	}
      else
	{
	  printf("SDL_SetVideoMode Width:%i Height:%i\n",pProps->width,pProps->height);
	  pGUI->pMainSurface = SDL_SetVideoMode(pProps->width,	\
						pProps->height,	\
						pProps->bpp,	\
						pProps->flags);
	}

      if(!pGUI->pMainSurface)
	return NULL;

      Globals* pGlobals = Globals::getInstance();
      if(!pGlobals)
	{
	  SDL_FreeSurface(pGUI->pMainSurface);
	  printf("Globals::getInstance failed\n");
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
      {     //alle EventTargets durchlaufen und MouseOver = false setzen
	pTmpEvtTarget->bMouseOver = false;
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
    s->showScreen(pGUI->pMainSurface);
#ifndef FSGPP_SHOW_IMMEDIATELY
    SDL_Flip(pGUI->pMainSurface);
#endif
  }
  void GUI::pollReadEvent(PollSource * ps)
  {
#ifdef TARGET_ARM

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
	checkPaintRequests();
      }//end if
    else
      {
	return;
      }
      }//end for
    return;
    #endif
  }

  inline bool GUI::processEvent(SDL_Event * theEvent)
  {
    bool paintRequest = false;
    if(pGUI->pActiveScreen)
      {
	if(pGUI->pActiveScreen->EvtTargets.Next)
	  {                            //EvtTargets Ausführen
	    if(EvtTarget::processTargets(theEvent,&pGUI->pActiveScreen->EvtTargets))
	      paintRequest = true;
	  }
      }
    if(pGUI->fnkSecondaryEvtHandler)
      (*pGUI->fnkSecondaryEvtHandler)(theEvent);
    return paintRequest;
  }

  inline int GUI::checkPaintRequests()
  {
    if(EvtTarget::paintRequested(&pGUI->pActiveScreen->EvtTargets))
      {     //alle EventTargets auf bPaintRequest untersuchen
	pGUI->pActiveScreen->showScreen(pGUI->pMainSurface);
#ifndef FSGPP_SHOW_IMMEDIATELY
	SDL_Flip(pGUI->pMainSurface);                                   //show buffer
#endif
      }
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
    bool paintRequest = false;
    while(SDL_PollEvent(theEvent))
      {
	if(theEvent->type==SDL_QUIT)
	  {
	    pm_ts->stopPolling();
	  }
	if(processEvent(theEvent))
	  {
	    paintRequest = true;
	    checkPaintRequests();
	  }
      }
    if(!paintRequest)//für EventTargets, die nicht durch SDL getriggert werden
      checkPaintRequests();
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

  int GUI::addPollSource(PollSource * psrc,bool custom)
  {
    return pm_ts->addSource(psrc,custom);
  }
}//end namespace
