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
  

   class GUI:IPollListener
  {

  public:

    static GUI* getInstance(GUI_Properties * p_properties,void (*fnkSecondaryEvtHandling)(SDL_Event * theEvent));
    LL * getActiveEvtTargets(void);
    void setActiveScreen(Screen * s);
    void activateScreen(Screen * s);
    int eventLoop(void);
    void stopEventLoop();
    //void theTsPollReaderFnk(PollSource * ps);
    virtual void pollEvent(PollSource * s);
  private:
    static GUI * pGUI;
      GUI();
      ~GUI()
	{
	  //delete(pActiveScreen);
	  SDL_FreeSurface(pMainSurface);
	  delete(pr_ts);
	  delete(pm_ts);
	};
      int processEvent(SDL_Event * theEvent);
      Screen * pActiveScreen;
      void (*fnkSecondaryEvtHandler)(SDL_Event * theEvent);
      SDL_Surface * pMainSurface;
      SDL_Event theSDL_Event;

      struct tsdev *ts_dev;
      PollManager*  pm_ts;
      PollReader* pr_ts;
      
  };
  
 
#endif /* __MAIN_H__*/
}// end namespace 

