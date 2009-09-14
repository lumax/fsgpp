/*
Bastian Ruppert 08.05.2009  

 */

#include "fsgGlobals.h"
static TTF_Font * FontButtonDefault = NULL;

SDL_Color GlobalSDL_ColorSewOrange = {.r = R_SEW_ORANGE,\
					.g = G_SEW_ORANGE,\
					.b = B_SEW_ORANGE}; 
SDL_Color GlobalSDL_ColorSewBlau = {.r = R_SEW_BLAU,\
					.g = G_SEW_BLAU,\
					.b = B_SEW_BLAU}; 
SDL_Color GlobalSDL_ColorSewGelb = {.r = R_SEW_GELB,\
					.g = G_SEW_GELB,\
					.b = B_SEW_GELB}; 
SDL_Color GlobalSDL_ColorSewGruen = {.r = R_SEW_GRUEN,\
					.g = G_SEW_GRUEN,\
					.b = B_SEW_GRUEN}; 
SDL_Color GlobalSDL_ColorSewGrau = {.r = R_SEW_GRAU,\
					.g = G_SEW_GRAU,\
					.b = B_SEW_GRAU}; 
SDL_Color GlobalSDL_ColorSewSchwarz = {.r = R_SEW_SCHWARZ,\
					.g = G_SEW_SCHWARZ,\
					.b = B_SEW_SCHWARZ}; 
Uint32 GlobalUint32ColorSewOrange;
Uint32 GlobalUint32ColorSewBlau;
Uint32 GlobalUint32ColorSewGelb;
Uint32 GlobalUint32ColorSewGruen;
Uint32 GlobalUint32ColorSewGrau;
Uint32 GlobalUint32ColorSewSchwarz;

int fsgGlobalsInit(void)
{
  FontButtonDefault = TTF_OpenFont(DEFAULTFONT,FONTBUTTONDEFAULTSIZE);
  if(!FontButtonDefault)
      return 1;

  GlobalUint32ColorSewOrange = SDL_MapRGB(SDL_GetVideoSurface()->format, \
					  R_SEW_ORANGE,			\
					  G_SEW_ORANGE,			\
					  B_SEW_ORANGE); 
  GlobalUint32ColorSewBlau  = SDL_MapRGB(SDL_GetVideoSurface()->format, \
					 R_SEW_BLAU,			\
					 G_SEW_BLAU,			\
					 B_SEW_BLAU);  
  GlobalUint32ColorSewGelb = SDL_MapRGB(SDL_GetVideoSurface()->format,	\
					R_SEW_GELB,			\
					G_SEW_GELB,			\
					B_SEW_GELB);
  GlobalUint32ColorSewGruen = SDL_MapRGB(SDL_GetVideoSurface()->format,	\
					 R_SEW_GRUEN,			\
					 G_SEW_GRUEN,			\
					 B_SEW_GRUEN);
  GlobalUint32ColorSewGrau = SDL_MapRGB(SDL_GetVideoSurface()->format,	\
					R_SEW_GRAU,			\
					G_SEW_GRAU,			\
					B_SEW_GRAU);
  GlobalUint32ColorSewSchwarz = SDL_MapRGB(SDL_GetVideoSurface()->format, \
					   R_SEW_SCHWARZ,		\
					   G_SEW_SCHWARZ,		\
					   B_SEW_SCHWARZ);
  
  return 0;
}

TTF_Font * fsgGlobalGetDefaultFont(void){
  return FontButtonDefault;
}

