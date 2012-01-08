/*
DataDisplay.cpp
Bastian Ruppert
07.01.2012
*/


#include <SDL/SDL_ttf.h>
#include <SDL/SDL_image.h>
#include <stdlib.h>

#include "Globals.h"
#include "Tools.h"
#include "DataDisplay.h"

namespace EuMax01
{

  DataDisplay::~DataDisplay(){}  

  DataDisplay::DataDisplay(		 short x,	\
					 short y,	\
					 unsigned short w,	\
					 unsigned short h)
  {
    SDL_Rect tmp;
    tmp.x = x;
    tmp.y = y;
    tmp.w = w;
    tmp.h = h;
    this->EvtTargetID = (char *)"DataDisplay";
    this->isVisible = true;
    this->pTSource = this;//Quelle setzen
    this->PosDimRect.x = x;
    this->PosDimRect.y = y;
    this->PosDimRect.w = w;
    this->PosDimRect.h = h;

    this->s16Pnt = 0;
    this->s16Len = 0;

    //Globals* global = Globals::getInstance();
    this->BackgroundColor = Globals::GlobalUint32ColorSewBlau;;
    this->DataColor = Globals::GlobalUint32ColorSewGelb;


    SDL_PixelFormat * format = SDL_GetVideoSurface()->format;
    Surface=SDL_CreateRGBSurface(SDL_SWSURFACE,		\
				 w,			\
				 h,			\
				 FSGDEFAULTCOLORDEPTH,	\
				 format->Rmask,		\
				 format->Gmask,		\
				 format->Bmask,		\
				 format->Amask);
    if(0!=Surface)
      {
	SDL_Rect tmpRect;
	tmpRect.x = 0;
	tmpRect.y = 0;
	tmpRect.w = this->PosDimRect.w;
	tmpRect.h = this->PosDimRect.h;
	SDL_FillRect(this->Surface,&tmpRect,this->BackgroundColor);
      }
  }

/*! \brief show DataDisplay on SDL_Surface.
 *         
 */
  int DataDisplay::show(SDL_Surface* target)
  {
    SDL_Rect tmpRect;
    //int iterations = 0;
    
    tmpRect.x = this->PosDimRect.x;
    tmpRect.y = this->PosDimRect.y;
    tmpRect.w = this->PosDimRect.w;
    tmpRect.h = this->PosDimRect.h;

    //Background
    if(SDL_BlitSurface(Surface,0,target,&tmpRect))
      {
	return -1;
      }

#ifdef FSGPP_SHOW_IMMEDIATELY 
    SDL_UpdateRect(target,tmpRect.x,tmpRect.y,tmpRect.w,tmpRect.h);
#endif
    // SDL_Flip(target);
    return 0;
  }

  int DataDisplay::paintData(signed short * data,unsigned int datalen)
  {

    SDL_Rect tmpRect;
    int iterations = 0;

    this->s16Pnt = data;
    this->s16Len = datalen;
    this->bPaintRequest = true;
    
    tmpRect.x = 0;//this->PosDimRect.x;
    tmpRect.y = 0;//this->PosDimRect.y;
    tmpRect.w = this->PosDimRect.w;
    tmpRect.h = this->PosDimRect.h;

    //Background
    if(SDL_FillRect(this->Surface,&tmpRect,this->BackgroundColor))
      {
	return -1;
      }

    if(this->PosDimRect.w<=this->s16Len)
      iterations = this->PosDimRect.w;
    else
      iterations = this->s16Len;
    tmpRect.w=1;

    for(int i =0;i<iterations;i++)
      {
	tmpRect.x=i;//this->PosDimRect.x+i;
	tmpRect.h=this->s16Pnt[i];
	if(SDL_FillRect(Surface,&tmpRect,this->DataColor))
	  {
	    return -1;
	  }
      }
    return 0;

	  /* NormalView
	  tmpRect.y=this->PosDimRect.y+(this->PosDimRect.h/2);
	  for(int i =0;i<iterations;i++)
	    {
	      tmpRect.x=this->PosDimRect.x+i;
	      tmpRect.h=this->s16Pnt[i];
	      if(SDL_FillRect(target,&tmpRect,this->DataColor))
		{
		  return -1;
		}
		}*/
  }

  int DataDisplay::paintSignedData(signed short * data,unsigned int datalen)
  {

    SDL_Rect tmpRect;
    int iterations = 0;

    this->s16Pnt = data;
    this->s16Len = datalen;
    this->bPaintRequest = true;
    
    tmpRect.x = 0;//this->PosDimRect.x;
    tmpRect.y = 0;//this->PosDimRect.y;
    tmpRect.w = this->PosDimRect.w;
    tmpRect.h = this->PosDimRect.h;

    //Background
    if(SDL_FillRect(this->Surface,&tmpRect,this->BackgroundColor))
      {
	return -1;
      }

    if(this->PosDimRect.w<=this->s16Len)
      iterations = this->PosDimRect.w;
    else
      iterations = this->s16Len;
    tmpRect.w=1;

    tmpRect.y=this->PosDimRect.h/2;
    for(int i =0;i<iterations;i++)
      {
	tmpRect.x=i;
	tmpRect.h=this->s16Pnt[i];
	if(SDL_FillRect(this->Surface,&tmpRect,this->DataColor))
	  {
	    return -1;
	  }
      }
    return 0;
  }
}//end namespace
