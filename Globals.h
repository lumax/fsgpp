/*
Bastian Ruppert 08.05.2009  

 */

namespace EuMax01
{

#ifndef __FSGGLOBALS_H__
#define __FSGGLOBALS_H__

/*
  define FSGPP_SHOW_IMMEDIATELY to let all Ites print their content
  by themself and do not use SDL_Flip in Main.cpp
  #undef FSGPP_SHOW_IMMEDIAELY
 */

#define DEFAULTFONT "aispec.ttf"
  //#define DEFAULTFONT "sfd/FreeSerif.ttf"
#define FONTBUTTONDEFAULTSIZE 20
#define FSGDEFAULTCOLORDEPTH 24

  static const unsigned char R_SEW_ORANGE = 238; 
  static const unsigned char G_SEW_ORANGE = 113; 
  static const unsigned char B_SEW_ORANGE =  0; 

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

#define R_BRIGHT_GRAY 130
#define G_BRIGHT_GRAY 130
#define B_BRIGHT_GRAY 130

#define R_DARK_GRAY 110
#define G_DARK_GRAY 110
#define B_DARK_GRAY 110

#define R_BLACK 0
#define G_BLACK 0
#define B_BLACK 0

class Globals
{

 private:
  static Globals * global;
  static TTF_Font * FontButtonDefault;
  Globals();

 public:
   static Globals*  getInstance();
   static SDL_Color GlobalSDL_ColorSewOrange;
   static SDL_Color GlobalSDL_ColorSewBlau;
   static SDL_Color GlobalSDL_ColorSewGelb;
   static SDL_Color GlobalSDL_ColorSewGruen;
   static SDL_Color GlobalSDL_ColorSewGrau;
   static SDL_Color GlobalSDL_ColorSewSchwarz;
   static SDL_Color GlobalSDL_ColorBrightGray;
   static SDL_Color GlobalSDL_ColorDarkGray;
   static SDL_Color GlobalSDL_ColorBlack;

   static Uint32 GlobalUint32ColorSewOrange;
   static Uint32 GlobalUint32ColorSewBlau;
   static Uint32 GlobalUint32ColorSewGelb;
   static Uint32 GlobalUint32ColorSewGruen;
   static Uint32 GlobalUint32ColorSewGrau;
   static Uint32 GlobalUint32ColorSewSchwarz;

   static Uint32 GlobalUint32ColorBrightGray;
   static Uint32 GlobalUint32ColorDarkGray;
   static Uint32 GlobalUint32ColorBlack;

  TTF_Font * getDefaultFont(void);
  ~Globals()
    {
      TTF_CloseFont(FontButtonDefault);
      FontButtonDefault=NULL;
    }

};

//#define FSG_BOARDERWIDTH 2

#define FSG_BACKGROUND Globals::GlobalUint32ColorSewBlau
#define FSG_COLOR_NORMAL Globals::GlobalUint32ColorDarkGray
#define FSG_COLOR_MARKED Globals::GlobalUint32ColorBrightGray

#define FSG_LABEL_BACKGROUND Globals::GlobalUint32ColorSewBlau

/* Sew - Style
#define FSG_BACKGROUND Globals::GlobalUint32ColorSewBlau
#define FSG_COLOR_NORMAL Globals::GlobalUint32ColorSewBlau
#define FSG_BOARDERCOLOR_NORMAL Globals::GlobalUint32ColorSewOrange
#define FSG_COLOR_MARKED Globals::GlobalUint32ColorSewOrange
#define FSG_BOARDERCOLOR_MARKED Globals::GlobalUint32ColorSewOrange

#define FSG_LABEL_BACKGROUND Globals::GlobalUint32ColorSewBlau
*/





#endif
}
