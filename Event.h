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
  EvtTarget();
  void addEvtTarget(EvtTarget * t);
  static void processTargets(SDL_Event * pSDL_Event,EvtTarget * t);
  static int paintRequested(EvtTarget * t);
  int (*PrivateShow)(void * pB,SDL_Surface * pSurface);
  bool bHide;
  bool bSelected;
  bool bPaintRequest;

  void * pTSource;
  SDL_Rect * pPosDimRect;
 protected:
  void (*fnkSelect)(void * source);
  void (*fnkUnSelect)(void * source);
  void (*PrivateSelectable)(void * b,bool selected);
 private:
  void processEvtTarget(SDL_Event * evt);
  void (*fnkKeyboardUp)(SDL_Event * theEvent,void * source);
  void (*fnkMouseOver)(SDL_Event * theEvent,void * source);
  void (*fnkLeftMouseButtonDown)(SDL_Event * theEvent,void * source);
  void (*fnkLeftMouseButtonUp)(SDL_Event * theEvent,void * source);

};


}
#endif /* __FSGEVENT_H__*/
