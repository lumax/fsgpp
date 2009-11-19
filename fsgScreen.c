/*
fsgEvtProcessor.c
Bastian Ruppert
*/
#include <defs.h>
#include "fsgLL.h"
#include "fsgEvent.h"
#include "fsgTools.h"
#include "fsgGlobals.h"
#include "fsgButton.h"
#include "fsgLabel.h"
#include "fsgCheckBox.h"

#include "fsgScreen.h"

/*_pTfsgScreen fsgScreenConstructor(){

  _pTfsgScreen s = (_pTfsgScreen)malloc(sizeof(_TfsgScreen)); 
  if(s == 0)
    return NULL; 
  s->EvtTargets.Next = 0;
  return s;
  }*/

int fsgScreenAddEvtTarget(_TfsgScreen * theScreen,_pTfsgEvtTarget theTarget){
  if(theScreen == NULL)
    return -1;
  fsgEventAddEvtTarget(&theScreen->EvtTargets,theTarget);
  return 0;
}


int fsgScreenShow(_TfsgScreen * s, SDL_Surface * pSurface)
{
  int i;
  _pTfsgEvtTarget pTmpEvtTarget;
  if(s==NULL)
    {
      errno = EINVAL;
      EC_FAIL;
    }

  i = fsgToolBlankSurface(pSurface,FSG_BACKGROUND);//TODO Rückgabewert
  pTmpEvtTarget = (_pTfsgEvtTarget)s->EvtTargets.Next;
  
  while(pTmpEvtTarget)
    {     //alle EventTargets durchlaufen und Anzeigen
      if(pTmpEvtTarget->PrivateShow)
	{
	  ec_neg1(pTmpEvtTarget->PrivateShow(pTmpEvtTarget->pTSource,\
					     pSurface) )
	}
      pTmpEvtTarget = (_pTfsgEvtTarget)pTmpEvtTarget->TfsgLL.Next;
    }
      return 0;
  EC_CLEANUP_BGN
    return -1;
  EC_CLEANUP_END
}

int fsgScreenAddButton(_TfsgScreen * s, _TfsgButton * btn)
{
  if(fsgButtonConstructor(btn)){
    return -1;
  }
  if(fsgScreenAddEvtTarget(s,&btn->EvtTarget)){
    return -1;
  }
  return 0;
}  

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

/* \brief Adds a CheckBox to the Screen and calls the CB Constructor
 * \param s The target Screen
 * \param pEvtTarget The object to put to screen
 * \return 0 on success, -1 on error
 */
int fsgScreenAddCheckBox(_TfsgScreen * s,\
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

