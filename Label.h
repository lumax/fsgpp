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

    Label(const char * text,			\
	   short x,				\
	   short y,				\
	   unsigned short w,			\
	  unsigned short h,			\
	  ButtonSettings * settings);
    //Label(const char * text,SDL_Rect PositionDimRect);
    //static void createLabel(Label* b,const char * t,SDL_Rect posDim);
    void setBorder(bool border);
    static int showLabel(void * v,SDL_Surface* target);
  protected:
    bool bBorder;
  };

  class TextField : public Label
  {
  public:
    TextField(const char * text,			\
	      unsigned int maxTextLen,			\
	      short x,					\
	      short y,					\
	      unsigned short w,				\
	      unsigned short h);
    TextField(const char * text,			\
	      unsigned int maxTextLen,			\
	      short x,					\
	      short y,					\
	      unsigned short w,				\
	      unsigned short h,				\
	      ButtonSettings * set);
    int removeChar(void);
    void addChar(char c);
    void setActive(bool active);
    char * getText();
    static const int StdASCIIChar = 0;
    static const int FloatNumericChar = 1;
    static const int IntegerNumericChar = 2;
    void activateKeyListener(int listener);

    /*! brief füllt text in das Textfeld ein und beachtet die
     * Textlänge
     */ 
    void setText(char * text);
    unsigned int getTextLen();
    static void keyboardDownEvtTextField(void * src,SDL_Event * evt);
  private:
    char (*keyLis)(SDL_KeyboardEvent * key);
    static const unsigned int MaxTextLen = 256;
    unsigned int MaxInstanceTextLen;
    char textBuffer[MaxTextLen];
    unsigned int TextLen;
  };

#endif /* __FSGLABEL_H__*/
}//end namespace

