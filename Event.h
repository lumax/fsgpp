/*
Event.h
Bastian Ruppert
03.12.2010

*/

#ifndef __FSGEVENT_H__
#define __FSGEVENT_H__
#include <SDL/SDL.h>
#include "LL.h"
namespace EuMax01
{

class EvtTarget:public LL
{

 public:
  
  bool bHide;
  bool bMouseOver;
  bool bSelectedByMouseDown;
  bool bPaintRequest;
  void * pTSource;
  SDL_Rect PosDimRect;

  EvtTarget();
  ~EvtTarget();
  void addEvtTarget(EvtTarget * t);
  void removeSingleEvtTarget(EvtTarget * t);
  static void processTargets(SDL_Event * pSDL_Event,EvtTarget * t);
  static int paintRequested(EvtTarget * t);
  int (*PrivateShow)(void * pB,SDL_Surface * pSurface);
  void setMouseOverEvtHandler(void (*pfnk)(void * src,SDL_Event *));
  void setLMButtonDownEvtHandler(void (*pfnk)(void * src,SDL_Event *));
  void setLMButtonUpEvtHandler(void (*pfnk)(void * src,SDL_Event *));
  void setLMButtonUpEvtHandler(void (*pfnk)(void * src,SDL_Event *),void * source);
  void setKeyboardDownEvtHandler(void (*pfnk)(void * src,SDL_Event *));
  void setKeyboardUpEvtHandler(void (*pfnk)(void * src,SDL_Event *));
  void hide(bool hide);
  void setPrivateMouseOver(void (*fnk)(void * b,bool selected));
 protected:
  void (*fnkMouseOverEvt)(void * source);
  void (*fnkMouseNotOverEvt)(void * source);
  void (*PrivateMouseOver)(void * b,bool selected);
  void (*fnkKeyboardUp)(void * src,SDL_Event * theEvent);
  void (*fnkKeyboardDown)(void * src,SDL_Event * theEvent);
  void (*fnkMouseMotion)(void * src,SDL_Event * theEvent);
  void (*fnkMouseOver)(void * src,SDL_Event * theEvent);
  void (*fnkLeftMouseButtonDown)(void * src,SDL_Event * theEvent);
  void (*fnkLeftMouseButtonUp)(void * src,SDL_Event * theEvent);

 private:
  void processEvtTarget(SDL_Event * evt);


};


}
#endif /* __FSGEVENT_H__*/
