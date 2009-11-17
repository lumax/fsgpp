/*
Bastian Ruppert
*/
#ifndef __FSGSCREEN_H__
#define __FSGSCREEN_H__

#include <fsgLL.h>
#include "fsgEvent.h"
#include "fsgButton.h"
#include "fsgLabel.h"

typedef struct
{
  _TfsgLL EvtTargets;
  void (*OnActivate)(void);
  void (*OnDeactivate)(void);
}_TfsgScreen;

/*! \brief creates new screen instance
 */
//extern _pTfsgScreen fsgScreenConstructor();

/*! \brief add component to screeninstance
 */
extern int fsgScreenAddEvtTarget(_TfsgScreen * theScreen,_pTfsgEvtTarget theTarget);

/*! \brief Activate this Screen
 */

/*! \brief activate the screeninstance
 */
extern void fsgScreenShow(_TfsgScreen * s,SDL_Surface * pSurface);

/*! \brief add Button to  the screeninstance
 */
extern int fsgScreenAddButton(_TfsgScreen * s, _TfsgButton * btn);

/*! \brief add Label to  the screeninstance
 */
extern int fsgScreenAddLabel(_TfsgScreen * s, _TfsgLabel * pL);
#endif /* __FSGSCREEN_H__*/
