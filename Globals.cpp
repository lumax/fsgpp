/*
Bastian Ruppert 08.05.2009  

 */
#include <SDL/SDL.h>
#include <SDL/SDL_ttf.h>
#include "Globals.h"
namespace EuMax01
{
  Globals* Globals::global = NULL;
  TTF_Font* Globals::FontButtonDefault = NULL;

  SDL_Color Globals::GlobalSDL_ColorSewOrange = {R_SEW_ORANGE,G_SEW_ORANGE,B_SEW_ORANGE,0}; 
  SDL_Color Globals::GlobalSDL_ColorSewBlau = {R_SEW_BLAU,G_SEW_BLAU,B_SEW_BLAU,0}; 
  SDL_Color Globals::GlobalSDL_ColorSewGelb = {R_SEW_GELB,G_SEW_GELB,B_SEW_GELB,0}; 
  SDL_Color Globals::GlobalSDL_ColorSewGruen = {R_SEW_GRUEN,G_SEW_GRUEN,B_SEW_GRUEN,0}; 
  SDL_Color Globals::GlobalSDL_ColorSewGrau = {R_SEW_GRAU,G_SEW_GRAU,B_SEW_GRAU,0}; 
  SDL_Color Globals::GlobalSDL_ColorSewSchwarz = {R_SEW_SCHWARZ,G_SEW_SCHWARZ,B_SEW_SCHWARZ,0};   
  SDL_Color Globals::GlobalSDL_ColorBrightGray = {R_BRIGHT_GRAY,G_BRIGHT_GRAY,B_BRIGHT_GRAY,0};
  SDL_Color Globals::GlobalSDL_ColorDarkGray= {R_DARK_GRAY,G_DARK_GRAY,B_DARK_GRAY,0};
  SDL_Color Globals::GlobalSDL_ColorBlack= {R_BLACK,G_BLACK,B_BLACK,0};

  Uint32 Globals::GlobalUint32ColorSewOrange=0;
  Uint32 Globals::GlobalUint32ColorSewBlau=0;
  Uint32 Globals::GlobalUint32ColorSewGelb=0;
  Uint32 Globals::GlobalUint32ColorSewGruen=0;
  Uint32 Globals::GlobalUint32ColorSewGrau=0;
  Uint32 Globals::GlobalUint32ColorSewSchwarz=0;

  Uint32 Globals::GlobalUint32ColorBrightGray=0;
  Uint32 Globals::GlobalUint32ColorDarkGray=0;
  Uint32 Globals::GlobalUint32ColorBlack=0;

  Globals* Globals::getInstance()
  {
    if(FontButtonDefault)
      {
	return global;
      }
    else
      {
	FontButtonDefault = TTF_OpenFont(DEFAULTFONT,FONTBUTTONDEFAULTSIZE);
	if(FontButtonDefault)
	  {
	    global = new Globals();
	    return global;
	  }
	return NULL;
      }
  }
  Globals::Globals()
  {
   
 


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
  GlobalUint32ColorBrightGray = SDL_MapRGB(SDL_GetVideoSurface()->format, \
					   R_BRIGHT_GRAY,		\
					   G_BRIGHT_GRAY,		\
					   B_BRIGHT_GRAY);
  GlobalUint32ColorDarkGray = SDL_MapRGB(SDL_GetVideoSurface()->format, \
					   R_DARK_GRAY,		\
					   G_DARK_GRAY,		\
					   B_DARK_GRAY);
  GlobalUint32ColorBlack = SDL_MapRGB(SDL_GetVideoSurface()->format, \
					   R_BLACK,		\
					   G_BLACK,		\
					   B_BLACK);
  }

  TTF_Font * Globals::getDefaultFont(void){
    return this->FontButtonDefault;
  }

}//end namespace
