/*
Bastian Ruppert
*/

#include "fsgLabel.h"
#include <SDL/SDL_ttf.h>
#include <SDL/SDL_image.h>
#include <stdlib.h>
#include "fsgGlobals.h"
#include "fsgTools.h"

int fsgLabelConstructor(_TfsgLabel * b)
{
  
  if(b->pFont == NULL){
    b->pFont = fsgGlobalGetDefaultFont();
  }
  if(b->pFontColor == NULL){
    b->pFontColor = &GlobalSDL_ColorSewGrau;
  }

  b->EvtTarget.type = FSG_LABEL;              //EvtTarget als LABEL Markieren   
  b->EvtTarget.pTSource = b;                   //Quelle setzen
  b->EvtTarget.pPosDimRect = &b->PosDimRect;   //Position und Dimension der Quelle setzen
  //b->EvtTarget.Private_fnkSelectable=fsgButtonSelect;//Der Button macht Aktion mit dem Selected Bit!
  //b->EvtTarget.pTargetSurface = 0;             //pTargetSurface resetten  
  //fsgLabelSetText(b,b->pLabelText);          //text setzen 
  
  return 0;        //alles OK
}

void fsgLabelSetText(_pTfsgLabel b,const char* text)
{
  b->pLabelText = text;
  b->EvtTarget.bPaintRequest = 1;
}

int fsgLabelShow(_pTfsgLabel b,SDL_Surface* target)
{ 
  int ret;
  
  SDL_Rect tmpRect;
  tmpRect.x = b->PosDimRect.x;
  tmpRect.y = b->PosDimRect.y;
  tmpRect.w = b->PosDimRect.w;
  tmpRect.h = b->PosDimRect.h;

  if(b->pFont == 0)
    return -1;      //Fehler
  if(b->pFontColor==0)
    return -1;      //Fehler

  //if label has Background SDL_Surface, then render Background SDL_Surface, else :
  if(SDL_FillRect(target,&tmpRect,FSG_LABEL_BACKGROUND)){   //Background
    return -1;
  }

  if(b->pLabelText){                                        //Text
    ret=fsgToolsBlitText(target,&tmpRect,b->pFont,b->pFontColor,b->pLabelText);
  }

  if( fsgToolRenderBorderFrame(target,&tmpRect,FSG_COLOR_NORMAL)){//Border
    return -1;
  }

  // SDL_UpdateRect(target,b->PosDimRect.x,b->PosDimRect.y,b->PosDimRect.w,b->PosDimRect.h);
  return 0;
}


