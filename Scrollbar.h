/*
Scrollbar.h
Bastian Ruppert
*/

#include <SDL/SDL.h>
#include <SDL/SDL_ttf.h>
#include "Event.h"


namespace EuMax01
{

#ifndef __FSGSCROLLBAR_H__
#define __FSGSCROLLBAR_H__

  class Scrollbar : public EvtTarget
  {
  public:
    Scrollbar(int maxValue,			\
	      int minValue,			\
	      int actualValue,			\
	      short x,				\
	      short y,				\
	      unsigned short w,			\
	      unsigned short h);
    
    //void setBorder(bool border);
    //int show(void * v,SDL_Surface* target);
  protected:
    bool bBorder;
  public:
    static const unsigned short NormalWidth = 20;//Breite der Links- und Rechtsbuttons
    static const unsigned short NormalPositionWidth = 10;//Breite des Positionsbuttons
    unsigned short w;
    unsigned short h;
    //    Left; Region;   Position;   Right 
    //    |__|<____________|  |_____>|__|
    Button leftBtn;
    Button rightBtn;
    Button scrollRegion;
    Button scrollPosition;
  };

#endif /* __FSGSCROLLBAR_H__*/
}//end namespace

