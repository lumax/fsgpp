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

  class Button : public EvtTarget
  {
  public:
    Button(const char * text,SDL_Rect PositionDimRect);
    //~Button();
    void setText(const char* text);
  private:
    //SDL_Surface * pNormalSurface;
    //SDL_Surface * pMarkedSurface;
    //SDL_Surface * pTextSurface;
    SDL_Rect PosDimRect;
    const char * pButtonText;
    TTF_Font * pFont;
    SDL_Color * pFontColor;

    static int show(void * pB,SDL_Surface * pSurface);
    static void select(void * b,bool seleced);
    
  };

#endif /* __FSGBUTTON_H__*/
}//end namespace

