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
#define FONTBUTTONBIGSIZE 18
#define FONTBUTTONDEFAULTSIZE 12
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

#define R_LIGHT_GRAY 189
#define G_LIGHT_GRAY 189
#define B_LIGHT_GRAY 189

#define R_BRIGHT_GRAY 130
#define G_BRIGHT_GRAY 130
#define B_BRIGHT_GRAY 130

#define R_DARK_GRAY 110
#define G_DARK_GRAY 110
#define B_DARK_GRAY 110

#define R_NEARLY_BLACK 50
#define G_NEARLY_BLACK 50
#define B_NEARLY_BLACK 50

#define R_BLACK 0
#define G_BLACK 0
#define B_BLACK 0

class Globals
{

 private:
  static Globals * global;
  static TTF_Font * FontButtonDefault;
  static TTF_Font * FontButtonBig;
  Globals();

 public:
   static Globals*  getInstance();
   static SDL_Color GlobalSDL_ColorSewOrange;
   static SDL_Color GlobalSDL_ColorSewBlau;
   static SDL_Color GlobalSDL_ColorSewGelb;
   static SDL_Color GlobalSDL_ColorSewGruen;
   static SDL_Color GlobalSDL_ColorSewGrau;
   static SDL_Color GlobalSDL_ColorSewSchwarz;
   static SDL_Color GlobalSDL_ColorLightGray;
   static SDL_Color GlobalSDL_ColorBrightGray;
   static SDL_Color GlobalSDL_ColorDarkGray;
   static SDL_Color GlobalSDL_ColorNearlyBlack;
   static SDL_Color GlobalSDL_ColorBlack;

   static SDL_Color GlobalSDL_Color1;
   static SDL_Color GlobalSDL_Color2;
   static SDL_Color GlobalSDL_Color3;
   static SDL_Color GlobalSDL_Color4;
   static SDL_Color GlobalSDL_Color5;
   static SDL_Color GlobalSDL_Color6;

   static SDL_Color GlobalSDL_ColorE1;
   static SDL_Color GlobalSDL_ColorE2;
   static SDL_Color GlobalSDL_ColorE3;
   static SDL_Color GlobalSDL_ColorE4;
   static SDL_Color GlobalSDL_ColorE5;
   static SDL_Color GlobalSDL_ColorE6;
   static SDL_Color GlobalSDL_ColorE7;
   static SDL_Color GlobalSDL_ColorE8;
   static SDL_Color GlobalSDL_ColorE9;
   static SDL_Color GlobalSDL_ColorE10;
   static SDL_Color GlobalSDL_ColorE11;
   static SDL_Color GlobalSDL_ColorE12;
   static SDL_Color GlobalSDL_ColorE13;
   static SDL_Color GlobalSDL_ColorE14;
   static SDL_Color GlobalSDL_ColorE15;
   static SDL_Color GlobalSDL_ColorE16;

   static Uint32 GlobalUint32ColorSewOrange;
   static Uint32 GlobalUint32ColorSewBlau;
   static Uint32 GlobalUint32ColorSewGelb;
   static Uint32 GlobalUint32ColorSewGruen;
   static Uint32 GlobalUint32ColorSewGrau;
   static Uint32 GlobalUint32ColorSewSchwarz;

   static Uint32 GlobalUint32ColorLightGray;
   static Uint32 GlobalUint32ColorBrightGray;
   static Uint32 GlobalUint32ColorDarkGray;
   static Uint32 GlobalUint32ColorNearlyBlack;
   static Uint32 GlobalUint32ColorBlack;

   static Uint32 GlobalUint32Color1;
   static Uint32 GlobalUint32Color2;
   static Uint32 GlobalUint32Color3;
   static Uint32 GlobalUint32Color4;
   static Uint32 GlobalUint32Color5;
   static Uint32 GlobalUint32Color6;

   static Uint32 GlobalUint32ColorE1;
   static Uint32 GlobalUint32ColorE2;
   static Uint32 GlobalUint32ColorE3;
   static Uint32 GlobalUint32ColorE4;
   static Uint32 GlobalUint32ColorE5;
   static Uint32 GlobalUint32ColorE6;
   static Uint32 GlobalUint32ColorE7;
   static Uint32 GlobalUint32ColorE8;
   static Uint32 GlobalUint32ColorE9;
   static Uint32 GlobalUint32ColorE10;
   static Uint32 GlobalUint32ColorE11;
   static Uint32 GlobalUint32ColorE12;
   static Uint32 GlobalUint32ColorE13;
   static Uint32 GlobalUint32ColorE14;
   static Uint32 GlobalUint32ColorE15;
   static Uint32 GlobalUint32ColorE16;

