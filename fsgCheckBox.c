/*
fsgCheckBox.c
Bastian Ruppert
17.11.2009
*/
#include <SDL/SDL_image.h>
#include <SDL/SDL.h>
#include <defs.h>
#include "fsgTools.h"
#include "fsgGlobals.h"
#include "fsgEvent.h"
#include "fsgCheckBox.h"

static int CheckBoxShow(void * pB,SDL_Surface * pSurface);

//static void CheckBoxSelect(void * b,int boolean);

static void CheckBoxLMBUp(SDL_Event * theEvent,void * source);

/* \brief Initialisiert die Instanz der CheckBox
 * \param pCB The target to construct
 * \param checked CheckBox initial value
 * \return 0 on success, -1 on error, errno is set
 * \retval 0 OK
 * \retval -1 errno =EINVAL: pCB->fnkCustomLeftMouseButtonUp is set, set customLeftMouseUp in EvtTarget!
 */
int fsgCheckBoxConstructor(_TfsgCheckBox * pCB,\
			   const int checked)
{
  if(pCB->PrivateCustomLeftMouseButtonUp)
    {
      errno = EINVAL;
      EC_FAIL;
    } 
  if(pCB->EvtTarget.fnkLeftMouseButtonUp)//custom Fnk sichern
    {
      pCB->PrivateCustomLeftMouseButtonUp = pCB->EvtTarget.fnkLeftMouseButtonUp;
    }
  pCB->EvtTarget.fnkLeftMouseButtonUp = CheckBoxLMBUp; 
  pCB->EvtTarget.PrivateShow = CheckBoxShow; //CheckBox Show Fnk setzen    
  pCB->EvtTarget.pTSource = pCB;     //Quelle setzen
  pCB->EvtTarget.pPosDimRect = &pCB->PosDimRect;   //Position und Dimension der Quelle setzen
  //pCB->EvtTarget.Private_fnkSelectable = CheckBoxSelect; //Der Button macht Aktion mit dem Selected Bit!
  
  if(checked)
    {
      pCB->bChecked = 1;
    }
  else
    {
      pCB->bChecked = 0;
    }
  return 0;        //alles OK
  EC_CLEANUP_BGN
    return -1;
  EC_CLEANUP_END
}

/* \brief On LeftMouseBUp, CheckBox is checked (or unchecked)
 * \param source The CheckBox
 * If the User left a custom LMBU_Event function, the User-Function 
 * will be executed. 
 */
static void CheckBoxLMBUp(SDL_Event * theEvent,void * source)
{
  _TfsgCheckBox * pCB = (_TfsgCheckBox *)source;
  if(pCB->bChecked)
    {
      fsgCheckBoxCheck(pCB,0);
    }
  else
    {
      fsgCheckBoxCheck(pCB,1);
    }
  if(pCB->PrivateCustomLeftMouseButtonUp)
    {
      pCB->PrivateCustomLeftMouseButtonUp(theEvent,source);
    }
}

/* \brief check or uncheck the CheckBox 
 * \param pCB The CheckBox
 * \param check 0 = uncheck, !=0 check
 */
void fsgCheckBoxCheck(_TfsgCheckBox * pCB,const int check)
{
  if(check)
    {
      pCB->bChecked = 1;
    }
  else
    {
      pCB->bChecked = 0;
    }
  pCB->EvtTarget.bPaintRequest = 1;
  if(pCB->fnkStatusChanged)  //call event function
    {
      pCB->fnkStatusChanged((void*)pCB,pCB->bChecked);
    }
}

/* \brief toggle status of the CheckBox 
 * \param pCB The CheckBox
 * \param check 0 = uncheck, !=0 check
 */
void fsgCheckBoxToggle(_TfsgCheckBox * pCB)
{
  if(pCB->bChecked)
    {
      fsgCheckBoxCheck(pCB,0);
    }
  else
    {
      fsgCheckBoxCheck(pCB,1);
    }
}

/* \brief returns the status of the CheckBox 
 * \param pCB The CheckBox
 * \return checked = 1, unchecked = 0
 */
int fsgCheckBoxGetStatus(_TfsgCheckBox * pCB)
{
  return pCB->bChecked;
}

/* \brief Prints the CheckBox
 * \param obj The EvtTarget Object
 * \param target Surface where to print to
 * \return 0 on success, -1 on error
 * \retval 0 OK
 * \retval -1 on fatal error (from SDL)
 */
static int CheckBoxShow(void * obj,SDL_Surface* target)
{
  SDL_Rect tmpRect;
  _TfsgCheckBox * b =(_TfsgCheckBox *)obj;
  tmpRect.x = b->PosDimRect.x;
  tmpRect.y = b->PosDimRect.y;
  tmpRect.w = b->PosDimRect.w;
  tmpRect.h = b->PosDimRect.h;

  //Background
  if(b->bChecked)
    {
      //if button has Background SDL_Surface, then render Background SDL_Surface, else :
      ec_neg1(SDL_FillRect(target,&tmpRect,FSG_COLOR_NORMAL))
    }
  else
    {
      ec_neg1(SDL_FillRect(target,&tmpRect,FSG_COLOR_MARKED))
    }
 
  //Border
  if(b->bChecked)
    {
    ec_neg1(fsgToolRenderBorderDown(target,\
				    &tmpRect,\
				    FSG_COLOR_MARKED))
    //if(fsgToolRenderBorder(target,&tmpRect,FSG_BOARDERWIDTH,FSG_BOARDERCOLOR_MARKED)){
    //  return -1;
    //}
   }
  else
   {
    ec_neg1( fsgToolRenderBorderUp(target,\
				   &tmpRect,\
				   FSG_COLOR_MARKED))
    //if(fsgToolRenderBorder(target,&tmpRect,FSG_BOARDERWIDTH,FSG_BOARDERCOLOR_NORMAL)){
    //  return -1;
    //}
   }
  return 0;
  EC_CLEANUP_BGN
    return -1;
  EC_CLEANUP_END
}
