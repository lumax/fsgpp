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

namespace EuMax01
{

  ButtonSettings::ButtonSettings(TTF_Font* Font,		\
				 SDL_Color * FontColor,		\
				 unsigned int NormalColor,	\
				 unsigned int MarkedColor)
  {
    this->Font = Font;
    this->Color = FontColor;
    this->NormalColor = NormalColor;
    this->MarkedColor = MarkedColor;
  }

  ButtonSettings::~ButtonSettings()
  {}

  TTF_Font * ButtonSettings::getFont()
  {
    return this->Font;
  }

  SDL_Color * ButtonSettings::getFontColor()
  {
    return this->Color;
  }

  unsigned int ButtonSettings::getNormalColor()
  {
    return this->NormalColor;
  }

  unsigned int ButtonSettings::getMarkedColor()
  {
    return this->MarkedColor;
  }

  Button::Button(const char * text,SDL_Rect PositionDimRect)
  {
    Button::createButton(this,text,PositionDimRect,0);
  }
  
  Button::Button(const char * text,			\
		 short x,				\
		 short y,				\
		 unsigned short w,			\
		 unsigned short h)
  {
    SDL_Rect tmp;
    tmp.x = x;
    tmp.y = y;
    tmp.w = w;
    tmp.h = h;
    Button::createButton(this,text,tmp,0);
  }

  Button::Button(const char * text,			\
		 short x,				\
		 short y,				\
		 unsigned short w,			\
		 unsigned short h,			\
		 ButtonSettings * settings)
  {
    SDL_Rect tmp;
    tmp.x = x;
    tmp.y = y;
    tmp.w = w;
    tmp.h = h;
    Button::createButton(this,text,tmp,settings);
  }
  
  void Button::createButton(Button* b,			\
			    const char * text,		\
			    SDL_Rect PositionDimRect,	\
			    ButtonSettings * settings)
  {
    if(settings)
      {
	b->setFont(settings->getFont());
	b->setFontColor(settings->getFontColor());
	b->setNormalColor(settings->getNormalColor());
	b->setMarkedColor(settings->getMarkedColor());
      }
    else
      {
	Globals* global = Globals::getInstance();
	b->pFont = global->getDefaultFont();
	b->pFontColor = &global->GlobalSDL_ColorNearlyBlack;
	b->setMarkedColor(Globals::GlobalUint32ColorLightGray);
	b->setNormalColor(Globals::GlobalUint32Color2);
      }

    b->setText(text);          //text setzen 
    b->PrivateShow = Button::show;//EvtTarget als Button Markieren   
    b->pTSource = b;//Quelle setzen
    b->PosDimRect.x = PositionDimRect.x;
    b->PosDimRect.y = PositionDimRect.y;
    b->PosDimRect.w = PositionDimRect.w;
    b->PosDimRect.h = PositionDimRect.h;
    b->PrivateMouseOver = Button::mouseOverEvent;//Der Button macht Aktion mit dem MouseOverBit!
    b->pNormalSurface = 0;
    b->pMarkedSurface = 0;
  }

  /* \brief Button is decorated by images and
   * \brief width and heigth set by constructor 
   * \param normal repräsentiert den Normal-Zustand
   * \param down repräsentiert den Pressed-Zustand
   * \return 0 on success, -1 on error loading images
   */
  int Button::setImages(const char* normal,const char* down)
  {
    SDL_Surface * tmp = 0;
    //normal
    tmp = IMG_Load(normal);
    if(!tmp)
      {
	return -1;
      }
    this->pNormalSurface = SDL_DisplayFormatAlpha(tmp);
    if(!this->pNormalSurface)
      {
	SDL_FreeSurface(tmp);
	return -1;
      }
    SDL_FreeSurface(tmp);

    //marked
    tmp = 0;
    tmp = IMG_Load(down);
    if(!tmp)
      {
	goto NormalSurfaceOK;
      }
    this->pMarkedSurface = SDL_DisplayFormatAlpha(tmp);
    if(!this->pMarkedSurface)
      {
	SDL_FreeSurface(tmp);
	goto NormalSurfaceOK;
      }
    SDL_FreeSurface(tmp);
    this->PrivateShow = Button::showImages;
    return 0;
  NormalSurfaceOK:
    SDL_FreeSurface(this->pNormalSurface);
    return -1;
  }

  /* \brief Button is decorated by images and
   * \param normal repräsentiert den Normal-Zustand
   * \param down repräsentiert den Pressed-Zustand
   */
  void Button::setImages(SDL_Surface* normal,	\
			 SDL_Surface* down)
  {
    //normal
    //this->pNormalSurface  = SDL_DisplayFormatAlpha(normal);
    this->pNormalSurface = normal;

    //marked
    //this->pMarkedSurface = SDL_DisplayFormatAlpha(down);
    this->pMarkedSurface = down;

    this->PrivateShow = Button::showImages;
  }

  void Button::setFont(TTF_Font* font)
  {
    if(font)
      this->pFont = font; 
  }

  void Button::setFontColor(SDL_Color * pColor)
  {
    if(pColor)
      this->pFontColor = pColor;
  }

/*void sdlBtn_destructor(_pTsdlButton b)
{
  if(b==NULL)
    return;
  // if(b->pvEventContainer)
  //  {
  //    sdlBtn_removeEvent((_pTsdlButtonEventContainer)b->pvEventContainer,b);
  //  }
  
  
  SDL_FreeSurface(b->pBitmapNormal);
  SDL_FreeSurface(b->pBitmapMarked);
  free(b->pEvtTarget);
  free(b);
  }*/

void Button::setText(const char* text)
{
  this->pButtonText = text;
  this->bPaintRequest = true;
}
  