   static const Uint32 R_1 = 255;
   static const Uint32 G_1 = 0;
   static const Uint32 B_1 = 255;
   static const Uint32 R_2 = 255;//weiss
   static const Uint32 G_2 = 255;
   static const Uint32 B_2 = 255;
   static const Uint32 R_3 = 0;
   static const Uint32 G_3 = 0;
   static const Uint32 B_3 = 0;
   static const Uint32 R_4 = 0;
   static const Uint32 G_4 = 0;
   static const Uint32 B_4 = 0;
   static const Uint32 R_5 = 0;
   static const Uint32 G_5 = 0;
   static const Uint32 B_5 = 0;
   static const Uint32 R_6 = 0;
   static const Uint32 G_6 = 0;
   static const Uint32 B_6 = 0;

   static const Uint32 R_E1 = 0x01;
   static const Uint32 G_E1 = 0xdf;
   static const Uint32 B_E1 = 0x01;
   static const Uint32 R_E2 = 0x04;
   static const Uint32 G_E2 = 0xb4;
   static const Uint32 B_E2 = 0x31;
   static const Uint32 R_E3 = 0x5f;
   static const Uint32 G_E3 = 0xb4;
   static const Uint32 B_E3 = 0x04;
   static const Uint32 R_E4 = 0x68;
   static const Uint32 G_E4 = 0x8a;
   static const Uint32 B_E4 = 0x08;
   static const Uint32 R_E5 = 0x86;
   static const Uint32 G_E5 = 0x8a;
   static const Uint32 B_E5 = 0x08;
   static const Uint32 R_E6 = 0x88;
   static const Uint32 G_E6 = 0x6a;
   static const Uint32 B_E6 = 0x08;
   static const Uint32 R_E7 = 0x54;
   static const Uint32 G_E7 = 0x5f;
   static const Uint32 B_E7 = 0x04;
   static const Uint32 R_E8 = 0xdf;
   static const Uint32 G_E8 = 0x74;
   static const Uint32 B_E8 = 0x01;
   static const Uint32 R_E9 = 0xff;
   static const Uint32 G_E9 = 0x40;
   static const Uint32 B_E9 = 0x00;
   static const Uint32 R_E10 =0xfe;
   static const Uint32 G_E10 =0x2e;
   static const Uint32 B_E10 =0x2e;
   static const Uint32 R_E11 =0xff;
   static const Uint32 G_E11 =0x00;
   static const Uint32 B_E11 =0x00;
   static const Uint32 R_E12 =0xdf;
   static const Uint32 G_E12 =0x01;
   static const Uint32 B_E12 =0x01;
   static const Uint32 R_E13 =0xb4;
   static const Uint32 G_E13 =0x04;
   static const Uint32 B_E13 =0x04;
   static const Uint32 R_E14 =0x8a;
   static const Uint32 G_E14 =0x08;
   static const Uint32 B_E14 =0x08;
   static const Uint32 R_E15 =0x61;
   static const Uint32 G_E15 =0x0b;
   static const Uint32 B_E15 =0x0b;
   static const Uint32 R_E16 =0x61;
   static const Uint32 G_E16 =0x0b;
   static const Uint32 B_E16 =0x0b;

   static TTF_Font * getFontButtonBig();

  TTF_Font * getDefaultFont(void);
  ~Globals()
    {
      TTF_CloseFont(FontButtonDefault);
      FontButtonDefault=NULL;
    }

};

//#define FSG_BOARDERWIDTH 2

#define FSG_BACKGROUND Globals::GlobalUint32ColorBlack
#define FSG_COLOR_NORMAL Globals::GlobalUint32ColorSewOrange//Globals::GlobalUint32ColorDarkGray
#define FSG_COLOR_MARKED Globals::GlobalUint32ColorLightGray

//#define FSG_COLOR_NORMAL Globals::GlobalUint32ColorSewBlau
//#define FSG_COLOR_MARKED Globals::GlobalUint32ColorSewOrange

//#define FSG_LABEL_BACKGROUND Globals::GlobalUint32ColorBlack

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
