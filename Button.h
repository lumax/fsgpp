/*
Button.h
Bastian Ruppert
04.12.2010
*/

#include <SDL/SDL.h>
#include <SDL/SDL_ttf.h>
#include "Event.h"


namespace EuMax01
{

#ifndef __FSGBUTTON_H__
#define __FSGBUTTON_H__

  class ButtonSettings
  {
  public:
    ButtonSettings(TTF_Font* Font,		\
		   SDL_Color * FontColor,		\
		   unsigned int NormalColor,	\
		   unsigned int MarkedColor);
    ~ButtonSettings();

    TTF_Font* getFont();
    SDL_Color * getFontColor();
    unsigned int getNormalColor();
    unsigned int getMarkedColor();

  private:
    TTF_Font* Font;
    SDL_Color * Color;
    unsigned int NormalColor;
    unsigned int MarkedColor;
  };

  class Button : public EvtTarget
  {
  public:
    Button(const char * text,			\
	   short x,				\
	   short y,				\
	   unsigned short w,			\
	   unsigned short h);

    Button(const char * text,			\
	   short x,				\
	   short y,				\
	   unsigned short w,			\
	   unsigned short h,			\
	   ButtonSettings * settings);

    Button(const char * text,SDL_Rect PositionDimRect);
    static void createButton(Button* b,\
			     const char * t,\
			     SDL_Rect posDim,\
			     ButtonSettings * settings);
    //~Button();
    void setText(const char* text);
    int setImages(const char* normal,const char* down);
    void setImages(SDL_Surface* normal,		\
		  SDL_Surface* down);
    void setFont(TTF_Font* font);
    void setFontColor(SDL_Color * pColor);
    void setNormalColor(unsigned int c);
    void setMarkedColor(unsigned int c);

  private:
    SDL_Surface * pNormalSurface;
    SDL_Surface * pMarkedSurface;

    static int showImages(void * v,SDL_Surface* target);
    static void mouseOverEvent(void * b,bool MouseOver);

  protected:
    const char * pButtonText;
    TTF_Font * pFont;
    SDL_Color * pFontColor;
    unsigned int uiNormalColor;
    unsigned int uiMarkedColor;
    static int show(void * pB,SDL_Surface * pSurface);
  };

#endif /* __FSGBUTTON_H__*/
}//end namespace

