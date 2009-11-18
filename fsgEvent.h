/*
fsgEvent.h
Bastian Ruppert
08.05.2009

*/

#ifndef __FSGEVENT_H__
#define __FSGEVENT_H__
#include <SDL/SDL.h>
#include <fsgLL.h>

typedef struct
{
  _TfsgLL TfsgLL;
  Uint8 unused1;
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
}_TfsgEvtTarget,*_pTfsgEvtTarget;

/*typedef struct
{
  _pTfsgEvtTarget * apEvtTargets;
  int MaxTargets;
  int CounterTargets;
  }_TfsgEvtTargetContainer,*_pTfsgEvtTargetContainer;*/

extern void fsgEventAddEvtTarget(_pTfsgLL z,_pTfsgEvtTarget t);

//extern _pTfsgEvtTargetContainer fsgEventEvtTargetContainerConstructor(int MaxEvtTargets);

extern void fsgEventProcessTargets(SDL_Event * pSDL_Event, _pTfsgLL t);

/*! /brief searching for an Item with a PaintRequest, resets PaintRequest,
  /return return 0 = no request, return 1 = PaintRequest
*/
extern int fsgEventPaintRequested(_pTfsgLL t);

#endif /* __FSGEVENT_H__*/
