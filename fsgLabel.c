/*
Bastian Ruppert
*/

#include "fsgLabel.h"
#include <SDL/SDL_ttf.h>
#include <SDL/SDL_image.h>
#include <stdlib.h>
#include <defs.h>
#include "fsgGlobals.h"
#include "fsgTools.h"


/*! \brief show fsgButton on SDL_Surface. Zeichnet den Normalbereich eines Buttons.
 *         
 */
static int fsgLabelShow(void * pL,SDL_Surface * pSurface);

int fsgLabelConstructor(_TfsgLabel * b)
{
  
  if(b->pFont == NULL){
    b->pFont = fsgGlobalGetDefaultFont();
  }
  if(b->pFontColor == NULL){
    b->pFontColor = &GlobalSDL_ColorSewGrau;
  }

  b->EvtTarget.PrivateShow = fsgLabelShow;//LabelShowfunktion setzen  
  b->EvtTarget.pTSource = b;                   //Quelle setzen
  b->EvtTarget.pPosDimRect = &b->PosDimRect;   //Position und Dimension der Quelle setzen
  return 0;        //alles OK
}

void fsgLabelSetText(_pTfsgLabel b,const char* text)
{
  b->pLabelText = text;
  b->EvtTarget.bPaintRequest = 1;
}

static int fsgLabelShow(void * v,SDL_Surface* target)
{ 
  int ret;
  SDL_Rect tmpRect;
  _pTfsgLabel b = (_pTfsgLabel)v;
  tmpRect.x = b->PosDimRect.x;
  tmpRect.y = b->PosDimRect.y;
  tmpRect.w = b->PosDimRect.w;
  tmpRect.h = b->PosDimRect.h;

  if(b->pFont == 0)
    EC_FAIL;      //Fehler
  if(b->pFontColor==0)
    EC_FAIL;      //Fehler

  //if label has Background SDL_Surface, then render Background SDL_Surface, else :
  ec_neg1(SDL_FillRect(target,&tmpRect,FSG_LABEL_BACKGROUND))//Background
  if(b->pLabelText){                                        //Text
    ret=fsgToolsBlitText(target,&tmpRect,b->pFont,b->pFontColor,b->pLabelText);
  }

  if( fsgToolRenderBorderFrame(target,&tmpRect,FSG_COLOR_NORMAL)){//Border
    EC_FAIL;
  }

  // SDL_UpdateRect(target,b->PosDimRect.x,b->PosDimRect.y,b->PosDimRect.w,b->PosDimRect.h);
  return 0;
  EC_CLEANUP_BGN
    return -1;
  EC_CLEANUP_END
}


