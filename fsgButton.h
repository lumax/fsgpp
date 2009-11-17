/*
fsgButton.h
Bastian Ruppert
08.05.2009
*/

#ifndef __FSGBUTTON_H__
#define __FSGBUTTON_H__
#include <SDL/SDL.h>
#include <SDL/SDL_ttf.h>
#include "fsgEvent.h"



//#define INPUTMODE_TOUCH 1 //Ein Touchscreen wird benutzt

//Maximale Anzahl der Buttons im EventContainer
//#define SDLBTN_MAX_EVENTS 3
//#define SDLBTN_DEFAULTCOLOR {.r=128,.g=128,.b=128}





typedef struct
{
  // SDL_Surface * pNormalSurface;
  //SDL_Surface * pMarkedSurface;
  //SDL_Surface * pTextSurface;
  SDL_Rect PosDimRect;
  const char * pButtonText;
  TTF_Font * pFont;
  SDL_Color * pFontColor;
  _TfsgEvtTarget EvtTarget;
}_TfsgButton,*_pTfsgButton;


/*! \brief fsgButton Default Constructor 
 */
extern int fsgButtonConstructor(_TfsgButton * b);



/*! \brief Setzt den Text eines Buttons.
 *
 */
extern void fsgButtonSetText(_pTfsgButton b,const char* text);

#endif /* __FSGBUTTON_H__*/
