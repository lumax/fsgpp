/*
Main.h
Bastian Ruppert
*/

namespace EuMax01
{

#ifndef __MAIN_H__
#define __MAIN_H__

  public class GUI
  {

  public:
    GUI (GUI_Properties * p_properties			\
	 ,void (*fnkSecondaryEvtHandling)		\
	 (SDL_Event * theEvent));
    LL * getActiveEvtTargets(void);
    void setActiveScreen(Screen * s);
    void activateScreen(_TfsgScreen * s);
    int eventLoop(void);
    
  private:
    Screen * pActiveScreen;
    void (*fnkSecondaryEvtHandler)(SDL_Event * theEvent);
    SDL_Surface * pMainSurface;
  }

  public class GUI_Properties
  {
  public:
    int width;
    int height;
    int bpp;//If bpp is 0, it is treated as the current display bits per pixel.
    Uint32 flags;
  }

#endif /* __MAIN_H__*/
}// end namespace 

