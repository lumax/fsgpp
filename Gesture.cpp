/*
Gesture.cpp
Bastian Ruppert
01.01.2011
*/

#include <SDL/SDL.h>
#include "Event.h"
#include "Gesture.h"

#undef GESTURE_DEBUG 
#ifdef GESTURE_DEBUG
#include <iostream>
using namespace std;
#endif
namespace EuMax01
{

  Gesture::~Gesture(){}
  Gesture::Gesture(SDL_Rect ActiveArea,IGestureListener * lis)
  {
    //clear memory
    /*    char * pv = (char*)this;
    for(unsigned int i=0; i<sizeof(Gesture);i++)
      {
	*pv = 0;
	pv++;
	}*/
    this->GESTUREACTION = 10;
    this->listener = lis;
    this->pTSource = this;//Quelle setzen
    this->PosDimRect.x = ActiveArea.x;
    this->PosDimRect.y = ActiveArea.y;
    this->PosDimRect.w = ActiveArea.w;
    this->PosDimRect.h = ActiveArea.h;
    this->fnkLeftMouseButtonDown = Gesture::mouseButtonDown;
    this->fnkLeftMouseButtonUp = Gesture::mouseButtonUp;
  }

  //int Gesture::show(SDL_Surface * target){return 0;}

  void Gesture::mouseMotion(void * src,SDL_Event * theEvent)
  {
    Gesture * pGes = (Gesture*)src;
    pGes->EvtCounter++;
    
    if(theEvent->motion.y<pGes->yPos)
      {
	pGes->yGesture-= pGes->yPos-theEvent->motion.y;
      }
    else if(theEvent->motion.y>pGes->yPos)
      {
	pGes->yGesture+= theEvent->motion.y-pGes->yPos;
      }
    pGes->yPos = theEvent->motion.y;
#ifdef GESTURE_DEBUG
    cout << "gesMM" << endl;
#endif
  }

  void Gesture::mouseButtonDown(void * src,SDL_Event * theEvent)
  {
    Gesture * pGes = (Gesture*)src;
    pGes->EvtCounter = 0;
    pGes->yGesture = 0;
    pGes->yPos = theEvent->motion.y;
    pGes->fnkMouseMotion = Gesture::mouseMotion;
#ifdef GESTURE_DEBUG
    cout << "gesMD" << endl;
#endif
  }

  void Gesture::mouseButtonUp(void * src,SDL_Event * theEvent)
  {
    Gesture * pGes = (Gesture*)src;
    int tmp =0;
    pGes->fnkMouseMotion = 0;
    if(pGes->yGesture<0)
      {
	tmp = pGes->yGesture*(-1);
      }
    else
      {
	tmp = pGes->yGesture;
      }
    if(tmp>=pGes->GESTUREACTION)
      {
	pGes->listener->yGestureOccured(pGes->yGesture,pGes->EvtCounter);
      }
#ifdef GESTURE_DEBUG
    cout << "gesMU" << endl;
#endif
  }

  /* \brief Button is decorated by images and
   * \param normal repräsentiert den Normal-Zustand
   * \param down repräsentiert den Pressed-Zustand
   */
  /*  void Button::setImages(SDL_Surface* normal,	\
			 SDL_Surface* down)
  {
  }*/

}//end namespace
