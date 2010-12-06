#include <SDL/SDL.h>
#include <stdio.h>

#include <sys/types.h>
#include <sys/time.h>
#include <sys/ioctl.h>
#include <unistd.h>
#include <fcntl.h>
#include <errno.h>
#include <limits.h>

//#include <tslib.h>

#define DEBUG_MOUSE 1

typedef unsigned char Uint8;
static int mouse_fd=-1;

/* rcg06112001 Set up IMPS/2 mode, if possible. This gives
 *  us access to the mousewheel, etc. Returns zero if
 *  writes to device failed, but you still need to query the
 *  device to see which mode it's actually in.
 */
static int set_imps2_mode(int fd)
{
	/* If you wanted to control the mouse mode (and we do :)  ) ...
		Set IMPS/2 protocol:
			{0xf3,200,0xf3,100,0xf3,80}
		Reset mouse device:
			{0xFF}
	*/
	Uint8 set_imps2[] = {0xf3, 200, 0xf3, 100, 0xf3, 80};
	/*Uint8 reset = 0xff;*/
	fd_set fdset;
	struct timeval tv;
	int retval = 0;

	if ( write(fd, &set_imps2, sizeof(set_imps2)) == sizeof(set_imps2) ) {
		/* Don't reset it, that'll clear IMPS/2 mode on some mice
		if (write(fd, &reset, sizeof (reset)) == sizeof (reset) ) {
			retval = 1;
		}
		*/
	}

	/* Get rid of any chatter from the above */
	FD_ZERO(&fdset);
	FD_SET(fd, &fdset);
	tv.tv_sec = 0;
	tv.tv_usec = 0;
	while ( select(fd+1, &fdset, 0, 0, &tv) > 0 ) {
		char temp[32];
		read(fd, temp, sizeof(temp));
	}

	return retval;
}


/* Returns true if the mouse uses the IMPS/2 protocol */
static int detect_imps2(int fd)
{
	int imps2;

	imps2 = 0;

	/*	if ( SDL_getenv("SDL_MOUSEDEV_IMPS2") ) {
		imps2 = 1;
		}*/
	if ( ! imps2 ) {
		Uint8 query_ps2 = 0xF2;
		fd_set fdset;
		struct timeval tv;

		/* Get rid of any mouse motion noise */
		FD_ZERO(&fdset);
		FD_SET(fd, &fdset);
		tv.tv_sec = 0;
		tv.tv_usec = 0;
		while ( select(fd+1, &fdset, 0, 0, &tv) > 0 ) {
			char temp[32];
			read(fd, temp, sizeof(temp));
		}

   		/* Query for the type of mouse protocol */
   		if ( write(fd, &query_ps2, sizeof (query_ps2)) == sizeof (query_ps2)) {
   			Uint8 ch = 0;

			/* Get the mouse protocol response */
			do {
				FD_ZERO(&fdset);
				FD_SET(fd, &fdset);
				tv.tv_sec = 1;
				tv.tv_usec = 0;
				if ( select(fd+1, &fdset, 0, 0, &tv) < 1 ) {
					break;
				}
			} while ( (read(fd, &ch, sizeof (ch)) == sizeof (ch)) &&
			          ((ch == 0xFA) || (ch == 0xAA)) );

			/* Experimental values (Logitech wheelmouse) */
#ifdef DEBUG_MOUSE
fprintf(stderr, "Last mouse mode: 0x%x\n", ch);
#endif
			if ( (ch == 3) || (ch == 4) ) {
				imps2 = 1;
			}
		}
	}
	return imps2;
}

