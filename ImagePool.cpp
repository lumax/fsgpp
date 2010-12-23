
#include <SDL/SDL.h>
#include <SDL/SDL_image.h>
#include <SDL/SDL_ttf.h> /*for Globals.h*/
#include "Globals.h"

#include "ImagePool.h"

namespace EuMax01
{

  ImagePool::ImagePool()
  {
    //clear memory
    char * pv = (char*)this;
    for(unsigned int i=0; i<sizeof(ImagePool);i++)
      {
	*pv = 0;
	pv++;
      }
    this->stdBtnIsSet = false;
  }

  SDL_Surface * ImagePool::getStdBtnNormal()
  {
    return this->stdBtnNormal;
  }

  SDL_Surface * ImagePool::getStdBtnMarked()
  {
    return this->stdBtnMarked;
  }

  int ImagePool::setStdButton(const char * pathNormalLeft,	\
			      const char * pathNormalMiddle,	\
			      const char * pathNormalRight,	\
			      const char * pathMarkedLeft,	\
			      const char * pathMarkedMiddle,	\
			      const char * pathMarkedRight,	\
			      unsigned short width,		\
			      unsigned short height)
  {
    SDL_Surface * tmp = 0; 
    SDL_Rect tmpRect;
    SDL_Rect tmpDestRect;
    SDL_PixelFormat * format = SDL_GetVideoSurface()->format;
    SDL_Surface * surfaceArray[6] = {0,0,0,0,0,0};
    const char * pathArray[6] = {pathNormalLeft,	\
				 pathNormalMiddle,	\
				 pathNormalRight,	\
				 pathMarkedLeft,	\
				 pathMarkedMiddle,\
				 pathMarkedRight}; 
    if(this->stdBtnIsSet)//busy
      {
	return -2;
      }
      
    for(int i=0;i<6;i++)
      {
	tmp = IMG_Load(pathArray[i]);
	if(!tmp)
	  {
	    goto loadingImagesReady;
	  }
	surfaceArray[i] = SDL_DisplayFormatAlpha(tmp);
	SDL_FreeSurface(tmp);
	if(!surfaceArray[i])
	  {
	    goto loadingImagesReady;
	  }
      }
    if(this->stdBtnNormal)
      {
	SDL_FreeSurface(this->stdBtnNormal);
      }

    if(this->stdBtnMarked)
      {
	SDL_FreeSurface(this->stdBtnMarked);
      }
    
    tmp=SDL_CreateRGBSurface(SDL_SWSURFACE,				\
			     width,					\
			     height,					\
			     FSGDEFAULTCOLORDEPTH,			\
			     format->Rmask,				\
			     format->Gmask,				\
			     format->Bmask,				\
			     format->Amask);    
    if(!tmp)
      {
	goto  loadingImagesReady;
      }
    
    this->stdBtnNormal = SDL_DisplayFormatAlpha(tmp);
    if(!this->stdBtnNormal)
      {
	SDL_FreeSurface(tmp);
	goto  loadingImagesReady;
      }
    
    this->stdBtnMarked = SDL_DisplayFormatAlpha(tmp);
    if(!this->stdBtnMarked)
      {
	SDL_FreeSurface(tmp);
	goto stdBtnNormalReady;
      }
    SDL_FreeSurface(tmp);
    

    //Background Normal & Background Marked
    tmpRect.x = 0;
    tmpRect.y = 0;
    tmpRect.w = 1;
    tmpRect.h = height;

    tmpDestRect.x = surfaceArray[0]->w;
    tmpDestRect.y = 0;
    tmpDestRect.w = 1;
    tmpDestRect.h = height;
    for(int i=0;i<width-(surfaceArray[0]->w+surfaceArray[2]->w);i++)
      {
	if(SDL_BlitSurface(surfaceArray[1],&tmpRect,	\
			   this->stdBtnNormal,&tmpDestRect)	\
	   )
	  {
	    goto stdBtnMarkedReady;
	  }
	if(SDL_BlitSurface(surfaceArray[4],&tmpRect,		\
			   this->stdBtnMarked,&tmpDestRect)	\
	   )
	  {
	    goto stdBtnMarkedReady;
	  }	
	tmpDestRect.x++;
      }
	  
    //Left Normal
    tmpDestRect.x = 0;
    tmpDestRect.y = 0;
    tmpDestRect.w = surfaceArray[0]->w;
    tmpDestRect.h = surfaceArray[0]->h;
    if(SDL_BlitSurface(surfaceArray[0],0,			\
		       this->stdBtnNormal,&tmpDestRect)		\
       )
      {
	goto stdBtnMarkedReady;
      }

   //Left Marked
    tmpDestRect.x = 0;
    tmpDestRect.y = 0;
    tmpDestRect.w = surfaceArray[3]->w;
    tmpDestRect.h = surfaceArray[3]->h;
    if(SDL_BlitSurface(surfaceArray[3],&tmpRect,		\
		       this->stdBtnMarked,&tmpDestRect)		\
       )
      {
	goto stdBtnMarkedReady;
      }	

	  //right normal
    tmpDestRect.x = width - surfaceArray[2]->w;
    tmpDestRect.y = 0;
    tmpDestRect.w = surfaceArray[2]->w;
    tmpDestRect.h = surfaceArray[2]->h;
    if(SDL_BlitSurface(surfaceArray[2],0,			\
		       this->stdBtnNormal,&tmpDestRect)		\
       )
      {
	goto stdBtnMarkedReady;
      }

    //right marked
    tmpDestRect.x = width - surfaceArray[5]->w;
    tmpDestRect.y = 0;
    tmpDestRect.w = surfaceArray[5]->w;
    tmpDestRect.h = surfaceArray[5]->h;
    if(SDL_BlitSurface(surfaceArray[5],0,			\
		       this->stdBtnMarked,&tmpDestRect)		\
       )
      {
	goto stdBtnMarkedReady;
      }
    
    tmp = this->stdBtnNormal;
    this->stdBtnNormal = SDL_DisplayFormatAlpha(tmp);
    if(!this->stdBtnNormal)
      {
	SDL_FreeSurface(tmp);
	goto stdBtnMarkedReady;
      }
    SDL_FreeSurface(tmp);
    
    tmp = this->stdBtnMarked;
    this->stdBtnMarked = SDL_DisplayFormatAlpha(tmp);
    if(!this->stdBtnMarked)
      {
	SDL_FreeSurface(tmp);
	goto stdBtnMarkedReady;
      }
    SDL_FreeSurface(tmp);    
    
    this->stdBtnWidth = width;
    this->stdBtnHeight = height;
    this->stdBtnIsSet = true;
	return 0;
	
  stdBtnMarkedReady:
    SDL_FreeSurface(stdBtnMarked);
  stdBtnNormalReady:
	  SDL_FreeSurface(stdBtnNormal);
    loadingImagesReady:
	  SDL_FreeSurface(tmp);
	for(int ii=0;ii<6;ii++)
	  {
	    SDL_FreeSurface(surfaceArray[ii]);
	  }
    return -1; 
  }
}
