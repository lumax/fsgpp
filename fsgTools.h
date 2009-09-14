/*
fsgTools.h
Bastian Ruppert
*/

#ifndef __FSGTOOLS_H__
#define __FSGTOOLS_H__
#include <SDL/SDL.h>
#include <SDL/SDL_ttf.h>

/*! \brief Zeichnet auf dem Surface an der Stelle PosDim einen rechteckigen 3D Rahmen in der 
 *         Farbe Color.
 */
extern int fsgToolRenderBorderUp(SDL_Surface * target,SDL_Rect * PosDim,Uint32 Color);

/*! \brief Zeichnet auf dem Surface an der Stelle PosDim einen rechteckigen 3D Rahmen in der 
 *         Farbe Color.
 */
extern int fsgToolRenderBorderDown(SDL_Surface * target,SDL_Rect * PosDim,Uint32 Color);

/*! \brief Zeichnet auf dem Surface an der Stelle PosDim einen rechteckigen Rahmen in der 
 *         Farbe Color.
 */
extern int fsgToolRenderBorderFrame(SDL_Surface * target,SDL_Rect * PosDim,Uint32 Color);

/*! \brief Zeichnet auf dem Surface einen rechteckigen Rahmen in der Farbe Color.
 * Der Rahmen ist Breite breit.
 *
 */
extern int fsgToolRenderBorder(SDL_Surface * target,SDL_Rect * PosDim,int Breite,Uint32 Color);

extern int fsgToolBlankSurface(SDL_Surface * s, Uint32 color);

/*! \brief Zeichnet den text auf posdim
 *
 */
extern int fsgToolsBlitText(SDL_Surface * tarSurface,SDL_Rect * posdim,TTF_Font * pFont,SDL_Color * pFontColor,const char * text);

#endif /* __FSGTOOLS_H__*/
