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
  TTF_Font* Globals::FontButtonBig = 0;

  SDL_Color Globals::GlobalSDL_ColorSewOrange = {R_SEW_ORANGE,G_SEW_ORANGE,B_SEW_ORANGE,0}; 
  SDL_Color Globals::GlobalSDL_ColorSewBlau = {R_SEW_BLAU,G_SEW_BLAU,B_SEW_BLAU,0}; 
  SDL_Color Globals::GlobalSDL_ColorSewGelb = {R_SEW_GELB,G_SEW_GELB,B_SEW_GELB,0}; 
  SDL_Color Globals::GlobalSDL_ColorSewGruen = {R_SEW_GRUEN,G_SEW_GRUEN,B_SEW_GRUEN,0}; 
  SDL_Color Globals::GlobalSDL_ColorSewGrau = {R_SEW_GRAU,G_SEW_GRAU,B_SEW_GRAU,0}; 
  SDL_Color Globals::GlobalSDL_ColorSewSchwarz = {R_SEW_SCHWARZ,G_SEW_SCHWARZ,B_SEW_SCHWARZ,0};
  SDL_Color Globals::GlobalSDL_ColorLightGray = {R_BRIGHT_GRAY,G_BRIGHT_GRAY,B_BRIGHT_GRAY,0};  
  SDL_Color Globals::GlobalSDL_ColorBrightGray = {R_BRIGHT_GRAY,G_BRIGHT_GRAY,B_BRIGHT_GRAY,0};
  SDL_Color Globals::GlobalSDL_ColorDarkGray= {R_DARK_GRAY,G_DARK_GRAY,B_DARK_GRAY,0};
  SDL_Color Globals::GlobalSDL_ColorNearlyBlack= {R_NEARLY_BLACK,G_NEARLY_BLACK,B_NEARLY_BLACK,0};
  SDL_Color Globals::GlobalSDL_ColorBlack= {R_BLACK,G_BLACK,B_BLACK,0};

  SDL_Color Globals::GlobalSDL_Color1={R_1,G_1,B_1};
  SDL_Color Globals::GlobalSDL_Color2={R_2,G_2,B_2};
  SDL_Color Globals::GlobalSDL_Color3={R_3,G_3,B_3};
  SDL_Color Globals::GlobalSDL_Color4={R_4,G_4,B_4};
  SDL_Color Globals::GlobalSDL_Color5={R_5,G_5,B_5};
  SDL_Color Globals::GlobalSDL_Color6={R_6,G_6,B_6};

  SDL_Color Globals::GlobalSDL_ColorE1={R_E1,G_E1,B_E1};
  SDL_Color Globals::GlobalSDL_ColorE2={R_E2,G_E2,B_E2};
  SDL_Color Globals::GlobalSDL_ColorE3={R_E3,G_E3,B_E3};
  SDL_Color Globals::GlobalSDL_ColorE4={R_E4,G_E4,B_E4};
  SDL_Color Globals::GlobalSDL_ColorE5={R_E5,G_E5,B_E5};
  SDL_Color Globals::GlobalSDL_ColorE6={R_E6,G_E6,B_E6};
  SDL_Color Globals::GlobalSDL_ColorE7={R_E7,G_E7,B_E7};
  SDL_Color Globals::GlobalSDL_ColorE8={R_E8,G_E8,B_E8};
  SDL_Color Globals::GlobalSDL_ColorE9={R_E9,G_E9,B_E9};
  SDL_Color Globals::GlobalSDL_ColorE10={R_E10,G_E10,B_E10};
  SDL_Color Globals::GlobalSDL_ColorE11={R_E11,G_E11,B_E11};
  SDL_Color Globals::GlobalSDL_ColorE12={R_E12,G_E12,B_E12};
  SDL_Color Globals::GlobalSDL_ColorE13={R_E13,G_E13,B_E13};
  SDL_Color Globals::GlobalSDL_ColorE14={R_E14,G_E14,B_E14};
  SDL_Color Globals::GlobalSDL_ColorE15={R_E15,G_E15,B_E15};
  SDL_Color Globals::GlobalSDL_ColorE16={R_E16,G_E16,B_E16};

  Uint32 Globals::GlobalUint32ColorSewOrange=0;
  Uint32 Globals::GlobalUint32ColorSewBlau=0;
  Uint32 Globals::GlobalUint32ColorSewGelb=0;
  Uint32 Globals::GlobalUint32ColorSewGruen=0;
  Uint32 Globals::GlobalUint32ColorSewGrau=0;
  Uint32 Globals::GlobalUint32ColorSewSchwarz=0;

  Uint32 Globals::GlobalUint32ColorLightGray=0;
  Uint32 Globals::GlobalUint32ColorBrightGray=0;
  Uint32 Globals::GlobalUint32ColorDarkGray=0;
  Uint32 Globals::GlobalUint32ColorNearlyBlack=0;
  Uint32 Globals::GlobalUint32ColorBlack=0;

  Uint32 Globals::GlobalUint32Color1=0;
  Uint32 Globals::GlobalUint32Color2=0;
  Uint32 Globals::GlobalUint32Color3=0;
  Uint32 Globals::GlobalUint32Color4=0;
  Uint32 Globals::GlobalUint32Color5=0;
  Uint32 Globals::GlobalUint32Color6=0;

  Uint32 Globals::GlobalUint32ColorE1=0;
  Uint32 Globals::GlobalUint32ColorE2=0;
  Uint32 Globals::GlobalUint32ColorE3=0;
  Uint32 Globals::GlobalUint32ColorE4=0;
  Uint32 Globals::GlobalUint32ColorE5=0;
  Uint32 Globals::GlobalUint32ColorE6=0;
  Uint32 Globals::GlobalUint32ColorE7=0;
  Uint32 Globals::GlobalUint32ColorE8=0;
  Uint32 Globals::GlobalUint32ColorE9=0;
  Uint32 Globals::GlobalUint32ColorE10=0;
  Uint32 Globals::GlobalUint32ColorE11=0;
  Uint32 Globals::GlobalUint32ColorE12=0;
  Uint32 Globals::GlobalUint32ColorE13=0;
  Uint32 Globals::GlobalUint32ColorE14=0;
  Uint32 Globals::GlobalUint32ColorE15=0;
  Uint32 Globals::GlobalUint32ColorE16=0;

  Globals* Globals::getInstance()
  {
    if(FontButtonDefault)
      {
	return global;
      }
    else
      {
	FontButtonBig = TTF_OpenFont(DEFAULTFONT,FONTBUTTONBIGSIZE);
	if(!FontButtonBig)
	  {
	    return 0;
	  }
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
  GlobalUint32ColorLightGray = SDL_MapRGB(SDL_GetVideoSurface()->format, \
					   R_LIGHT_GRAY,		\
					   G_LIGHT_GRAY,		\
					   B_LIGHT_GRAY);
  GlobalUint32ColorBrightGray = SDL_MapRGB(SDL_GetVideoSurface()->format, \
					   R_BRIGHT_GRAY,		\
					   G_BRIGHT_GRAY,		\
					   B_BRIGHT_GRAY);
  GlobalUint32ColorDarkGray = SDL_MapRGB(SDL_GetVideoSurface()->format, \
					   R_DARK_GRAY,		\
					   G_DARK_GRAY,		\
					   B_DARK_GRAY);
  GlobalUint32ColorBlack = SDL_MapRGB(SDL_GetVideoSurface()->format,	\
				      R_NEARLY_BLACK,				\
				      G_NEARLY_BLACK,				\
				      B_NEARLY_BLACK);
  GlobalUint32ColorBlack = SDL_MapRGB(SDL_GetVideoSurface()->format,	\
					   R_BLACK,		\
					   G_BLACK,		\
					   B_BLACK);
  GlobalUint32Color1 = SDL_MapRGB(SDL_GetVideoSurface()->format,	\
				  Globals::R_1,				\
				  Globals::G_1,				\
				  Globals::B_1);
  GlobalUint32Color2 = SDL_MapRGB(SDL_GetVideoSurface()->format,	\
				  Globals::R_2,				\
				  Globals::G_2,				\
				  Globals::B_2);
  GlobalUint32Color3 = SDL_MapRGB(SDL_GetVideoSurface()->format,	\
				  Globals::R_3,				\
				  Globals::G_3,				\
				  Globals::B_3);
  GlobalUint32Color4 = SDL_MapRGB(SDL_GetVideoSurface()->format,	\
				  Globals::R_4,				\
				  Globals::G_4,				\
				  Globals::B_4);
  GlobalUint32Color5 = SDL_MapRGB(SDL_GetVideoSurface()->format,	\
				  Globals::R_5,				\
				  Globals::G_5,				\
				  Globals::B_5);
  GlobalUint32Color6 = SDL_MapRGB(SDL_GetVideoSurface()->format,	\
				  Globals::R_6,				\
				  Globals::G_6,				\
				  Globals::B_6);

  GlobalUint32ColorE1 = SDL_MapRGB(SDL_GetVideoSurface()->format,	\
				   Globals::R_E1,			\
				   Globals::G_E1,			\
				   Globals::B_E1);
  GlobalUint32ColorE2 = SDL_MapRGB(SDL_GetVideoSurface()->format,	\
				   Globals::R_E2,			\
				   Globals::G_E2,			\
				   Globals::B_E2);
  GlobalUint32ColorE3 = SDL_MapRGB(SDL_GetVideoSurface()->format,	\
				   Globals::R_E3,			\
				   Globals::G_E3,			\
				   Globals::B_E3);
  GlobalUint32ColorE4 = SDL_MapRGB(SDL_GetVideoSurface()->format,	\
				   Globals::R_E4,			\
				   Globals::G_E4,			\
				   Globals::B_E4);
  GlobalUint32ColorE5 = SDL_MapRGB(SDL_GetVideoSurface()->format,	\
				   Globals::R_E5,			\
				   Globals::G_E5,			\
				   Globals::B_E5);
  GlobalUint32ColorE6 = SDL_MapRGB(SDL_GetVideoSurface()->format,	\
				   Globals::R_E6,			\
				   Globals::G_E6,			\
				   Globals::B_E6);
  GlobalUint32ColorE7 = SDL_MapRGB(SDL_GetVideoSurface()->format,	\
				   Globals::R_E7,			\
				   Globals::G_E7,			\
				   Globals::B_E7);
  GlobalUint32ColorE8 = SDL_MapRGB(SDL_GetVideoSurface()->format,	\
				   Globals::R_E8,			\
				   Globals::G_E8,			\
				   Globals::B_E8);
  GlobalUint32ColorE9 = SDL_MapRGB(SDL_GetVideoSurface()->format,	\
				   Globals::R_E9,			\
				   Globals::G_E9,			\
				   Globals::B_E9);
  GlobalUint32ColorE10 = SDL_MapRGB(SDL_GetVideoSurface()->format,	\
				   Globals::R_E10,			\
				   Globals::G_E10,			\
				   Globals::B_E10);
  GlobalUint32ColorE11 = SDL_MapRGB(SDL_GetVideoSurface()->format,	\
				   Globals::R_E11,			\
				   Globals::G_E11,			\
				   Globals::B_E11);
  GlobalUint32ColorE12 = SDL_MapRGB(SDL_GetVideoSurface()->format,	\
				   Globals::R_E12,			\
				   Globals::G_E12,			\
				   Globals::B_E12);
  GlobalUint32ColorE13 = SDL_MapRGB(SDL_GetVideoSurface()->format,	\
				   Globals::R_E13,			\
				   Globals::G_E13,			\
				   Globals::B_E13);
  GlobalUint32ColorE14 = SDL_MapRGB(SDL_GetVideoSurface()->format,	\
				   Globals::R_E14,			\
				   Globals::G_E14,			\
				   Globals::B_E14);
  GlobalUint32ColorE15 = SDL_MapRGB(SDL_GetVideoSurface()->format,	\
				   Globals::R_E15,			\
				   Globals::G_E15,			\
				   Globals::B_E15);
  GlobalUint32ColorE16 = SDL_MapRGB(SDL_GetVideoSurface()->format,	\
				   Globals::R_E16,			\
				   Globals::G_E16,			\
				   Globals::B_E16);
  }



  TTF_Font * Globals::getDefaultFont(void){
    return this->FontButtonDefault;
  }

  TTF_Font * Globals::getFontButtonBig()
  {
    return Globals::FontButtonBig;
  }
}//end namespace
