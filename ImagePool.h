/*
ImagePool.h
Bastian Ruppert
23.12.2010
*/

namespace EuMax01
{

#ifndef __FSGIMAGEPOOL_H__
#define __FSGIMAGEPOOL_H__

  class ImagePool
  {
  public:
    ImagePool();
    int setStdButton(const char * pathNormalLeft,	\
		     const char * pathNormalMiddle,	\
		     const char * pathNormalRight,	\
		     const char * pathMarkedLeft,	\
		     const char * pathMarkedMiddle,	\
		     const char * pathMarkedRight,	\
		     unsigned short width,		\
		     unsigned short height,		\
		     Uint32 BackgroundColor);
    SDL_Surface * getStdBtnNormal();
    SDL_Surface * getStdBtnMarked();
  private:
    bool stdBtnIsSet;
    unsigned short stdBtnWidth;
    unsigned short stdBtnHeight;
    SDL_Surface * stdBtnNormal;
    SDL_Surface * stdBtnMarked;
  };

#endif /* __FSGIMAGEPOOL_H__*/
}//end namespace

