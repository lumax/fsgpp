/*
Bastian Ruppert 08.05.2009  

 */

#ifndef __FSGGLOBALS_H__
#define __FSGGLOBALS_H__
#include <SDL/SDL.h>
#include <SDL/SDL_ttf.h>

#define DEFAULTFONT "aispec.ttf"
#define FONTBUTTONDEFAULTSIZE 20
#define FSGDEFAULTCOLORDEPTH 24




//#define FSG_BOARDERWIDTH 2



extern SDL_Color GlobalSDL_ColorSewOrange;
extern SDL_Color GlobalSDL_ColorSewBlau;
extern SDL_Color GlobalSDL_ColorSewGelb;
extern SDL_Color GlobalSDL_ColorSewGruen;
extern SDL_Color GlobalSDL_ColorSewGrau;
extern SDL_Color GlobalSDL_ColorSewSchwarz;
extern Uint32 GlobalUint32ColorSewOrange;
extern Uint32 GlobalUint32ColorSewBlau;
extern Uint32 GlobalUint32ColorSewGelb;
extern Uint32 GlobalUint32ColorSewGruen;
extern Uint32 GlobalUint32ColorSewGrau;
extern Uint32 GlobalUint32ColorSewSchwarz;


#define FSG_BACKGROUND GlobalUint32ColorSewBlau
#define FSG_COLOR_NORMAL GlobalUint32ColorSewBlau
#define FSG_BOARDERCOLOR_NORMAL GlobalUint32ColorSewOrange
#define FSG_COLOR_MARKED GlobalUint32ColorSewOrange
#define FSG_BOARDERCOLOR_MARKED GlobalUint32ColorSewOrange

#define FSG_LABEL_BACKGROUND GlobalUint32ColorSewBlau
//#define FSG_LABEL_FONTCOLOR GlobalUint32ColorSewGrau

extern int fsgGlobalsInit(void);
extern TTF_Font * fsgGlobalGetDefaultFont(void);


#define R_SEW_ORANGE 238 
#define G_SEW_ORANGE 113 
#define B_SEW_ORANGE 0 

#define R_SEW_BLAU 0 
#define G_SEW_BLAU 104 
#define B_SEW_BLAU 132//180 

#define R_SEW_GELB 255 
#define G_SEW_GELB 237 
#define B_SEW_GELB 0 

#define R_SEW_GRUEN 10 
#define G_SEW_GRUEN 154 
#define B_SEW_GRUEN 51 

#define R_SEW_GRAU 207 
#define G_SEW_GRAU 208 
#define B_SEW_GRAU 208 

#define R_SEW_SCHWARZ 26 
#define G_SEW_SCHWARZ 26 
#define B_SEW_SCHWARZ 24
#endif
