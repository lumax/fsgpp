#usage : make all -f ProgMakefile
PROJECT_NAME=fsgpp
DEFS+=-D_GNU_SOURCE=1 -D_REENTRANT
INCLUDES+=-I/usr/include/SDL 
#-I$(INCLUDE_DIR)/libruputils
LIBS+=-lSDL -lSDL_ttf -lSDL_image 
#-lruputils
#-L$(LIB_DIR)/


CPPFLAGS+=-g -Wall `sdl-config --cflags`
LDFLAGS+=

OBJS = LL.o Screen.o Main.o Tools.o Globals.o Event.o Button.o

include $(MAKE_DIR)/globalpp.mak

