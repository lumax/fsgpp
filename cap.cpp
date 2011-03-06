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
      unsigned int crossBreite = cap->camWidth;
      unsigned int crossDicke = 2;
      int zeile = w*2;
      //unsigned int crossX = w/2-crossBreite/2;
      //unsigned int crossY = h/2-crossDicke;
      unsigned int crossX = cap->camCrossX;
      unsigned int crossY = cap->camHeight/4*3;

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
      start = (crossX*2);//+zeile*(crossBreite/2);
      for(i=0;i<h;i++)
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
      if(counter>=40)
	ptheGUI->stopEventLoop();
    }
}

static void evtB1(void * src,SDL_Event * evt){
  cap_cam_addCrossX(0,-10);
}
static void evtB2(void * src,SDL_Event * evt){
  cap_cam_addCrossX(0,-1);
}
static void evtB3(void * src,SDL_Event * evt){
  cap_cam_addCrossX(0,1);
}
static void evtB4(void * src,SDL_Event * evt){
  cap_cam_addCrossX(0,10);
}
static void evtB5(void * src,SDL_Event * evt){
  cap_cam_addCrossX(1,-10);
}
static void evtB6(void * src,SDL_Event * evt){
  cap_cam_addCrossX(1,-1);
}
static void evtB7(void * src,SDL_Event * evt){
  cap_cam_addCrossX(1,1);
}
static void evtB8(void * src,SDL_Event * evt){
  cap_cam_addCrossX(1,10);
}

int main()
{
  //SDL_version compile_version;
  GUI_Properties props;
  GUI* theGUI;

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

  CamControl camCtrl = CamControl(theGUI);

/*
<------------------| sdlwidth/2

<------------- camwidth*2 ---------------->

___________________________________________
|                  |                      |
|                  |                      |
|                  |                      |
|                  |                      |
|                  |                      |
|                  |                      |
|__________________|______________________|

         | camhalbe0
           camhalbe1          | 

camhalbe0 =  sdlwidth/2 -camwidth/2
camhalbe1 =  sdlwidth/2 +camwidth/2

    B1 B2 B3 B4          B5 B6 B7 B8   
    << < | > >>          << < | > >>

B1 = camhalbe0 - 2*Buttonwidth - 2*Abstand
B2 = camhalbe0 - 1*Buttonwidth - 1*Abstand
B3 = camhalbe0 + 0*Buttonwidth + 1*Abstand
B4 = camhalbe0 + 1*Buttonwidth + 2*Abstand
B5 = camhalbe1 - 2*ButtonWidth - 2*Abstand
B6 = camhalbe1 - 1*            - 1*Abstand
B7 = camhalbe1 + 0*            + 1*
B8 = camhalbe1 + 1*            + 2*  
*/
  int sdlw = props.width;
  int camhalbe0 = sdlw/2 - camwidth/2;
  int camhalbe1 = sdlw/2 + camwidth/2;
  int X = 0;
  int Y = camheight + 20;//hier fangen die Buttons an
  int BtnW=60;
  int BtnH=30;
  int Abstand = 5;

  SDL_Rect PosDimRect={0+X,0+Y,BtnW,BtnH};

  PosDimRect.x = camhalbe0 - 2*BtnW - 2*Abstand;
  Button* B1=new Button("<<",PosDimRect);
  B1->setLMButtonUpEvtHandler(evtB1);

  PosDimRect.x = camhalbe0 - 1*BtnW - 1*Abstand;
  Button* B2=new Button("<",PosDimRect);
  B2->setLMButtonUpEvtHandler(evtB2);

  PosDimRect.x = camhalbe0 + 0*BtnW + 1*Abstand;
  Button* B3=new Button(">",PosDimRect);
  B3->setLMButtonUpEvtHandler(evtB3);

  PosDimRect.x = camhalbe0 + 1*BtnW + 2*Abstand;
  Button* B4=new Button(">>",PosDimRect);
  B4->setLMButtonUpEvtHandler(evtB4);

  PosDimRect.x = camhalbe1 - 2*BtnW - 2*Abstand;
  Button* B5=new Button("<<",PosDimRect);
  B5->setLMButtonUpEvtHandler(evtB5);

  PosDimRect.x = camhalbe1 - 1*BtnW - 1*Abstand;
  Button* B6=new Button("<",PosDimRect);
  B6->setLMButtonUpEvtHandler(evtB6);

  PosDimRect.x = camhalbe1 + 0*BtnW + 1*Abstand;
  Button* B7=new Button(">",PosDimRect);
  B7->setLMButtonUpEvtHandler(evtB7);

  PosDimRect.x = camhalbe1 + 1*BtnW + 2*Abstand;
  Button* B8=new Button(">>",PosDimRect);
  B8->setLMButtonUpEvtHandler(evtB8);

  Screen* s1 = new Screen();
  s1->addEvtTarget(B1);
  s1->addEvtTarget(B2);
  s1->addEvtTarget(B3);
  s1->addEvtTarget(B4);
  s1->addEvtTarget(B5);
  s1->addEvtTarget(B6);
  s1->addEvtTarget(B7);
  s1->addEvtTarget(B8);

  theGUI->activateScreen(s1);

  theGUI->eventLoop();
}
