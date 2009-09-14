/*
fsgEvtProcessor.c
Bastian Ruppert
*/

#include "fsgScreen.h"
#include "fsgMain.h"
#include "fsgTypes.h"
#include "fsgTools.h"
#include "fsgGlobals.h"

_pTfsgScreen fsgScreenConstructor(/*_TfsgGUI * GUI,*/int MaxEventTargets){

  if(MaxEventTargets < 0)
    return NULL;

  _pTfsgScreen s = (_pTfsgScreen)malloc(sizeof(_TfsgScreen)); 
  if(s == 0)
    return NULL; 
  
  s->pTargets = fsgEventEvtTargetContainerConstructor(MaxEventTargets);
  if(s->pTargets == NULL){
    goto SCREEN_READY;
  }
  
  s->MaxEvtTargets = MaxEventTargets;
  //  s->pGUI = GUI;
  
  return s;
  
 SCREEN_READY:
  free(s);
  
  return NULL;
}

//void fsgScreenFree(_pTfsgScreen s){
//  free(s)
//}

int fsgScreenAddEvtTarget(_pTfsgScreen theScreen,_pTfsgEvtTarget theTarget){
  if(theScreen == NULL)
    return -1;
  return fsgEventAddEvtTarget(theScreen->pTargets,theTarget);
}


void fsgScreenShow(_pTfsgScreen s, SDL_Surface * pSurface)
{
  int i,tmp;
  if(s==NULL)
    return;

  tmp = s->pTargets->CounterTargets;
  
  i = fsgToolBlankSurface(pSurface,FSG_BACKGROUND);//TODO Rückgabewert
  
  for(i=0;i<tmp;i++){     //alle EventTargets durchlaufen und Anzeigen
    switch(s->pTargets->apEvtTargets[i]->type)
      {
      case FSG_BUTTON:{
	fsgButtonShow((_pTfsgButton)s->pTargets->apEvtTargets[i]->pTSource,pSurface);//TODO Rückgabe
	break;
      }
      case FSG_LABEL:{
	fsgLabelShow((_pTfsgLabel)s->pTargets->apEvtTargets[i]->pTSource,pSurface);//TODO Rückgabe
	break;
      }
      default:{
	break;
      }
    }
  }
}

int fsgScreenAddButton(_pTfsgScreen s, _TfsgButton * btn)
{
  if(fsgButtonConstructor(btn)){
    return -1;
  }
  if(fsgScreenAddEvtTarget(s,&btn->EvtTarget)){
    return -2;
  }
  return 0;
}  

int fsgScreenAddLabel(_pTfsgScreen s, _TfsgLabel * btn)
{
  if(fsgLabelConstructor(btn)){
    return -1;
  }
  if(fsgScreenAddEvtTarget(s,&btn->EvtTarget)){
    return -2;
  }
  return 0;
}  
