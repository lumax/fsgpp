/*
Label.cpp
Bastian Ruppert
07.2011
*/

#include <SDL/SDL_ttf.h>
#include <SDL/SDL_image.h>
#include <stdlib.h>
#include <string.h>

#include "Globals.h"
#include "Tools.h"
#include "Button.h"
#include "Label.h"

//#include <stdio.h>

namespace EuMax01
{

  static void keyboardDownEvtTextField(void * src,SDL_Event * evt)
  {
    TextField* tf = (TextField*)src;
    SDL_KeyboardEvent * key = (SDL_KeyboardEvent *)&evt->key;
    char zeichen = 0;
    //SDLMod mod = key->keysym.mod;
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
	    tf->removeChar();
	  }
	else if(key->keysym.sym == SDLK_BACKSPACE)
	  {
	    tf->removeChar();
	  }
	else if(key->keysym.sym == SDLK_ESCAPE)
	  {
	    //printf("escape\n");
	  }
	else if(key->keysym.sym == SDLK_RETURN)
	  {
	    //printf("enter\n");
	  }
	else
	  {
	    zeichen = Tool::getStdASCII_Char(key);
	  }
	if(zeichen)
	  {
	    tf->addChar(zeichen);
	    //printf("%c",zeichen);
	    //fflush(0);
	  }
      }
    //PrintKeyInfo( key );
  }

  TextField::TextField(const char * text,			\
		       unsigned int maxTextLen,			\
		       short x,					\
		       short y,					\
		       unsigned short w,			\
		       unsigned short h):Label(text,x,y,w,h)
  {
    //SDL_Rect tmp;
    unsigned int len = 0;
    this->setKeyboardDownEvtHandler(keyboardDownEvtTextField);
    textBuffer[MaxTextLen-1]='\0';
    textBuffer[0]='\0';
    
    if(maxTextLen>TextField::MaxTextLen-1)
      this->MaxInstanceTextLen = TextField::MaxTextLen-1;
    else
      this->MaxInstanceTextLen = maxTextLen;
    
    if(text)
      {
	len = strlen(text);
	len++;
	if(len>this->MaxInstanceTextLen)
	  {
	    this->TextLen = this->MaxInstanceTextLen;
	  }
	else
	  {
	    this->TextLen = len;
	  }
	strncpy(this->textBuffer,text,this->TextLen);
      }
    else
      {
	this->TextLen = 0;
      }
    Label::setText(this->textBuffer);

    this->setActive(false);
    //this->setKeyboardUpEvtHandler(keyboardEvt);
  }

  char * TextField::getText()
  {
    return textBuffer;
  }

  unsigned int TextField::getTextLen()
  {
    return TextLen;
  }

  void TextField::addChar(char c)
  {
    if(this->TextLen<this->MaxInstanceTextLen)
      {
	this->textBuffer[this->TextLen]=c;
	this->TextLen++;
	this->textBuffer[this->TextLen]='\0';
	Label::setText(this->textBuffer);
      }
  }

  void TextField::setText(char * text)
  {
    unsigned int textlen = strlen(text);
    this->textBuffer[0]='\0';
    this->TextLen = 0;

    for(unsigned int i=0;i<textlen&&i<TextField::MaxTextLen;i++)
      {
	addChar(text[i]);
      }
  }

  int TextField::removeChar()
  {
    if(this->TextLen)
      {
	this->TextLen--;
	this->textBuffer[TextLen] = '\0';
	Label::setText(this->textBuffer);
      }
    return this->TextLen;
  }

  void TextField::setActive(bool active)
  {
    if(active)
      {
	this->bBorder = true;
	this->setKeyboardDownEvtHandler(keyboardDownEvtTextField);
      }
    else
      {
	this->bBorder = false;
	this->setKeyboardDownEvtHandler(0);
      }
  }

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
    if(SDL_FillRect(target,&tmpRect,b->uiMarkedColor)){
	return -1;
      }
    //Text
    tmpRect.x +=2;
    tmpRect.y +=2;
    if(b->pButtonText)
      {
	Tool::blitText(target,&tmpRect,b->pFont,b->pFontColor,b->pButtonText);
      }
    tmpRect.x -=2;
    tmpRect.y -=2;
    //Border
    if(b->bBorder)
      {
	if( Tool::renderBorderDown(target,&tmpRect,b->uiNormalColor)){
	  return -1;
	}
      }
#ifdef FSGPP_SHOW_IMMEDIATELY 
    SDL_UpdateRect(target,tmpRect.x,tmpRect.y,tmpRect.w,tmpRect.h);
#endif
     // SDL_Flip(target);
    return 0;
  }

  void Label::setBorder(bool border)
  {
    this->bBorder = border;
  }
  
}//end namespace
