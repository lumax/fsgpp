/*
fsgMain.h
Bastian Ruppert
*/

#ifndef __FSGMAIN_H__
#define __FSGMAIN_H__
#include "fsgScreen.h"

typedef struct
{
  _pTfsgScreen pActiveScreen;
  void (*fnkSecondaryEvtHandler)(SDL_Event * theEvent);
  SDL_Surface * pMainSurface;
  //  SDL_Surface * pDoubleBuf0;
  //SDL_Surface * pDoubleBuf1;
  //SDL_Surface * pSurface;
}_TfsgGUI;

typedef struct
{
  int width;
  int height;
  int bpp;//If bpp is 0, it is treated as the current display bits per pixel.
  Uint32 flags;
}_TfsgGUI_Properties;

/*! \brief Initialisiert die GUI
 *
 */
extern int fsgMainInit(_TfsgGUI_Properties * p_properties,void (*fnkSecondaryEvtHandling)(SDL_Event * theEvent));

/*! \brief Set the EvtTargetContainer to process
 *
 */
extern void fsgMainSetActiveScreen(_pTfsgScreen  s);

/*! \brief Returns the ActiveEvtTargets of the GUI the EvtTargetContainer to process
 *
 */
extern _pTfsgEvtTargetContainer fsgMainGetActiveEvtTargets(void);

extern void fsgMainActivateScreen(_pTfsgScreen s);

/*! \brief Processing the SDL_Events in endlessloop
 *
 */
extern int fsgMainEventLoop(void);

#endif /* __FSGEVENT_H__*/
