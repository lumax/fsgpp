/*
fsgCheckBox.h
Bastian Ruppert
17.11.2009
*/

#ifndef __fsgCheckBox_h__
#define __fsgCheckBox_h__

typedef struct
{
  _TfsgEvtTarget EvtTarget;
  SDL_Rect PosDimRect;
  int bChecked;
  void (*fnkStatusChanged)(void * source,int newStatus);
  void (*PrivateCustomLeftMouseButtonUp)(SDL_Event * theEvent,\
					     void * source);
}_TfsgCheckBox;

extern int fsgCheckBoxConstructor(_TfsgCheckBox * b,\
				  const int checked);

extern void fsgCheckBoxCheck(_TfsgCheckBox * pCB,const int check);
extern void fsgCheckBoxToggle(_TfsgCheckBox * pCB);
extern int fsgCheckBoxGetStatus(_TfsgCheckBox * pCB);

#endif /* __fsgCheckBox_h__ */
