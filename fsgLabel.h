/*
Bastian Ruppert
*/

#ifndef __FSGLABEL_H__
#define __FSGLABEL_H__
#include <SDL/SDL.h>
#include <SDL/SDL_ttf.h>
#include "fsgEvent.h"

typedef struct
{
  SDL_Rect PosDimRect;
  int bSelected;
  const char * pLabelText;
  TTF_Font * pFont;
  SDL_Color * pFontColor;
  _TfsgEvtTarget EvtTarget;
}_TfsgLabel,*_pTfsgLabel;


/*! \brief fsgButton Default Constructor 
 */
extern int fsgLabelConstructor(_TfsgLabel * b);

/*! \brief process the  fsgButton Event Handler 
 */
//extern void fsgLabelProcess(SDL_Event * evt,_pTfsgEvtTarget tar);

/*! \brief show fsgButton on SDL_Surface. Zeichnet den Normalbereich eines Buttons.
 *         
 */
extern int fsgLabelShow(_pTfsgLabel pL,SDL_Surface * pSurface);

/*! \brief Setzt den Text eines Buttons.
 *
 */
extern void fsgLabelSetText(_pTfsgLabel b,const char* text);

#endif /* __FSGLABEL_H__*/