  int Button::showImages(void * v,SDL_Surface* target)
  {
    SDL_Rect tmpRect;
    Button* b =(Button*)v;
    SDL_Surface* tmpSurface;
    
    tmpRect.x = b->PosDimRect.x;
    tmpRect.y = b->PosDimRect.y;
    tmpRect.w = b->PosDimRect.w;
    tmpRect.h = b->PosDimRect.h;

    //Background
    if(b->bSelectedByMouseDown)
      {
	tmpSurface = b->pMarkedSurface;
      }
    else
      {
	tmpSurface = b->pNormalSurface;
      }

    if(SDL_BlitSurface(tmpSurface,0,target,&tmpRect))
      {
	return -1;
      }

    //Text
    if(b->pButtonText){                                        
      if(Tool::blitText(target,&tmpRect,b->pFont,b->pFontColor,b->pButtonText)){
	return -1;
      }
    }
#ifdef FSGPP_SHOW_IMMEDIATELY 
    SDL_UpdateRect(target,tmpRect.x,tmpRect.y,tmpRect.w,tmpRect.h);
#endif
    return 0;
  }
  
/*! \brief show fsgButton on SDL_Surface. Zeichnet den Normalbereich eines Buttons.
 *         
 */
  int Button::show(void * v,SDL_Surface* target)
  {
    SDL_Rect tmpRect;
    Button* b =(Button*)v;
    
    tmpRect.x = b->PosDimRect.x;
    tmpRect.y = b->PosDimRect.y;
    tmpRect.w = b->PosDimRect.w;
    tmpRect.h = b->PosDimRect.h;

    //Background
    if(b->bSelectedByMouseDown){
    //if button has Background SDL_Surface, then render Background SDL_Surface, else :
      if(SDL_FillRect(target,&tmpRect,b->uiNormalColor)){
	return -1;
    }
  }else{
      if(SDL_FillRect(target,&tmpRect,b->uiMarkedColor)){
	return -1;
      }
    }
    //Text
    if(b->bSelectedByMouseDown)
      {
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
      }
    else
      {
	if(b->pButtonText)
	  {
	    if(Tool::blitText(target,&tmpRect,b->pFont,b->pFontColor,b->pButtonText)){
	      return -1;
	    }
	  }
      }

    //Border
    if(b->bSelectedByMouseDown){
      if( Tool::renderBorderDown(target,&tmpRect,b->uiNormalColor)){
	return -1;
      }
      //if(fsgToolRenderBorder(target,&tmpRect,FSG_BOARDERWIDTH,FSG_BOARDERCOLOR_MARKED)){
      //  return -1;
      //}
    }else{
      if( Tool::renderBorderUp(target,&tmpRect,b->uiMarkedColor)){
	return -1;
      }
    }
#ifdef FSGPP_SHOW_IMMEDIATELY 
    SDL_UpdateRect(target,tmpRect.x,tmpRect.y,tmpRect.w,tmpRect.h);
#endif
     // SDL_Flip(target);
    return 0;
  }
  
  /*! \brief private Funktion zum setzen des Selected-Bits
   *
   */
  void Button::mouseOverEvent(void * v,bool MouseOver)
  {
    // EvtTarget* t = (EvtTarget)v;
    Button* b =(Button*)v;
    if(MouseOver)
      {
	if(b->fnkMouseOverEvt){
	  (*b->fnkMouseOverEvt)(b->pTSource);//execFnk 
	}
      }
  else
    {
      if(b->fnkMouseNotOverEvt){
	(*b->fnkMouseNotOverEvt)(b->pTSource);//execFnk 
      }
    }
    b->bPaintRequest = true;
  }

  void Button::setNormalColor(unsigned int c)
  {
    uiNormalColor = c;
  }

  void Button::setMarkedColor(unsigned int c)
  {
    uiMarkedColor = c;
  }

 /* //SDL_Surface Konstruktion
  r.x = 0;
  r.y = 0;
  r.w = b->PosDimRect.w;
  r.h = b->PosDimRect.h;

  SDL_PixelFormat * format = SDL_GetVideoSurface()->format;
  b->pNormalSurface=SDL_CreateRGBSurface(SDL_SWSURFACE,			\
					 b->PosDimRect.w,		\
					 b->PosDimRect.h,		\
					 FSGDEFAULTCOLORDEPTH,		\
					 format->Rmask,			\
					 format->Gmask,			\
					 format->Bmask,			\
					 format->Amask); 
  if(b->pNormalSurface == NULL) 
    return -1;
 
  
  if(SDL_FillRect(b->pNormalSurface,&r,FSG_COLOR_NORMAL))
    goto NormalSurfaceReady;
  if(fsgToolRenderBorder(b->pNormalSurface,&r,FSG_BOARDERWIDTH,FSG_BOARDERCOLOR_NORMAL))
    goto NormalSurfaceReady;
  
  b->pMarkedSurface=SDL_CreateRGBSurface(SDL_SWSURFACE,			\
					 b->PosDimRect.w,		\
					 b->PosDimRect.h,		\
					 FSGDEFAULTCOLORDEPTH,		\
					 format->Rmask,			\
					 format->Gmask,			\
					 format->Bmask,			\
					 format->Amask);   
  if(b->pMarkedSurface == NULL) 
    goto NormalSurfaceReady;
  if(SDL_FillRect(b->pMarkedSurface,&r,FSG_COLOR_MARKED))
    goto MarkedSurfaceReady;
  if(fsgToolRenderBorder(b->pMarkedSurface,&r,FSG_BOARDERWIDTH,FSG_BOARDERCOLOR_MARKED))
    goto MarkedSurfaceReady;
 */
}//end namespace
