#ifndef __FSGLL_H__
#define __FSGLL_H__
/*
 Version 1.0
 */

typedef struct _T_fsgLL_Item
{
  struct _T_fsgLL_Item * Next;
  //struct _T_fsgLL_Item * Prev;
  int data;
}_TfsgLL,*_pTfsgLL;

/*! /brief fügt dem Target das Item hinzu
 */
extern void fsgLLAdd(_pTfsgLL pTarget,_pTfsgLL pItem);
#endif /*__FGSLL_H__*/
