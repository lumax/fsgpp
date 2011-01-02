/*
Gesture.cpp
Bastian Ruppert
01.01.2011
*/


#include <SDL/SDL.h>

//#include "Globals.h"
//#include "Tools.h"
#include "Event.h"

#include "Gesture.h"

#include <iostream>

namespace EuMax01
{

  Gesture::Gesture(SDL_Rect ActiveArea)
  {
    //clear memory
    char * pv = (char*)this;
    for(unsigned int i=0; i<sizeof(Gesture);i++)
      {
	*pv = 0;
	pv++;
      }

    this->GESTUREACTION = 20;
    this->pTSource = this;//Quelle setzen
    this->PosDimRect.x = ActiveArea.x;
    this->PosDimRect.y = ActiveArea.y;
    this->PosDimRect.w = ActiveArea.w;
    this->PosDimRect.h = ActiveArea.h;
    this->fnkLeftMouseButtonDown = Gesture::mouseButtonDown;
    this->fnkLeftMouseButtonUp = Gesture::mouseButtonUp;
  }

  void Gesture::mouseMotion(void * src,SDL_Event * theEvent)
  {
    Gesture * pGes = (Gesture*)src;
    int tmp=0;
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
	std::cout << "Gesture:"<< pGes->yGesture <<"cnt:"<< pGes->EvtCounter<< std::endl;
	Gesture::mouseButtonDown(src,theEvent);
      }
  }
  void Gesture::mouseButtonDown(void * src,SDL_Event * theEvent)
  {
    Gesture * pGes = (Gesture*)src;
    pGes->EvtCounter = 0;
    pGes->yGesture = 0;
    pGes->yPos = theEvent->motion.y;
    pGes->fnkMouseMotion = Gesture::mouseMotion;
    std::cout << "Gesture : mouseButtonDown"<<std::endl; 
  }
  void Gesture::mouseButtonUp(void * src,SDL_Event * theEvent)
  {
    Gesture * pGes = (Gesture*)src;
    pGes->fnkMouseMotion = 0;
    std::cout << "Gesture : mouseButtonUp"<<std::endl; 
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
