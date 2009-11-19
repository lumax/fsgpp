/*
Bastian Ruppert
*/

#include <stdio.h>
#include <stdlib.h>
#include <SDL/SDL.h>
#include <fsgEvent.h>
#include <fsgButton.h>
#include <fsgCheckBox.h>
#include <fsgLabel.h>
#include <fsgScreen.h>
#include <fsgMain.h>

static void ScreenActivate(void){printf("OnActivate\n");}
static void ScreenDeactivate(void){printf("OnDeactivate\n");}

_TfsgScreen Screen1 = {
  .OnActivate = ScreenActivate,
  .OnDeactivate = ScreenDeactivate,
};
_TfsgScreen Screen2 = {
};

static void evtBtn1(SDL_Event * evt,void * src){
  printf("evtBtn1MouseUp\n");
  fsgMainActivateScreen(&Screen2);
}
static void evtBtn2(SDL_Event * evt,void * src){
  printf("evtBtn2MouseUp\n");
  //sdlMenuActivate(pTargetSurface);
}
static void evtBtn3(SDL_Event * evt,void * src){
  printf("evtBtn3MouseUp\n");
  exit(0);  
}

_TfsgButton Btn1={.PosDimRect={.x=10,.y=10,.w=150,.h=30},	\
		  .pButtonText = "Sccreen2",                    \
		  .EvtTarget={.fnkMouseOver = 0,                \
			      .fnkLeftMouseButtonDown = 0,      \
			      .fnkLeftMouseButtonUp = evtBtn1}	\
};

_TfsgButton Btn2={.PosDimRect={.x=10,.y=50,.w=150,.h=30},	\
		  .pButtonText = "Button2",                     \
		  .EvtTarget={.fnkMouseOver = 0,                \
			      .fnkLeftMouseButtonDown = 0,      \
			      .fnkLeftMouseButtonUp = evtBtn2}	\
};

_TfsgButton Btn3={.PosDimRect={.x=10,.y=90,.w=150,.h=30},	\
		  .pButtonText = "Button3",                     \
		  .EvtTarget={.fnkMouseOver = 0,                \
			      .fnkLeftMouseButtonDown = 0,      \
			      .fnkLeftMouseButtonUp = evtBtn3}	\
};

_TfsgLabel L1;
_TfsgCheckBox CB1;

static void evtBtn21(SDL_Event * evt,void * src){
  printf("evtBtn21MouseUp\n");
  fsgMainActivateScreen(&Screen1); 
}
static void evtBtn22(SDL_Event * evt,void * src){
  fsgLabelSetText(&L1,"ToggleCB");
  fsgCheckBoxToggle(&CB1);
  //sdlMenuActivate(pTargetSurface);
}
static void evtBtn23(SDL_Event * evt,void * src){
  printf("evtBtn23MouseUp, CheckBoxStatus:%i\n",\
	 fsgCheckBoxGetStatus(&CB1) );
}
static void evtBtn23LSel(void * src){
  printf("evtBtn23LSel\n");
  fsgLabelSetText(&L1,"MouseOverBtn1");
}
static void evtBtn23LUnSel(void * src){
  printf("evtBtn23LUnSel\n");
  fsgLabelSetText(&L1,"!MouseOverBtn1");
  //fsgScreenShow(pScreen2);
}

_TfsgLabel L1={.PosDimRect={.x=160,.y=10,.w=150,.h=30},	\
	       .pLabelText = "HUHU-x-x-x-x-x",                  \
	       .EvtTarget={.fnkMouseOver = 0,			\
			   .fnkLeftMouseButtonDown = 0,		\
			      .fnkSelect = evtBtn23LSel,        \
			      .fnkUnSelect = evtBtn23LUnSel}	\
}; 

_TfsgButton Btn21={.PosDimRect={.x=10,.y=10,.w=150,.h=30},	\
		  .pButtonText = "Screen1",                     \
		  .EvtTarget={.fnkMouseOver = 0,                \
			      .fnkLeftMouseButtonDown = 0,      \
			      .fnkLeftMouseButtonUp = evtBtn21}	\
};

_TfsgButton Btn22={.PosDimRect={.x=10,.y=50,.w=150,.h=30},	\
		  .pButtonText = "Button22",                    \
		  .EvtTarget={.fnkMouseOver = 0,                \
			      .fnkLeftMouseButtonDown = 0,      \
			      .fnkLeftMouseButtonUp = evtBtn22}	\
};

_TfsgButton Btn23={.PosDimRect={.x=10,.y=90,.w=150,.h=30},	\
		  .pButtonText = "Button23",                    \
		  .EvtTarget={.fnkMouseOver = 0,                \
			      .fnkLeftMouseButtonDown = 0,      \
			      .fnkLeftMouseButtonUp = evtBtn23,	\
			      .fnkSelect = evtBtn23LSel,        \
			      .fnkUnSelect = evtBtn23LUnSel}	\
};

static void StatusChanged(void * src,int stat)
{
  printf("CheckBox Status Changed to %i\n",stat); 
}

_TfsgCheckBox CB1={.PosDimRect={.x=170,.y=90,.w=30,.h=30},\
		   .fnkStatusChanged=StatusChanged
};

int createScreen1(void){
  /*pScreen1 = fsgScreenConstructor();
  if(!pScreen1){
    printf("pScreen1 Constructor failed!\n");
    return -1;
    }*/
    
  if(fsgScreenAddButton(&Screen1,&Btn1)){
    printf("add Button to pScreen1 failed!\n");
    return -1;
  }
  if(fsgScreenAddButton(&Screen1,&Btn2)){
    printf("add Button2 to pScreen1 failed!\n");
    return -1;
  }
  if(fsgScreenAddButton(&Screen1,&Btn3)){
    printf("add Button3 to pScreen1 failed!\n");
    return -1;
  }
  

  //fsgScreenShow(pScreen1);
  return 0;
}

int createScreen2(void){
  /*pScreen2 = fsgScreenConstructor();
  if(!pScreen2){
    printf("pScreen1 Constructor failed!\n");
    return -1;
    }*/
    
  if(fsgScreenAddButton(&Screen2,&Btn21)){
    printf("add Button to pScreen2 failed!\n");
    return -1;
  }
  if(fsgScreenAddButton(&Screen2,&Btn22)){
    printf("add Button2 to pScreen2 failed!\n");
    return -1;
  }
  if(fsgScreenAddButton(&Screen2,&Btn23)){
    printf("add Button3 to pScreen2 failed!\n");
    return -1;
  }
  
   if(fsgScreenAddLabel(&Screen2,&L1)){
    printf("add Label1 to pScreen2 failed!\n");
    return -1;
  }
   if(fsgScreenAddCheckBox(&Screen2,&CB1,0)){
    printf("add Label1 to pScreen2 failed!\n");
    return -1;     
   }

  //fsgScreenShow(pScreen1);
  return 0;
}


int main(int argl, char* args[])
{
  _TfsgGUI_Properties props={.width=320, \
			     .height=240,	\
			     .bpp=0,		\
			     .flags=SDL_SWSURFACE};
  
  //pGUI = fsgMainInit(&props,0);
  if(fsgMainInit(&props,0)){
    return -1;
  }
  
  if(createScreen1()){
    return -1;
  }

  if(createScreen2()){
    return -1;
  }
  
  fsgMainActivateScreen(&Screen2);

  fsgMainEventLoop();

  return 0;
}



