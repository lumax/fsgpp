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

#include <dsp_jpeg.h>
#include "v4l_capture.h"
#include "iniParser.h"

using namespace std;
using namespace EuMax01;

class CamControl:IPollTimerListener,IPollReadListener
{
public:
  CamControl(GUI * pGUI,int PixelFormat);
  virtual void pollReadEvent(PollSource * s);
  virtual void pollTimerExpired(long us);
  unsigned char *framebuffer0;
  unsigned char *framebuffer1;
private:
  bool cam0ready;
  bool cam1ready;
  PollTimer * pPollTimer;
  PollReader * pPollReaderCam0;
  PollReader * pPollReaderCam1;
  GUI * ptheGUI;
  int PixelFormat;//0 = normal, 1 = MJPEG
};

static int camwidth = 0;
static int camheight = 0;


static CamControl * camCtrl;

static unsigned char getYfromRGB(unsigned char r,unsigned char g,unsigned char b)
{
  //double d = ((0.257*r)+(0.504*g)+(0.098*(double)b)+16);
  //return (unsigned char)d;
  return (unsigned char)((0.257*r)+(0.504*g)+(0.098*b)+16);
}

static unsigned char getUfromRGB(unsigned char r,unsigned char g,unsigned char b)
{
  return (unsigned char)((0.439*r)-(0.368*g)-(0.071*b)+128);
}

static unsigned char getVfromRGB(unsigned char r,unsigned char g,unsigned char b)
{
  return (unsigned char)(-(0.148*r)-(0.291*g)+(0.439*b)+128);
}

static void overlayAndCrossair(struct v4l_capture* cap,char * pc,size_t len)
{
  unsigned int i,ii;
  int w = cap->camWidth;
  int h = cap->camHeight;
  int alles = 0;
  int cam = cap->camnumber;
  int wMalZwei = w*2;
  int wMalVier = w*4;
  int offset = cam*wMalZwei;

  //Fadenkreuz
  unsigned int crossBreite = cap->camWidth;
  unsigned int crossDicke = 1;
  int zeile = w*2;
  //unsigned int crossX = w/2-crossBreite/2;
  //unsigned int crossY = h/2-crossDicke;
  unsigned int crossX = cap->camCrossX;
  unsigned int crossY = cap->camHeight/2;

  int start = zeile*crossY;
  //int flag = 1;
  unsigned char Y = 106,U = 221,V = 202;


  /*  if(flag)
    {
      Y = getYfromRGB(255,0,255);
      U = getUfromRGB(255,0,255);
      V = getVfromRGB(255,0,255);
      printf("Y = %i, U=%i, V=%i\n",Y,U,V);
      flag=0;
      }*/

  //int lineoffset = crossY*h*4;

  //horizontale Linie
  for(i=0;i<crossDicke;i++)
    {
      for(ii=0;ii<crossBreite*2;ii+=4)//ii++)
	{
	  //pc[start+ii]=0x00;
	  pc[start+ii]=Y;
	  pc[start+ii+1]=V;
	  pc[start+ii+2]=Y;
	  pc[start+ii+3]=U;
	}
      start+=zeile;
    }
  //vertikale Linie
  start = (crossX*2);//+zeile*(crossBreite/2);
  for(i=0;i<h;i++)
    {
      for(ii=0;ii<crossDicke/**2*/;ii+=4)
	{
	  pc[start+ii]=Y;
	  if(i%2)//ein Pixel in Abhängigkeit
	    {
	      pc[start+ii+1]=U;
	    }
	  else
	    {
	      pc[start+ii+1]=V;
	    }
	  //pc[start+ii+2]=Y;
	  //pc[start+ii+3]=U;
	}
      start+=zeile;
    }

  for(i=0;i<h;i++)
    {
      memcpy(cap->sdlOverlay->pixels[0]+i*wMalVier+offset,	\
	     pc+alles,						\
	     wMalZwei);
	  alles += w*2;
    }
}