/*int OpenInputTS()
{
	int i;
	const char *mousedev;
	const char *mousedrv;
	struct tsdev *ts_dev;

	mousedrv = NULL;//SDL_getenv("SDL_MOUSEDRV");
	mousedev = NULL; //SDL_getenv("SDL_MOUSEDEV");
	mouse_fd = -1;

	mousedrv = SDL_getenv("SDL_MOUSEDRV");
	mousedev = SDL_getenv("SDL_MOUSEDEV");
	if ( mousedrv && (SDL_strcmp(mousedrv, "TSLIB") == 0) ) {
		if (mousedev == NULL) mousedev = SDL_getenv("TSLIB_TSDEVICE");
		if (mousedev != NULL) {
			mouse_fd = ts_open(mousedev, 1);
			if ((ts_dev != NULL) && (ts_config(ts_dev) >= 0)) {
#ifdef DEBUG_MOUSE
				fprintf(stderr, "Using tslib touchscreen\n");
#endif
				mouse_drv = MOUSE_TSLIB;
				mouse_fd = ts_fd(ts_dev);
				return mouse_fd;
			}
		}
		mouse_drv = MOUSE_NONE;
		return mouse_fd;
	}
	}*/

 //static  struct tsdev *ts_dev;
int OpenMouse()
{
	int i;
	const char *mousedev;
	const char *mousedrv;
	

	mousedrv = NULL;//SDL_getenv("SDL_MOUSEDRV");
	mousedev = NULL; //SDL_getenv("SDL_MOUSEDEV");
	mouse_fd = -1;

		static const char *ps2mice[] = {
		    "/dev/input/mice", "/dev/usbmouse", "/dev/psaux", NULL
		};
		/* Now try to use a modern PS/2 mouse */
		for ( i=0; (mouse_fd < 0) && ps2mice[i]; ++i ) {
			mouse_fd = open(ps2mice[i], O_RDWR, 0);
			if (mouse_fd < 0) {
				mouse_fd = open(ps2mice[i], O_RDONLY, 0);
			}
			if (mouse_fd >= 0) {
				/* rcg06112001 Attempt to set IMPS/2 mode */
				set_imps2_mode(mouse_fd);
				if (detect_imps2(mouse_fd)) {
#ifdef DEBUG_MOUSE
fprintf(stderr, "Using IMPS2 mouse\n");
#endif
 fprintf(stderr, "mouse_drv = MOUSE_IMPS2 using %s\n",ps2mice[i]);
//mouse_drv = MOUSE_IMPS2;
   return 0;
				} else {
#ifdef DEBUG_MOUSE
fprintf(stderr, "Using PS2 mouse\n");
#endif
//fprintf(stderr, "using %s\n"ps2mice[i],)
//mouse_drv = MOUSE_PS2;
				}
			}
		}
		return 1;
}

static int posted = 0;

void FB_vgamousecallback(int button, int relative, int dx, int dy)
{
  /*int button_1, button_3;
	int button_state;
	int state_changed;
	int i;
	Uint8 state;
  */
  printf("FB_vgamousecallback\n");
  printf("button : %i, relative: %i, dx: %i, dy: %i\n",button,relative,dx,dy);
	
	
	/*	if ( dx || dy ) {
	  posted += SDL_PrivateMouseMotion(0, relative, dx, dy);
	}

	// Swap button 1 and 3 
	button_1 = (button & 0x04) >> 2;
	button_3 = (button & 0x01) << 2;
	button &= ~0x05;
	button |= (button_1|button_3);

	// See what changed 
	button_state = SDL_GetMouseState(NULL, NULL);
	state_changed = button_state ^ button;
	for ( i=0; i<8; ++i ) {
		if ( state_changed & (1<<i) ) {
			if ( button & (1<<i) ) {
				state = SDL_PRESSED;
			} else {
				state = SDL_RELEASED;
			}
			posted += SDL_PrivateMouseButton(state, i+1, 0, 0);
		}
		}*/
}


