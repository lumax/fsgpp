/*
Bastian Ruppert
*/

namespace EuMax01
{

#ifndef __FSGSCREEN_H__
#define __FSGSCREEN_H__

  class Screen : public EvtTarget
{
 public:
  Screen();
  int show(SDL_Surface * pSurface);
  void addEvtTarget(EvtTarget * theTarget);
  EvtTarget EvtTargets;
  int addButton(Button * btn);
  
  //extern int fsgScreenAddLabel(_TfsgScreen * s, _TfsgLabel * pL);
  /*extern int fsgScreenAddCheckBox(_TfsgScreen * s,		\
    _TfsgCheckBox * pEvtTar,
    int checked);*/
  void (*OnActivate)(void);
  void (*OnDeactivate)(void);
 private:
};


#endif /* __FSGSCREEN_H__*/
}//end namespace
