#include <iostream>
using namespace std;
using namespace EuMax01;


int main()
{
  GUI_Properties props;
  props.width=320;
  props.height=240;
  props.bpp=0;
  props.flags=SDL_SWSURFACE;

  _TfsgGUI_Properties props={.width=320, \
			     .height=240,	\
			     .bpp=0,		\
			     .flags=SDL_SWSURFACE};
  
  //pGUI = fsgMainInit(&props,0);
  if(initMain(&props,0)){
    return -1;
  }
  
  /* if(createScreen1()){
    return -1;
  }

  if(createScreen2()){
    return -1;
  }
  
  fsgMainActivateScreen(&Screen2);*/

  fsgMainEventLoop();

  cout << "huhu" << endl;
}
