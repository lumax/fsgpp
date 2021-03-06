/*
Gesture.h
Bastian Ruppert
01.01.2011
*/


namespace EuMax01
{

#ifndef __FSGGESTURE_H__
#define __FSGGESTURE_H__

  class IGestureListener
  {
   public:
    virtual ~IGestureListener() {}
    virtual void yGestureOccured(int yGesture,int tempo) = 0;
  };

  class Gesture : public EvtTarget
  {
  public:
    Gesture(SDL_Rect ActiveArea,IGestureListener * lis);
    ~Gesture();
  private:
    IGestureListener * listener;
    int EvtCounter;
    int yPos;
    int yGesture;
    int GESTUREACTION;
    static void mouseMotion(void * src,SDL_Event * theEvent);
    static void mouseButtonDown(void * src,SDL_Event * theEvent);
    static void mouseButtonUp(void * src,SDL_Event * theEvent);
  };

#endif /* __FSGGESTURE_H__*/
}//end namespace

