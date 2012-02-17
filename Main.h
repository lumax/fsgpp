/*
Main.h
Bastian Ruppert
*/

namespace EuMax01
{

#ifndef __MAINGUI_H__
#define __MAINGUI_H__
  
   class GUI_Properties
  {
  public:
    int width;
    int height;
    int bpp;//If bpp is 0, it is treated as the current display bits per pixel.
    Uint32 flags;
  };
  

   class GUI:IPollReadListener,IPollTimerListener
  {

  public:

    static GUI* getInstance(GUI_Properties * p_properties,void (*fnkSecondaryEvtHandling)(SDL_Event * theEvent),bool useCurWandH);
    static GUI* getInstance(GUI_Properties * p_properties,void (*fnkSecondaryEvtHandling)(SDL_Event * theEvent));
    LL * getActiveEvtTargets(void);
    void activateScreen(Screen * s);
    int eventLoop(void);
    void stopEventLoop();
    SDL_Surface * getMainSurface();
    //void theTsPollReaderFnk(PollSource * ps);
    virtual void pollReadEvent(PollSource * s);
    virtual void pollTimerExpired(long us);
    void addPollTimer(PollTimer * p_pt);
    int addPollReader(PollReader * p_pr);
    int addPollSource(PollSource * psrc,bool custom);
  private:
    void setActiveScreen(Screen * s);
    static GUI * pGUI;
      GUI();
      ~GUI()
	{
	  //delete(pActiveScreen);
	  SDL_FreeSurface(pMainSurface);
	  delete(pr_ts);
	  delete(pm_ts);
	};
      /* ! brief Lässt das Event auf alle Targets des ActiveScreen wirken
       * returns paintRequest, ja oder nein
       */
      inline bool processEvent(SDL_Event * theEvent);
      inline int checkPaintRequests();
      Screen * pActiveScreen;
      void (*fnkSecondaryEvtHandler)(SDL_Event * theEvent);
      SDL_Surface * pMainSurface;
      SDL_Event theSDL_Event;
#ifdef TARGET_ARM
      struct tsdev *ts_dev;
#endif
      PollManager*  pm_ts;
      PollReader* pr_ts;
      
  };
  
 
#endif /* __MAIN_H__*/
}// end namespace 

