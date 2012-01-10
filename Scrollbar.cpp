/*
Scrollbar.cpp
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
#include "Scrollbar.h"

//#include <stdio.h>

namespace EuMax01
{

  Scrollbar::Scrollbar(int maxValue,				\
		       int minValue,				\
		       int actialValue,				\
		       short x,					\
		       short y,					\
		       unsigned short w,			\
		       unsigned short h):EvtTarget(),		\
					 leftBtn(0,0,0,0,0),	\
					 rightBtn(0,0,0,0,0),	\
					 scrollRegion(0,0,0,0,0),\
					 scrollPosition(0,0,0,0,0)
  {
    //    LeftBtn = Button(0,0,0,0,0);
    SDL_Rect tmp;
    if(w<(Scrollbar::NormalWidth*2+Scrollbar::NormalPositionWidth))
      w = Scrollbar::NormalWidth*2+Scrollbar::NormalPositionWidth;
    tmp.x = x;
    tmp.y = y;
    tmp.w = Scrollbar::NormalWidth;
    tmp.h = h;
    Button::createButton(&this->leftBtn,"<",tmp,0);
    this->leftBtn.bMouseOver = false;

    tmp.x = x + w - Scrollbar::NormalWidth;
    tmp.y = y;
    tmp.w = Scrollbar::NormalWidth;
    tmp.h = h;
    Button::createButton(&this->rightBtn,">",tmp,0);
    this->rightBtn.bMouseOver = false;

    tmp.x = x + Scrollbar::NormalWidth+1;
    tmp.y = y;
    tmp.w = w - Scrollbar::NormalWidth*2-2;
    tmp.h = h;
    Button::createButton(&this->scrollRegion," ",tmp,0);
    this->scrollRegion.setPrivateMouseOver(0);
    this->scrollRegion.bMouseOver = true;
    this->scrollRegion.bPaintRequest = true;

    tmp.x = x + w/2 - Scrollbar::NormalPositionWidth/2;
    tmp.y = y;
    tmp.w = Scrollbar::NormalPositionWidth;
    tmp.h = h;
    Button::createButton(&this->scrollPosition,"X",tmp,0);
    this->scrollPosition.bMouseOver = false;
    
    this->addEvtTarget(&this->leftBtn);
    this->addEvtTarget(&this->rightBtn);
    //this->addEvtTarget(&this->scrollPosition);
    this->addEvtTarget(&this->scrollRegion);
    
  }
  
/*! \brief show fsgButton on SDL_Surface. Zeichnet den Normalbereich eines Buttons.
 *         
 */
/*  int Scrollbar::show(void * v,SDL_Surface* target)
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
*/
/*
  void Label::setBorder(bool border)
  {
    this->bBorder = border;
  }
*/
}//end namespace
