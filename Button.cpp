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

  Button::Button(const char * text,SDL_Rect PositionDimRect)
  {
    Globals* global = Globals::getInstance();
    this->pFont = global->getDefaultFont();
    
    this->pFontColor = &global->GlobalSDL_ColorSewGrau;
    
    this->setText(text);          //text setzen 
    this->PrivateShow = Button::show;//EvtTarget als Button Markieren   
    this->pTSource = this;//Quelle setzen
    this->PosDimRect.x = PositionDimRect.x;
    this->PosDimRect.y = PositionDimRect.y;
    this->PosDimRect.w = PositionDimRect.w;
    this->PosDimRect.h = PositionDimRect.h;
    this->pPosDimRect = &this->PosDimRect;   //Position und Dimension der Quelle setzen
    this->PrivateSelectable = Button::select; //Der Button macht Aktion mit dem Selected Bit!
  //b->EvtTarget.pTargetSurface = 0;             //pTargetSurface resetten
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
    if(b->bSelected){
    //if button has Background SDL_Surface, then render Background SDL_Surface, else :
      if(SDL_FillRect(target,&tmpRect,FSG_COLOR_NORMAL)){
	return -1;
    }
  }else{
      if(SDL_FillRect(target,&tmpRect,FSG_COLOR_MARKED)){
	return -1;
      }
    }
    //Text
    if(b->pButtonText){                                        
      if(Tool::blitText(target,&tmpRect,b->pFont,b->pFontColor,b->pButtonText)){
	return -1;
      }
    }
    //Border
    if(b->bSelected){
      if( Tool::renderBorderDown(target,&tmpRect,FSG_COLOR_MARKED)){
	return -1;
      }
      //if(fsgToolRenderBorder(target,&tmpRect,FSG_BOARDERWIDTH,FSG_BOARDERCOLOR_MARKED)){
      //  return -1;
      //}
    }else{
      if( Tool::renderBorderUp(target,&tmpRect,FSG_COLOR_MARKED)){
	return -1;
      }
      //if(fsgToolRenderBorder(target,&tmpRect,FSG_BOARDERWIDTH,FSG_BOARDERCOLOR_NORMAL)){
      //  return -1;
      //}
    }
    //SDL_UpdateRect(target,tmpRect.x,tmpRect.y,tmpRect.w,tmpRect.h);
    // SDL_Flip(target);
    return 0;
  }
  
  /*! \brief private Funktion zum setzen des Selected-Bits
   *
   */
  void Button::select(void * v,bool selected)
  {
    // EvtTarget* t = (EvtTarget)v;
    Button* b =(Button*)v;
    if(selected)
      {
	if(b->fnkSelect){
	  (*b->fnkSelect)(b->pTSource);//execFnk 
	}
      }
  else
    {
      if(b->fnkUnSelect){
	(*b->fnkUnSelect)(b->pTSource);//execFnk 
      }
    }
  b->bPaintRequest = true;
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
