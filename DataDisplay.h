/*
DataDisplay.h
Bastian Ruppert
07.01.2012
*/

#include <SDL/SDL.h>
#include <SDL/SDL_ttf.h>
#include "Event.h"


namespace EuMax01
{

#ifndef __DATADISPLAY_H__
#define __DATADISPLAY_H__

  class DataDisplay : public EvtTarget
  {
  public:
    DataDisplay(short x,		\
		short y,			\
		unsigned short w,		\
		unsigned short h);
    
    ~DataDisplay();

    int paintData(signed short *data,unsigned int datalen);
    int paintSignedData(signed short *data,unsigned int datalen);
    int paintDoubleMagData(double * data,unsigned int datalen,unsigned int Divisor);
  private:
    SDL_Surface * Surface;
    unsigned int WhatToShow;
    signed short * s16Pnt;
    double * f64Pnt;
    unsigned int s16Len;
    unsigned int DataColor;
    unsigned int BackgroundColor;
  protected:
    int show(SDL_Surface * pSurface);
  };

#endif /* __DATADISPLAY_H__*/
}//end namespace