/***************************************************************/
static void processMJPEG(struct v4l_capture* cap,const void * p,int method,size_t len)
{
  static int counter =0;
  unsigned char *framebuffer;
  int i;
  //if(cap->camnumber)
  //  return;
  if(counter<=50)
    {
      counter++;
      return;
    }
  if(method==IO_METHOD_MMAP)
    {
      //printf("pixelformat = MJPEG\n");

      if(cap->camnumber)
	{
	  framebuffer = camCtrl->framebuffer1;
	}
      else
	{
	  framebuffer = camCtrl->framebuffer0;
	}
      i = jpeg_decode(framebuffer,(unsigned char*)p,\
		      &cap->camWidth,\
		      &cap->camHeight);
      if(i)
	printf("error jpeg_decode\n");

      SDL_LockSurface(cap->mainSurface);
      SDL_LockYUVOverlay(cap->sdlOverlay);

      overlayAndCrossair(cap,(char *)framebuffer,len);

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
/***************************************************************/
static void processImages(struct v4l_capture* cap,const void * p,int method,size_t len)
{
  if(method==IO_METHOD_MMAP)
    {
      SDL_LockSurface(cap->mainSurface);
      SDL_LockYUVOverlay(cap->sdlOverlay);

      char * pc = (char *)p;
      overlayAndCrossair(cap,(char *)pc,len);

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

/*static inline unsigned char clamp (double x)
{
int r = x;      // round to nearest

        if (r < 0)         return 0;
        else if (r > 255)  return 255;
        else               return r;
}

static void inverseConversion()
{
  int Y1, Cb, Cr;         // gamma pre-corrected input [0;255]
int ER, EG, EB;         // output [0;255]

 double r, g, b;         // temporaries
  double y1, pb, pr;

  y1 = (255 / 219.0) * (Y1 - 16);
  pb = (255 / 224.0) * (Cb - 128);
  pr = (255 / 224.0) * (Cr - 128);

  r = 1.0 * y1 + 0     * pb + 1.402 * pr;
  g = 1.0 * y1 - 0.344 * pb - 0.714 * pr;
  b = 1.0 * y1 + 1.772 * pb + 0     * pr;

  ER = clamp (r * 255); // [ok? one should prob. limit y1,pb,pr]
  EG = clamp (g * 255);
  EB = clamp (b * 255);
}
*/
static void convertYUYVtoRGB(char * src,char * target,int w,int h)
{
  //R = 1.164(Y - 16) + 1.596(V - 128)
  //G = 1.164(Y - 16) - 0.813(V - 128) - 0.391(U - 128)
  //B = 1.164(Y - 16) + 2.018(U - 128)

  //target : RGBA
  //source Y0 U0 Y1 V0  Y2 U2 Y3 V2  ...usw.
  //Es gibt w*h Pixel! YUYV hat zwei Pixel in vier Bytes

  unsigned int len = (w*h)/2;
  unsigned int i;
  double term1 = 0;
  char alpha = 0;//255;//128;

  char * ps = src;
  char * pt = target;
  for(i=0;i<len;i++)
    {
      term1 = (double)(1.164*(ps[0]-16));
      pt[0] = (char)( term1 + 1.596*(ps[3]-128) );//R
      pt[1] = (char)( term1 - 0.813*(ps[3]-128) - 0.391*(ps[1] - 128) );//G
      pt[2] = (char)( term1 + 2.018*(ps[1]-128) );//B
      pt[3] = alpha;

      pt+=4; // das nächste Pixel beim Target

      term1 = 1.164*(ps[2]-16);
      pt[0] = (char)( term1 + 1.596*(ps[3]-128) );//R
      pt[1] = (char)( term1 - 0.813*(ps[3]-128) - 0.391*(ps[1] - 128) );//G
      pt[2] = (char)( term1 + 2.018*(ps[1]-128) );//B
      pt[3] = alpha;

      pt+=4;
      ps+=4;
    }
}

static void processRGBImages(struct v4l_capture* cap,const void * p,int method,size_t len)
{
  static SDL_Surface * pSf = 0;
  static int initNotDone = 1;
  //printf("processRGBImages len:%i\n",len);
  if(method==IO_METHOD_MMAP)
    {
      //printf("cap->cam : %i\n",cap->camnumber);
      if(cap->camnumber==0)
	{
	  if(initNotDone)
	    {
	      printf("mainSurface BitsPerPixel:%i, BytesPerPixel :%i\n",\
		     cap->mainSurface->format->BitsPerPixel,		\
		     cap->mainSurface->format->BytesPerPixel);
	      //SDL_SWSURFACE|SDL_SRCALPHA,
	      pSf =SDL_CreateRGBSurface(SDL_HWSURFACE,                 \
					cap->camWidth,			\
					cap->camHeight,			\
					32,				\
					SDL_GetVideoSurface()->format->Rmask, \
					SDL_GetVideoSurface()->format->Gmask, \
					SDL_GetVideoSurface()->format->Bmask, \
					SDL_GetVideoSurface()->format->Amask);
	      if(!pSf)
		{
		  printf("SDL_CreateRGBSurface failed in processRGBImages\n");
		  exit(-1);
		}
	      printf("pSf pitch:%i\n",pSf->pitch);
	      printf("SDL_GetVideoSurface()->format->Rmask: %x\n",SDL_GetVideoSurface()->format->Rmask);
	      printf("SDL_GetVideoSurface()->format->Gmask: %x\n",SDL_GetVideoSurface()->format->Gmask);
	      printf("SDL_GetVideoSurface()->format->Bmask: %x\n",SDL_GetVideoSurface()->format->Bmask);
	      printf("SDL_GetVideoSurface()->format->Amask: %x\n",SDL_GetVideoSurface()->format->Amask);
	      printf("SDL_GetVideoSurface()->format->BitsPerPixel: %i\n",SDL_GetVideoSurface()->format->BitsPerPixel);
	      printf("SDL_GetVideoSurface()->format->BytesPerPixel: %i\n",SDL_GetVideoSurface()->format->BytesPerPixel);
	      printf("SDL_GetVideoSurface()->format->alpha: %i\n",SDL_GetVideoSurface()->format->alpha);
	      printf("SDL_GetVideoSurface()->format->palette: %x\n",SDL_GetVideoSurface()->format->palette);
	      initNotDone = 0;
	    }
	  else
	    {
	      char * pc = (char *)p;
	      convertYUYVtoRGB(pc,(char *)pSf->pixels,cap->camWidth,cap->camHeight);
	      SDL_Rect destrect;
	      destrect.x = 50;
	      destrect.y = 50;
	      destrect.w=cap->camWidth;
	      destrect.h = cap->camHeight;
	      if(SDL_BlitSurface(pSf,0,cap->mainSurface,&destrect))
		printf("Blitting failed in processRGBImages\n");
	      if(SDL_Flip(cap->mainSurface))
		printf("Flipping failed in processRGBImages\n");
	    }//end else initNotDone
	}//end if cap->cam  == 1
      else
	{
	  //printf("not yet support for cam %i\n",cap->cam);
	}
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


CamControl::CamControl(GUI * pGUI,int Pixelformat)
{
  this->ptheGUI = pGUI;

  if(Pixelformat)
    this->PixelFormat = 1;//1 = MJPEG
  else
    this->PixelFormat = 0;

  cap_init(pGUI->getMainSurface(),	\
	   camwidth,				\
	   camheight,				\
	   0,				\
	   this->PixelFormat);
  cam0ready=false;
  cam1ready=false;
  pPollTimer = new PollTimer(1000,this);
  pPollReaderCam0 = new PollReader(this);
  pPollReaderCam1 = new PollReader(this);

  pGUI->addPollTimer(pPollTimer);
  // cap_uninit();

#ifdef C6COMPILE
  this->framebuffer0 =
    (unsigned char *) C6RUN_MEM_calloc(1,
			     (size_t) camwidth * (camheight +
						   8) * 2);
  this->framebuffer1 =
    (unsigned char *) C6RUN_MEM_calloc(1,
			     (size_t) camwidth * (camheight +
						   8) * 2);
#else
  this->framebuffer0 =
    (unsigned char *) calloc(1,
			     (size_t) camwidth * (camheight +
						   8) * 2);
  this->framebuffer1 =
    (unsigned char *) calloc(1,
			     (size_t) camwidth * (camheight +
						   8) * 2);
#endif /* C6COMPILE */
}

void CamControl::pollReadEvent(PollSource * s)
{
  if(s==pPollReaderCam0)
    {
      //printf("0");
      if(-1==cap_read_frame(0))
	{
	  printf("error on polling camera0\n");
	}
    }
    if(s==pPollReaderCam1)
    {
      //printf("1");
      if(-1==cap_read_frame(1))
	{
	  printf("error on polling camera1\n");
	}
    }
}

void CamControl::pollTimerExpired(long us)
{
  bool again = false;
  int camfd = 0;
  if(!this->cam0ready)
    {
      camfd=cap_cam_init(0,processRGBImages);
      printf("cap_cam_init(0,processRGBImages);\n");
      /*if(this->PixelFormat==2)
	{

	}*/
      /*if(this->PixelFormat==1)
	{
	  camfd=cap_cam_init(0,processMJPEG);
	}
      else
	{
	  camfd=cap_cam_init(0,processImages);
	  }*/
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
      camfd=cap_cam_init(1,processRGBImages);
      printf("cap_cam_init(1,processRGBImages);\n");
      /*if(this->PixelFormat)
	{
	  camfd=cap_cam_init(1,processMJPEG);
	}
      else
	{
	  camfd=cap_cam_init(1,processImages);
	  }*/
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
      //printf("TODO remove PollTimer\n");
    }
}

static void evtB1(void * src,SDL_Event * evt){
  cap_cam_addCrossX(0,-10);
}
static void evtB2(void * src,SDL_Event * evt){
  cap_cam_addCrossX(0,-2);
}
static void evtB3(void * src,SDL_Event * evt){
  cap_cam_addCrossX(0,2);
}
static void evtB4(void * src,SDL_Event * evt){
  cap_cam_addCrossX(0,10);
}
static void evtB5(void * src,SDL_Event * evt){
  cap_cam_addCrossX(1,-10);
}
static void evtB6(void * src,SDL_Event * evt){
  cap_cam_addCrossX(1,-2);
}
static void evtB7(void * src,SDL_Event * evt){
  cap_cam_addCrossX(1,2);
}
static void evtB8(void * src,SDL_Event * evt){
  cap_cam_addCrossX(1,10);
}
static void evtExit(void * src,SDL_Event * evt){
  GUI::getInstance(0,0)->stopEventLoop();
}

const char * usage =				\
  "cap -xga for 1024x768 else PAL Widescreen with 1024*576\n"\
  "    -fullscreen for Fullscreen\n"\
  "    -m for MJPEG (normally use RAW\n";

static void theSecondaryEvtHandling(SDL_Event * theEvent)
{
  switch(theEvent->type)
    {
    case (SDL_ACTIVEEVENT):
      {
	printf("---\n");
	printf("SDL_ACTIVEEVENT type %i,\n",theEvent->type);
	printf("SDL_ACTIVEEVENT gain %i,\n",theEvent->active.gain);
	printf("SDL_ACTIVEEVENT type %i,\n",theEvent->active.state);
	break;
      }
    default:
      {
	printf("eventType %i,\n",theEvent->type);
      }
    }
}

int main(int argc, char *argv[])
{
  //SDL_version compile_version;
  GUI* theGUI;
  int sdlwidth = 1024;
  int sdlheight = 576;
  GUI_Properties props;
  int Pixelformat = 0;//0 = normal, 1 = MJPEG
  char tmp[64];

  props.width=0;
  props.height=0;
  props.bpp=0;
  props.flags=0;

  //camwidth = 640;//352;//800;
  //camheight = 480;//288;//600

  if(!iniParser_getParam("cap.conf","sdlwidth",tmp,64))
    {
      sdlwidth = atoi(tmp);
      printf("sdlwidth = %i\n",sdlwidth);
    }
  if(!iniParser_getParam("cap.conf","sdlheight",tmp,64))
    {
      sdlheight = atoi(tmp);
      printf("sdlheigth = %i\n",sdlheight);
    }
  if(!iniParser_getParam("cap.conf","camwidth",tmp,64))
    {
      camwidth = atoi(tmp);
      printf("camwidth = %i\n",camwidth);
    }
 if(!iniParser_getParam("cap.conf","camheight",tmp,64))
    {
      camheight = atoi(tmp);
      printf("camheight = %i\n",camheight);
    }
  if(!iniParser_getParam("cap.conf","pixelformat",tmp,64))
    {
      if(!strcmp("mjpeg",tmp))
	{
	  Pixelformat=1;
	  printf("pixelformat = mjpeg\n");
	}
      else
	{
	  Pixelformat = 0;
	  printf("pixelformat = normal\n");
	}	  
    }

  argc--;
  while(argc)
    {
      if(!strcmp(argv[argc],"-xga")||!strcmp(argv[argc],"-XGA"))
	{
	  sdlwidth = 1024;
	  sdlheight = 768;
	}
      else if(!strcmp(argv[argc],"-fullscreen"))
	{
	  props.flags|=SDL_FULLSCREEN;
	}
      else if(!strcmp(argv[argc],"-m"))
	{
	  Pixelformat=1;
	}
      else
	{
	  printf("%s",usage);
	  return 0;
	}
      argc--;
    }

  props.width=sdlwidth;//1280;//720;
  props.height=sdlheight;//576;
  props.bpp=0;
  props.flags|=SDL_SWSURFACE;//SDL_HWSURFACE;//|SDL_DOUBLEBUF;

  if(SDL_BYTEORDER==SDL_BIG_ENDIAN)
    {
      printf("SDL_BYTEORDER==SDL_BIG_ENDIAN\n");
    }
  if(SDL_BYTEORDER==SDL_LIL_ENDIAN)
    {
      printf("SDL_BYTEORDER==SDL_LIL_ENDIAN\n");
    }

  theGUI=GUI::getInstance(&props,/*theSecondaryEvtHandling*/0);
  if(!theGUI){
    printf("failure GUI::getInstance()\n");
    return -1;
  }

  camCtrl = new CamControl(theGUI,Pixelformat);

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

    B1 B2 B3 B4   Bexit  B5 B6 B7 B8   
    << < | > >>          << < | > >>

B1 = camhalbe0 - 2*Buttonwidth - 2*Abstand
B2 = camhalbe0 - 1*Buttonwidth - 1*Abstand
B3 = camhalbe0 + 0*Buttonwidth + 1*Abstand
B4 = camhalbe0 + 1*Buttonwidth + 2*Abstand
B5 = camhalbe1 - 2*ButtonWidth - 2*Abstand
B6 = camhalbe1 - 1*            - 1*Abstand
B7 = camhalbe1 + 0*            + 1*
B8 = camhalbe1 + 1*            + 2*
Bexit = sdlw/2 - Buttonwidth/2  
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
  
  PosDimRect.x = sdlw/2 - BtnW/2;
  Button* Bexit=new Button("QUIT",PosDimRect);
  Bexit->setLMButtonUpEvtHandler(evtExit);  

  Screen* s1 = new Screen();
  s1->addEvtTarget(B1);
  s1->addEvtTarget(B2);
  s1->addEvtTarget(B3);
  s1->addEvtTarget(B4);
  s1->addEvtTarget(B5);
  s1->addEvtTarget(B6);
  s1->addEvtTarget(B7);
  s1->addEvtTarget(B8);
  s1->addEvtTarget(Bexit);

  theGUI->activateScreen(s1);

  theGUI->eventLoop();
}
