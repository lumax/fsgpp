/*
Label.cpp
Bastian Ruppert
07.2011
*/


#include <SDL/SDL_ttf.h>
#include <SDL/SDL_image.h>
#include <stdlib.h>

#include "Globals.h"
#include "Tools.h"
#include "Button.h"
#include "Label.h"

#include <stdio.h>

namespace EuMax01
{

  static void keyboardDownEvt(void * src,SDL_Event * evt)
  {
    SDL_KeyboardEvent * key = (SDL_KeyboardEvent *)&evt->key;
    char zeichen = 0;
    SDLMod mod = key->keysym.mod;
    //Tool::PrintKeyInfo( key );
    //return;

    if( key->type == SDL_KEYUP )
      {
	//printf( "Release:- " );
      }
    else
      {
	//printf( "Press:- " );
	//PrintKeyInfo( key );
	if(key->keysym.sym == SDLK_DELETE)
	  {
	    printf("entf\n");
	  }
	if(key->keysym.sym == SDLK_BACKSPACE)
	  {
	    printf("backspace\n");
	  }
	if(key->keysym.sym == SDLK_ESCAPE)
	  {
	    printf("escape\n");
	  }
	else
	  {
	    zeichen = Tool::getStdASCII_Char(key);
	  }
	if(zeichen)
	  {
	    printf("%c",zeichen);
	    fflush(0);
	  }
      }
    //PrintKeyInfo( key );
  }

  /*  TextField::TextField(const char * text,				\
		       unsigned int textLen,				\
		       SDL_Rect PositionDimRect):Label(text,	\
							   textLen,	\
							   PositionDimRect.x, \
							   PositionDimRect.y, \
							   PositionDimRect.w, \
							   PositionDimRect.h)
  {

  }*/

  TextField::TextField(const char * text,			\
		       unsigned int textLen,			\
		       short x,					\
		       short y,					\
		       unsigned short w,			\
		       unsigned short h):Label(text,x,y,w,h)
  {
    SDL_Rect tmp;
    this->setKeyboardDownEvtHandler(keyboardDownEvt);

    if(textLen>TextField::MaxTextLen)
      this->TextLen = TextField::MaxTextLen;
    else
      this->TextLen = textLen;
    //this->setKeyboardUpEvtHandler(keyboardEvt);
  }

  /*  Label::Label(const char * text,SDL_Rect PositionDimRect):Button(text,PositionDimRect)
  {

  }*/
  
  Label::Label(const char * text,			\
		 short x,				\
		 short y,				\
		 unsigned short w,			\
	       unsigned short h):Button(text,x,y,w,h)
  {
    SDL_Rect tmp;
    tmp.x = x;
    tmp.y = y;
    tmp.w = w;
    tmp.h = h;
    Button::createButton(this,text,tmp);
    this->PrivateSelectable = 0;
    this->bSelected = false;
    this->PrivateShow = Label::showLabel;
    this->bBorder = false;
  }

/*! \brief show fsgButton on SDL_Surface. Zeichnet den Normalbereich eines Buttons.
 *         
 */
  int Label::showLabel(void * v,SDL_Surface* target)
  {
    SDL_Rect tmpRect;
    Label* b =(Label*)v;
    
    tmpRect.x = b->PosDimRect.x;
    tmpRect.y = b->PosDimRect.y;
    tmpRect.w = b->PosDimRect.w;
    tmpRect.h = b->PosDimRect.h;

    //Background
    if(SDL_FillRect(target,&tmpRect,FSG_COLOR_MARKED)){
	return -1;
      }
    //Text
    tmpRect.x +=2;
    tmpRect.y +=2;
    if(b->pButtonText)
      {
	if(Tool::blitText(target,&tmpRect,b->pFont,b->pFontColor,b->pButtonText)){
	  return -1;
	}
      }
    tmpRect.x -=2;
    tmpRect.y -=2;
    //Border
    if(b->bBorder)
      {
	if( Tool::renderBorderDown(target,&tmpRect,FSG_COLOR_NORMAL)){
	  return -1;
	}
      }
#ifdef FSGPP_SHOW_IMMEDIATELY 
    SDL_UpdateRect(target,tmpRect.x,tmpRect.y,tmpRect.w,tmpRect.h);
#endif
     // SDL_Flip(target);
    return 0;
  }
  
}//end namespace
