/*
Bastian Ruppert
*/
#include <SDL/SDL_ttf.h>
#include "LL.h"
#include "Event.h"
#include "Tools.h"
#include "Globals.h"
#include "Button.h"
//#include "fsgLabel.h"
//#include "fsgCheckBox.h"

#include "Screen.h"

namespace EuMax01
{

  Screen::Screen()
  {
    OnActivate=0;
    OnDeactivate=0;
    //EvtTargets nullen!
    char * pcTmp = (char *)&this->EvtTargets;
    for(unsigned int i=0;i<sizeof(EvtTarget);i++)
      {
	*pcTmp=0;
	pcTmp++;
      }
  }
  
  void Screen::addEvtTarget(EvtTarget * theTarget)
  {
    this->EvtTargets.addLL(theTarget);
  }
  
  int Screen::show(SDL_Surface * pSurface)
  {
    int i;
    EvtTarget * pTmpEvtTarget;
    //Globals * pGlobals = Globals::getInstance();
    i = Tool::blankSurface(pSurface,FSG_BACKGROUND);//TODO Rückgabewert
    pTmpEvtTarget = (EvtTarget*)this->EvtTargets.Next;
    
    while(pTmpEvtTarget)
    {     //alle EventTargets durchlaufen und Anzeigen
      if(pTmpEvtTarget->PrivateShow&&!pTmpEvtTarget->bHide)
	{
	  if(pTmpEvtTarget->PrivateShow(pTmpEvtTarget->pTSource,pSurface) )
	return -1;
    }
    pTmpEvtTarget = (EvtTarget*)pTmpEvtTarget->Next;
  }
  return 0;
}

  /* void Screen::addButton(Button * btn)
  {
    if(fsgButtonConstructor(btn)){
      return -1;
    }
    if(fsgScreenAddEvtTarget(s,&btn->EvtTarget)){
      return -1;
    }
    return 0;
    }  */
  /*
int fsgScreenAddLabel(_TfsgScreen * s, _TfsgLabel * btn)
{
  if(fsgLabelConstructor(btn)){
    return -1;
  }
  if(fsgScreenAddEvtTarget(s,&btn->EvtTarget)){
    return -1;
  }
  return 0;
} 
*/
/* \brief Adds a CheckBox to the Screen and calls the CB Constructor
 * \param s The target Screen
 * \param pEvtTarget The object to put to screen
 * \return 0 on success, -1 on error
 */
/*int fsgScreenAddCheckBox(_TfsgScreen * s,		\
			 _TfsgCheckBox * pEvtTar,\
			 int checked)
{
  ec_neg1( fsgCheckBoxConstructor(pEvtTar,checked) )

  ec_neg1( fsgScreenAddEvtTarget(s,&pEvtTar->EvtTarget) )

  return 0;
  EC_CLEANUP_BGN
    return -1;
  EC_CLEANUP_END
}
*/
}