static void handle_mouse()
{
  	static int start = 0;
	static unsigned char mousebuf[BUFSIZ];
	static int relative = 1;

	int i, nread;
	int button = 0;
	int dx = 0, dy = 0;
	int packetsize = 0;
	int realx, realy;
	
	//	handle_tslib();
	//return;
	
	//find out Packetsize:switch(mouse_drv)	
	//case MOUSE_IMPS2:
	packetsize = 4;
	//break;
	// case MOUSE_TSLIB:
	//#if SDL_INPUT_TSLIB
	//handle_tslib(this);
	//#endif
	//return; // nothing left to do for tslib
	/* Read as many packets as possible */
	nread = read(mouse_fd, &mousebuf[start], BUFSIZ-start);
	if ( nread < 0 ) 
	  {
	    return;
	  }
	nread += start;
#ifdef DEBUG_MOUSE
	fprintf(stderr, "Read %d bytes from mouse, start = %d\n", nread, start);
#endif
	for ( i=0; i<(nread-(packetsize-1)); i += packetsize ) 
	  {
	    //	switch (mouse_drv) {
	    //			case MOUSE_IMPS2:
	    /* Get current mouse state */
	    button = (mousebuf[i] & 0x04) >> 1 | /*Middle*/
	      (mousebuf[i] & 0x02) >> 1 | /*Right*/
	      (mousebuf[i] & 0x01) << 2 | /*Left*/
	      (mousebuf[i] & 0x40) >> 3 | /* 4 */
	      (mousebuf[i] & 0x80) >> 3;  /* 5 */
	    dx = (mousebuf[i] & 0x10) ?
	      mousebuf[i+1] - 256 : mousebuf[i+1];
	    dy = (mousebuf[i] & 0x20) ?
	      -(mousebuf[i+2] - 256) : -mousebuf[i+2];
	    switch (mousebuf[i+3]&0x0F) 
	      {
	      case 0x0E: /* DX = +1 */
	      case 0x02: /* DX = -1 */
		break;
	      case 0x0F: /* DY = +1 (map button 4) */
		FB_vgamousecallback(button | (1<<3),
				    1, 0, 0);
		break;
	      case 0x01: /* DY = -1 (map button 5) */
		FB_vgamousecallback(button | (1<<4),
				    1, 0, 0);
		break;
	      }
	    FB_vgamousecallback(button, relative, dx, dy);
	  }
	if ( i < nread ) {
	  SDL_memcpy(mousebuf, &mousebuf[i], (nread-i));
	  start = (nread-i);
	} else {
	  start = 0;
	}
	return;
}


void FB_PumpEvents()
{
	fd_set fdset;
	int max_fd;
	static struct timeval zero;
	int tmpi = 20;
	do {
	  /*		if ( switched_away ) {
			struct vt_stat vtstate;

			SDL_mutexP(hw_lock);
			if ( (ioctl(keyboard_fd, VT_GETSTATE, &vtstate) == 0) &&
			     vtstate.v_active == current_vt ) {
				switched_away = 0;
				switch_vt_done(this);
			}
			SDL_mutexV(hw_lock);
			}*/

	  //posted = 0;

		FD_ZERO(&fdset);
		max_fd = 0;
		/*		if ( keyboard_fd >= 0 ) {
			FD_SET(keyboard_fd, &fdset);
			if ( max_fd < keyboard_fd ) {
				max_fd = keyboard_fd;
			}
			}*/
		if ( mouse_fd >= 0 ) {
			FD_SET(mouse_fd, &fdset);
			if ( max_fd < mouse_fd ) {
				max_fd = mouse_fd;
			}
		}
		if ( select(max_fd+1, &fdset, NULL, NULL, NULL/*&zero*/) > 0 ) {
		  /*			if ( keyboard_fd >= 0 ) {
				if ( FD_ISSET(keyboard_fd, &fdset) ) {
					handle_keyboard(this);
				}
				}*/
			if ( mouse_fd >= 0 ) {
				if ( FD_ISSET(mouse_fd, &fdset) ) {
					handle_mouse();
				}
			}
		}
	} while ( tmpi/*posted*/ );
}



	int main()
{
  printf("huhu\n");
  if(OpenMouse())
  {
    printf("error OpenMouse\n");
    return;
  }
  FB_PumpEvents();
}
