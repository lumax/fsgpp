#include <iostream>

#include <iostream>
//#include <stdlib.h>
#include <SDL/SDL.h>
#include <SDL/SDL_ttf.h>
#include <SDL/SDL_image.h>
#include "Event.h"
#include "Button.h"
//#include <fsgCheckBox.h>
//#include <fsgLabel.h>
#include "Screen.h"
#include "Globals.h"
#include "Poll.h"
#include "Main.h"
#include "ImagePool.h"
#include "Gesture.h"

using namespace std;
using namespace EuMax01;

static void evtBtn2(void * src,SDL_Event * evt){
  cout << "evtBtn"<< endl;
  //sdlMenuActivate(pTargetSurface);
}

class GestureListener : public IGestureListener
{
public:
  void yGestureOccured(int yGes,int tempo);
};

void GestureListener::yGestureOccured(int yGes,int tempo)
{
  cout << "yGestureOccured :"<< yGes << " " << tempo <<endl;
}

int main()
{
  GUI_Properties props;
  GUI* theGUI;

  SDL_version compile_version;
  const SDL_version *link_version=IMG_Linked_Version();
  SDL_IMAGE_VERSION(&compile_version);
  printf("compiled with SDL_image version: %d.%d.%d\n", 
	 compile_version.major,
	 compile_version.minor,
	 compile_version.patch);
  printf("running with SDL_image version: %d.%d.%d\n", 
	 link_version->major,
	 link_version->minor,
	 link_version->patch);

  if(SDL_BYTEORDER==SDL_BIG_ENDIAN)
    {
      cout << "SDL_BYTEORDER==SDL_BIG_ENDIAN"<<endl;
    }
  if(SDL_BYTEORDER==SDL_LIL_ENDIAN)
    {
      cout << "SDL_BYTEORDER==SDL_LIL_ENDIAN"<<endl;
    }



  props.width=640;
  props.height=480;
  props.bpp=0;
  props.flags=SDL_SWSURFACE;


  /*GUI_Properties props={.width=320,		\
			     .height=240,	\
			     .bpp=0,		\
			     .flags=SDL_SWSURFACE};
  */
  //pGUI = fsgMainInit(&props,0);
  theGUI=GUI::getInstance(&props,0);
  if(!theGUI){
    cout << "failure GUI::getInstance()"<<endl;
    return -1;
  }


  SDL_Rect PosDimRect={10,10,500,80};
  
  Button* Btn1=new Button("Τη γλώσσα",PosDimRect);
  if(Btn1->setImages("Images/buttonUp2.png","Images/buttonUp.png"))
    {
      cout << "error loading Images"<< endl;
    }
  Btn1->setLMButtonDownEvtHandler(evtBtn2);
  Btn1->setLMButtonUpEvtHandler(evtBtn2);
  Btn1->setMouseOverEvtHandler(evtBtn2);

  Button* Btn2=new Button("食食احساس   من",30,200,500,80);
  /*  if(Btn2->setImages("Images/png24_2.png","Images/buttonUp2.png"))
    {
      cout << "error loading Images"<< endl;
      }*/
  if(Btn2->setImages("Images/resources/elements/barrelButtonLeft.png",\
		     "Images/resources/elements/barrelButtonPushedLeft.png"))
    {
      cout << "error loading Images"<< endl;
    }

  int ret = 0;  
  ImagePool StdBtn = ImagePool();
  ret=StdBtn.setStdButton("Images/resources/elements/barrelButtonLeft.png", \
			  "Images/resources/elements/barrelButtonMiddle.png", \
			  "Images/resources/elements/barrelButtonRight.png", \
			  "Images/resources/elements/barrelButtonPushedLeft.png", \
			  "Images/resources/elements/barrelButtonPushedMiddle.png", \
			  "Images/resources/elements/barrelButtonPushedRight.png", \
			  500,						\
			  80,						\
			  FSG_BACKGROUND);
  if(ret)
    {
      cout << "error loading Images for ImagePool"<< endl;
    }

  ImagePool StdBtn2 = ImagePool();
  ret=StdBtn2.setStdButton("Images/resources/elements/barrelButtonLeft.png", \
			  "Images/resources/elements/barrelButtonMiddle.png", \
			  "Images/resources/elements/barrelButtonRight.png", \
			  "Images/resources/elements/barrelButtonPushedLeft.png", \
			  "Images/resources/elements/barrelButtonPushedMiddle.png", \
			  "Images/resources/elements/barrelButtonPushedRight.png", \
			  300,						\
			  80,						\
			  FSG_BACKGROUND);
  if(ret)
    {
      cout << "error loading Images for ImagePool"<< endl;
    }

  
  Button* Btn3=new Button("lmaa",30,300,500,80);
  Btn3->setImages(StdBtn.getStdBtnNormal(),StdBtn.getStdBtnMarked());

  Button* Btn4=new Button("lmaa",30,400,300,80);
  Btn4->setImages(StdBtn2.getStdBtnNormal(),StdBtn2.getStdBtnMarked());
  SDL_Rect gesturedim={0,0,640,480};
  GestureListener GesLis = GestureListener();
  Gesture slideGesture = Gesture(gesturedim,&GesLis);
  Screen* s1 = new Screen();
  s1->addEvtTarget(&slideGesture);
  s1->addEvtTarget(Btn1);
  s1->addEvtTarget(Btn2);
  s1->addEvtTarget(Btn3);
  s1->addEvtTarget(Btn4);

  theGUI->activateScreen(s1);

  theGUI->eventLoop();

  cout << "huhu" << endl;
}
