/*
fsgEvent.h
Bastian Ruppert
08.05.2009

*/

#ifndef __FSGEVENT_H__
#define __FSGEVENT_H__
#include <SDL/SDL.h>
#include "fsgTypes.h"

typedef struct
{
  Uint8 type;
  Uint8 bSelected;
  Uint8 bPaintRequest;
  Uint8 unused0;
  void * pTSource;
  SDL_Rect * pPosDimRect;
  void (*Private_fnkSelectable)(void * b,int bool);
  void (*fnkKeyboardUp)(SDL_Event * theEvent,void * source);
  void (*fnkMouseOver)(SDL_Event * theEvent,void * source);
  void (*fnkLeftMouseButtonDown)(SDL_Event * theEvent,void * source);
  void (*fnkLeftMouseButtonUp)(SDL_Event * theEvent,void * source);
  void (*fnkSelect)(void * source);
  void (*fnkUnSelect)(void * source);
}_TfsgEvtTarget,*_pTfsgEvtTarget;

typedef struct
{
  _pTfsgEvtTarget * apEvtTargets;
  int MaxTargets;
  int CounterTargets;
}_TfsgEvtTargetContainer,*_pTfsgEvtTargetContainer;

extern int fsgEventAddEvtTarget(_pTfsgEvtTargetContainer z,_pTfsgEvtTarget t);

extern _pTfsgEvtTargetContainer fsgEventEvtTargetContainerConstructor(int MaxEvtTargets);

extern void fsgEventProcessTargets(SDL_Event * pSDL_Event, _pTfsgEvtTargetContainer t);

/*! /brief searching for an Item with a PaintRequest, resets PaintRequest,
  /return return 0 = no request, return 1 = PaintRequest
*/
extern int fsgEventPaintRequested(_pTfsgEvtTargetContainer t);

#endif /* __FSGEVENT_H__*/
