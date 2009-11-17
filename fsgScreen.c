/*
fsgEvtProcessor.c
Bastian Ruppert
*/

#include "fsgScreen.h"
#include "fsgMain.h"
#include "fsgTypes.h"
#include "fsgTools.h"
#include "fsgGlobals.h"

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


void fsgScreenShow(_TfsgScreen * s, SDL_Surface * pSurface)
{
  int i;
  _pTfsgEvtTarget pTmpEvtTarget;
  if(s==NULL)
    return;

  i = fsgToolBlankSurface(pSurface,FSG_BACKGROUND);//TODO Rückgabewert
  pTmpEvtTarget = (_pTfsgEvtTarget)s->EvtTargets.Next;
  
  while(pTmpEvtTarget)
    {     //alle EventTargets durchlaufen und Anzeigen
      switch(pTmpEvtTarget->type)
	{
	case FSG_BUTTON:
	  {
	    fsgButtonShow((_pTfsgButton)pTmpEvtTarget->pTSource,pSurface);//TODO Rückgabe
	    break;
	  }
	case FSG_LABEL:
	  {
	    fsgLabelShow((_pTfsgLabel)pTmpEvtTarget->pTSource,pSurface);//TODO Rückgabe
	    break;
	  }
	default:
	  {
	    break;
	  }
	}
      pTmpEvtTarget = (_pTfsgEvtTarget)pTmpEvtTarget->TfsgLL.Next;
    }
}

int fsgScreenAddButton(_TfsgScreen * s, _TfsgButton * btn)
{
  if(fsgButtonConstructor(btn)){
    return -1;
  }
  if(fsgScreenAddEvtTarget(s,&btn->EvtTarget)){
    return -2;
  }
  return 0;
}  

int fsgScreenAddLabel(_TfsgScreen * s, _TfsgLabel * btn)
{
  if(fsgLabelConstructor(btn)){
    return -1;
  }
  if(fsgScreenAddEvtTarget(s,&btn->EvtTarget)){
    return -2;
  }
  return 0;
}  
