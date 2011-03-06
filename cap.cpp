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

static int camwidth = 0;
static int camheight = 0;

/***************************************************************/
static void processImages(struct v4l_capture* cap,const void * p,int method,size_t len)
{
  unsigned int i,ii;
  if(method==IO_METHOD_MMAP)
    {
      SDL_LockSurface(cap->mainSurface);
      SDL_LockYUVOverlay(cap->sdlOverlay);

      int w = cap->camWidth;
      int h = cap->camHeight;
      int alles = 0;
      int cam = cap->camnumber;
      int wMalZwei = w*2;
      int wMalVier = w*4;
      int offset = cam*wMalZwei;

      //Fadenkreuz
      unsigned int crossBreite = 88;
      unsigned int crossDicke = 4;
      int zeile = w*2;
      //unsigned int crossX = w/2-crossBreite/2;
      //unsigned int crossY = h/2-crossDicke;
      unsigned int crossX = 100;
      unsigned int crossY = 200;
      if(cam)
	{
	  crossX = 200;
	  crossY = 150;
	}
      else
	{
	  crossX = 50;
	  crossY = 50;
	}
      int start = crossX*2+zeile*crossY;
      //int lineoffset = crossY*h*4;
      char * pc = (char *)p;

      //horizontale Linie
      for(i=0;i<crossDicke;i++)
	{
	  for(ii=0;ii<crossBreite*2;ii++)
	    {
	      pc[start+ii]=0x00;
	    }
	  start+=zeile;
	}
      //vertikale Linie
      start = (crossX+crossBreite/2)*2+zeile*(crossY-crossBreite/2);
      for(i=0;i<crossBreite;i++)
	{
	  for(ii=0;ii<crossDicke*2;ii++)
	    {
	      pc[start+ii]=0x00;
	    }
	  start+=zeile;
	}

      for(i=0;i<h;i++)
	{
	  memcpy(cap->sdlOverlay->pixels[0]+i*wMalVier+offset,p+alles, wMalZwei);
	  alles += w*2;
	}
      //printf("alles = %i, len = %i\n",alles,len);
      SDL_UnlockYUVOverlay(cap->sdlOverlay);
      SDL_UnlockSurface(cap->mainSurface);

      /*tmpRect.h=tmpRect.h*MULTIPLIKATOR;*2;//untereinander
	tmpRect.w=tmpRect.w*2*MULTIPLIKATOR;*4;//nebeneinander*/
      SDL_DisplayYUVOverlay(cap->sdlOverlay, &cap->sdlRect);
    }
  else if(method==IO_METHOD_USERPTR)
    {
      printf("IO_METHOD_USEPTR not supported in process_image2\n");
    }
  else
    {
      fputc ('_', stdout);
      fflush (stdout);
    }
}

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
  PollReader * pPollReaderCam1;
  GUI * ptheGUI;
};

CamControl::CamControl(GUI * pGUI)
{
  this->ptheGUI = pGUI;
  cap_init(pGUI->getMainSurface(),	\
	   camwidth,				\
	   camheight,				\
	   0,				\
	   0);
  cam0ready=false;
  cam1ready=false;
  pPollTimer = new PollTimer(1000,this);
  pPollReaderCam0 = new PollReader(this);
  pPollReaderCam1 = new PollReader(this);

  pGUI->addPollTimer(pPollTimer);
  // cap_uninit();
}

void CamControl::pollReadEvent(PollSource * s)
{
  if(s==pPollReaderCam0)
    {
      printf("0");
      if(-1==cap_read_frame(0))
	{
	  printf("error on polling camera0\n");
	}
    }
    if(s==pPollReaderCam1)
    {
      printf("1");
      if(-1==cap_read_frame(1))
	{
	  printf("error on polling camera1\n");
	}
    }
}

void CamControl::pollTimerExpired(long us)
{
  static int counter = 0;
  bool again = false;
  int camfd = 0;
  if(!this->cam0ready)
    {
      camfd=cap_cam_init(0,processImages);
      if(camfd<0)
	{
	  again = true;
	}
      else
	{
	  printf("add cam0 to PollManager\n");
	  this->cam0ready = true;
	  this->pPollReaderCam0->setReadSource(camfd);
	  if(this->ptheGUI->addPollReader(pPollReaderCam0)!=0)
	    printf("addPollReader failed\n");
	}
    }

  if(!this->cam1ready)
    {
      camfd = cap_cam_init(1,processImages);
      if(camfd<0)
	{
	  again = true;
	}
      else
	{
	  printf("add cam1 to PollManager\n");
	  this->cam1ready = true;
	  this->pPollReaderCam1->setReadSource(camfd);
	  if(this->ptheGUI->addPollReader(pPollReaderCam1)!=0)
	    printf("addPollReader failed\n");
	}
    }
  if(again)
    {
      printf("try to find camera again...\n");
    }
  else
    {
      printf("TODO remove PollTimer\n");
      counter++;
      if(counter>=10)
	ptheGUI->stopEventLoop();
    }
}

static void evtBtn2(void * src,SDL_Event * evt){
  printf("evtBtn\n");
}

int main()
{
  //SDL_version compile_version;
  GUI_Properties props;
  GUI* theGUI;

  int Y = 300;
  camwidth = 352;
  camheight = 288;

  props.width=720;
  props.height=576;
  props.bpp=0;
  props.flags=SDL_SWSURFACE;//SDL_HWSURFACE;//|SDL_DOUBLEBUF;

  if(SDL_BYTEORDER==SDL_BIG_ENDIAN)
    {
      printf("SDL_BYTEORDER==SDL_BIG_ENDIAN\n");
    }
  if(SDL_BYTEORDER==SDL_LIL_ENDIAN)
    {
      printf("SDL_BYTEORDER==SDL_LIL_ENDIAN\n");
    }

  theGUI=GUI::getInstance(&props,0);
  if(!theGUI){
    printf("failure GUI::getInstance()\n");
    return -1;
  }

  SDL_Rect PosDimRect={10,10+Y,500,80};
  Button* Btn1=new Button("huhu",PosDimRect);
  /*if(Btn1->setImages("Images/buttonUp2.png","Images/buttonUp.png"))
    {
      printf("error loading Images\n");
      }*/
  Btn1->setLMButtonDownEvtHandler(evtBtn2);
  Btn1->setLMButtonUpEvtHandler(evtBtn2);
  Btn1->setMouseOverEvtHandler(evtBtn2);

  Screen* s1 = new Screen();
  s1->addEvtTarget(Btn1);
   CamControl camCtrl = CamControl(theGUI);

    theGUI->activateScreen(s1);

  theGUI->eventLoop();

}
