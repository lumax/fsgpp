/*
fsgButton.c
Bastian Ruppert
08.05.2009
*/

#include "fsgButton.h"
#include "fsgGlobals.h"
//#include <SDL/SDL_ttf.h>
#include <SDL/SDL_image.h>
#include <stdlib.h>

#include "fsgTools.h"



/*! \brief private Funktion zum setzen des Selected-Bits
 *
 */
static void fsgButtonSelect(void * b,int bool);

int fsgButtonConstructor(_TfsgButton * b)
{
  if(b->pFont == NULL){
    b->pFont = fsgGlobalGetDefaultFont();
  }
  if(b->pFontColor == NULL){
    b->pFontColor = &GlobalSDL_ColorSewGrau;
  }
  
  fsgButtonSetText(b,b->pButtonText);          //text setzen 
  b->EvtTarget.type = FSG_BUTTON;              //EvtTarget als Button Markieren   
  b->EvtTarget.pTSource = b;                   //Quelle setzen
  b->EvtTarget.pPosDimRect = &b->PosDimRect;   //Position und Dimension der Quelle setzen
  b->EvtTarget.Private_fnkSelectable = fsgButtonSelect; //Der Button macht Aktion mit dem Selected Bit!
  //b->EvtTarget.pTargetSurface = 0;             //pTargetSurface resetten
  
  return 0;        //alles OK
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

void fsgButtonSetText(_pTfsgButton b,const char* text)
{
  b->pButtonText = text;
}

int fsgButtonShow(_pTfsgButton b,SDL_Surface* target)
{
  SDL_Rect tmpRect;
  tmpRect.x = b->PosDimRect.x;
  tmpRect.y = b->PosDimRect.y;
  tmpRect.w = b->PosDimRect.w;
  tmpRect.h = b->PosDimRect.h;

  //Background
  if(b->EvtTarget.bSelected){
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
    if(fsgToolsBlitText(target,&tmpRect,b->pFont,b->pFontColor,b->pButtonText)){
      return -1;
    }
  }
  //Border
  if(b->EvtTarget.bSelected){
    if( fsgToolRenderBorderDown(target,&tmpRect,FSG_COLOR_MARKED)){
      return -1;
    }
    //if(fsgToolRenderBorder(target,&tmpRect,FSG_BOARDERWIDTH,FSG_BOARDERCOLOR_MARKED)){
    //  return -1;
    //}
  }else{
    if( fsgToolRenderBorderUp(target,&tmpRect,FSG_COLOR_MARKED)){
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

static void fsgButtonSelect(void * v,int bool)
{
  _pTfsgEvtTarget t = (_pTfsgEvtTarget)v;
  _pTfsgButton b =(_pTfsgButton)t->pTSource;
  if(bool)
    {
      if(b->EvtTarget.fnkSelect){
	(*b->EvtTarget.fnkSelect)(b->EvtTarget.pTSource);//execFnk 
      }
    }
  else
    {
      if(b->EvtTarget.fnkUnSelect){
	(*b->EvtTarget.fnkUnSelect)(b->EvtTarget.pTSource);//execFnk 
      }
    }
  t->bPaintRequest = 1;
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
