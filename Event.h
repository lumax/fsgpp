/*
Event.h
Bastian Ruppert
03.12.2010

*/
namespace EuMax01
{

#ifndef __FSGEVENT_H__
#define __FSGEVENT_H__
#include <SDL/SDL.h>
#include "LL.h"

class EvtTarget
{

 public:
  static void addEvtTarget(LL * z,EvtTarget * t);
  static void processTargets(SDL_Event * pSDL_Event,LL * t);
  int paintRequested(LL * t);

 private:
  LL theLL;
  Uint8 bHide;
  Uint8 bSelected;
  Uint8 bPaintRequest;
  Uint8 unused0;
  void * pTSource;
  SDL_Rect * pPosDimRect;
  int (*PrivateShow)(void * pB,SDL_Surface * pSurface);
  void (*PrivateSelectable)(void * b,int boolean);
  void (*fnkKeyboardUp)(SDL_Event * theEvent,void * source);
  void (*fnkMouseOver)(SDL_Event * theEvent,void * source);
  void (*fnkLeftMouseButtonDown)(SDL_Event * theEvent,void * source);
  void (*fnkLeftMouseButtonUp)(SDL_Event * theEvent,void * source);
  void (*fnkSelect)(void * source);
  void (*fnkUnSelect)(void * source);
}

#endif /* __FSGEVENT_H__*/
}
