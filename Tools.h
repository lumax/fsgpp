/*
fsgTools.h
Bastian Ruppert
*/

#ifndef __FSGTOOLS_H__
#define __FSGTOOLS_H__

namespace EuMax01
{




class Tool
{
 public:
  static int renderBorderUp(SDL_Surface * target,SDL_Rect * PosDim,Uint32 Color);
  static int renderBorderDown(SDL_Surface * target,SDL_Rect * PosDim,Uint32 Color);
  static int renderBorderFrame(SDL_Surface * target,SDL_Rect * PosDim,Uint32 Color);
  static int renderBorder(SDL_Surface * target,SDL_Rect * PosDim,int Breite,Uint32 Color);
  static int blankSurface(SDL_Surface * s, Uint32 color);
  static int blankSurface(SDL_Surface * s,	\
			  Uint32 color,		\
			  SDL_Rect * area);
  static int blitText(SDL_Surface * tarSurface,SDL_Rect * posdim,TTF_Font * pFont,SDL_Color * pFontColor,const char * text); 
 private:
  static Uint32 getPixel(SDL_Surface *surf, int x, int y);
  static Uint32 becloudColor(SDL_PixelFormat * format,Uint8 *r,Uint8 *g, Uint8 * b, unsigned int offset);
  static Uint32 brightenColor(SDL_PixelFormat * format,Uint8 *r,Uint8 *g, Uint8 * b, unsigned int offset);
  static int getRGB(Uint32 Color,Uint8 * pr,Uint8 * pg,Uint8 * pb);
  static int renderBorder3D(SDL_Surface * target,SDL_Rect * PosDim,Uint32 Color,int boolUp);

};



}
#endif /* __FSGTOOLS_H__*/

