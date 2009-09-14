/*
Bastian Ruppert
*/
#ifndef __FSGSCREEN_H__
#define __FSGSCREEN_H__

#include "fsgEvent.h"
#include "fsgButton.h"
#include "fsgLabel.h"

typedef struct
{
  int MaxEvtTargets;
  _pTfsgEvtTargetContainer pTargets;
}_TfsgScreen, *_pTfsgScreen;


/*! \brief creates new screen instance
 */
extern _pTfsgScreen fsgScreenConstructor(int MaxEventTargets);

/*! \brief add component to screeninstance
 */
extern int fsgScreenAddEvtTarget(_pTfsgScreen theScreen,_pTfsgEvtTarget theTarget);

/*! \brief Activate this Screen
 */

/*! \brief activate the screeninstance
 */
extern void fsgScreenShow(_pTfsgScreen s,SDL_Surface * pSurface);

/*! \brief add Button to  the screeninstance
 */
extern int fsgScreenAddButton(_pTfsgScreen s, _TfsgButton * btn);

/*! \brief add Label to  the screeninstance
 */
extern int fsgScreenAddLabel(_pTfsgScreen s, _TfsgLabel * pL);
#endif /* __FSGSCREEN_H__*/
