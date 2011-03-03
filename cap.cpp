//#include <iostream>
#include <stdio.h>
//#include <iostream>
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

#include "v4l_capture.h"

using namespace std;
using namespace EuMax01;

class CamControl:IPollTimerListener,IPollReadListener
{
public:
  CamControl(GUI * pGUI);
  virtual void pollReadEvent(PollSource * s);
  virtual void pollTimerExpired(long us);
private:
  bool cam0ready;
  bool cam1ready;
  PollTimer * pPollTimer;
  PollReader * pPollReaderCam0;
  GUI * ptheGUI;
};

CamControl::CamControl(GUI * pGUI)
{
  this->ptheGUI = pGUI;
  cap_init(pGUI->getMainSurface(),	\
	   352,				\
	   288,				\
	   0,				\
	   0);
  pPollTimer = new PollTimer(1000,this);
  pPollReaderCam0 = new PollReader(this);

  pGUI->addPollTimer(pPollTimer);
  // cap_uninit();
}

void CamControl::pollReadEvent(PollSource * s)
{
  if(s==pPollReaderCam0)
    printf("PollSource = pPollReaderCam0 ");
  printf("pollReadEvent\n");
}

void CamControl::pollTimerExpired(long us)
{
  bool again = false;
  int camfd = 0;
  if(!this->cam0ready)
    {
      camfd=cap_cam_init(0);
      if(camfd<0)
	{
	  again = true;
	}
      else
	{
	  this->cam0ready = true;
	  this->pPollReaderCam0->setReadSource(camfd);
	  this->ptheGUI->addPollReader(pPollReaderCam0);
	}
    }

  if(!this->cam1ready)
    {
      camfd = cap_cam_init(1);
      if(camfd<0)
	{
	  again = true;
	}
      else
	{
	  this->cam1ready = true;
	  
	}
    }
  if(again)
    {
      printf("try to find camera again...\n");
    }
  else
      printf("try to find camera...\n");
}

static void evtBtn2(void * src,SDL_Event * evt){
  printf("evtBtn\n");
}

int main()
{
  GUI_Properties props;
  GUI* theGUI;

  SDL_version compile_version;

  if(SDL_BYTEORDER==SDL_BIG_ENDIAN)
    {
      printf("SDL_BYTEORDER==SDL_BIG_ENDIAN\n");
    }
  if(SDL_BYTEORDER==SDL_LIL_ENDIAN)
    {
      printf("SDL_BYTEORDER==SDL_LIL_ENDIAN\n");
    }

  props.width=720;
  props.height=576;
  props.bpp=0;
  props.flags=SDL_HWSURFACE;

  theGUI=GUI::getInstance(&props,0);
  if(!theGUI){
    printf("failure GUI::getInstance()\n");
    return -1;
  }

  SDL_Rect PosDimRect={10,400,500,80};
  Button* Btn1=new Button("huhu",PosDimRect);
  if(Btn1->setImages("Images/buttonUp2.png","Images/buttonUp.png"))
    {
      printf("error loading Images\n");
    }
  Btn1->setLMButtonDownEvtHandler(evtBtn2);
  Btn1->setLMButtonUpEvtHandler(evtBtn2);
  Btn1->setMouseOverEvtHandler(evtBtn2);

  Screen* s1 = new Screen();
  s1->addEvtTarget(Btn1);

  CamControl camCtrl = CamControl(theGUI);

  theGUI->activateScreen(s1);

  theGUI->eventLoop();

}
