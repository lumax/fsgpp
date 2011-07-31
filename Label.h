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

#ifndef __FSGLABEL_H__
#define __FSGLABEL_H__

  class Label : public Button
  {
  public:
    Label(const char * text,			\
	   short x,				\
	   short y,				\
	   unsigned short w,			\
	   unsigned short h);
    //Label(const char * text,SDL_Rect PositionDimRect);
    //static void createLabel(Label* b,const char * t,SDL_Rect posDim);
  protected:
    bool bBorder;
    static int showLabel(void * v,SDL_Surface* target);
    
  };

  class TextField : public Label
  {
  public:
    TextField(const char * text,			\
	      short x,					\
	      short y,					\
	      unsigned short w,				\
	      unsigned short h);
    void removeChar(void);
    void addChar(char c);
  private:
    static const unsigned int MaxTextLen = 8;
    char textBuffer[MaxTextLen];
    unsigned int TextLen;
  };

#endif /* __FSGLABEL_H__*/
}//end namespace

