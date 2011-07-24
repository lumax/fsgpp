/*
Button.cpp
Bastian Ruppert
04.12.2010
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
  void PrintModifiers( SDLMod mod );
   /* Print all information about a key event */
    void PrintKeyInfo( SDL_KeyboardEvent *key ){
        /* Is it a release or a press? */
        if( key->type == SDL_KEYUP )
            printf( "Release:- " );
        else
            printf( "Press:- " );

        /* Print the hardware scancode first */
        printf( "Scancode: 0x%02X", key->keysym.scancode );
        /* Print the name of the key */
        printf( ", Name: %s", SDL_GetKeyName( key->keysym.sym ) );
        /* We want to print the unicode info, but we need to make */
        /* sure its a press event first (remember, release events */
        /* don't have unicode info                                */
        if( key->type == SDL_KEYDOWN ){
            /* If the Unicode value is less than 0x80 then the    */
            /* unicode value can be used to get a printable       */
            /* representation of the key, using (char)unicode.    */
            printf(", Unicode: " );
            if( key->keysym.unicode < 0x80 && key->keysym.unicode > 0 ){
                printf( "%c (0x%04X)", (char)key->keysym.unicode,
                        key->keysym.unicode );
            }
            else{
                printf( "? (0x%04X)", key->keysym.unicode );
            }
        }
        printf( "\n" );
        /* Print modifier info */
        PrintModifiers( key->keysym.mod );
    }

    /* Print modifier info */
    void PrintModifiers( SDLMod mod ){
        printf( "Modifers: " );

        /* If there are none then say so and return */
        if( mod == KMOD_NONE ){
            printf( "None\n" );
            return;
        }

        /* Check for the presence of each SDLMod value */
        /* This looks messy, but there really isn't    */
        /* a clearer way.                              */
        if( mod & KMOD_NUM ) printf( "NUMLOCK " );
        if( mod & KMOD_CAPS ) printf( "CAPSLOCK " );
        if( mod & KMOD_LCTRL ) printf( "LCTRL " );
        if( mod & KMOD_RCTRL ) printf( "RCTRL " );
        if( mod & KMOD_RSHIFT ) printf( "RSHIFT " );
        if( mod & KMOD_LSHIFT ) printf( "LSHIFT " );
        if( mod & KMOD_RALT ) printf( "RALT " );
        if( mod & KMOD_LALT ) printf( "LALT " );
        if( mod & KMOD_CTRL ) printf( "CTRL " );
        if( mod & KMOD_SHIFT ) printf( "SHIFT " );
        if( mod & KMOD_ALT ) printf( "ALT " );
        printf( "\n" );
    }

  static void keyboardUp(void * src,SDL_Event * evt)
  {
    PrintKeyInfo( &evt->key );
  }

  Label::Label(const char * text,SDL_Rect PositionDimRect):Button(text,PositionDimRect)
  {

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
    this->setKeyboardDownEvtHandler(keyboardUp);
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
