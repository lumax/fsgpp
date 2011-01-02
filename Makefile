#usage : make all -f ProgMakefile
PROJECT_NAME=fsgpp
DEFS+=-D_GNU_SOURCE=1 -D_REENTRANT
INCLUDES+=-I/usr/include/SDL -I/usr/include
#-I$(INCLUDE_DIR)/libruputils
LIBS+=-lSDL -lSDL_ttf -lSDL_image 
#-lruputils
#-L$(LIB_DIR)/

ifdef CROSS_COMPILE
CPPFLAGS+=-DTARGET_ARM
endif

CPPFLAGS+=-g -Wall
#`sdl-config --cflags`
LDFLAGS+=-lSDL -lSDL_ttf -lSDL_image -lts

OBJS = LL.o Screen.o Main.o Tools.o Globals.o Event.o Button.o Poll.o\
	ImagePool.o Gesture.o

include $(MAKE_DIR)/globalpp.mak

public:
	cp ${PROJECT_NAME} ${ELDK_FS}/usr/work/fsgpp/${PROJECT_NAME}
	cp Poll.cpp ${ELDK_FS}/usr/work/fsgpp/Poll.cpp
	cp Main.cpp ${ELDK_FS}/usr/work/fsgpp/Main.cpp
	cp Event.cpp ${ELDK_FS}/usr/work/fsgpp/Event.cpp
	cp Screen.cpp ${ELDK_FS}/usr/work/fsgpp/Screen.cpp
	cp LL.cpp ${ELDK_FS}/usr/work/fsgpp/LL.cpp
	cp Button.cpp ${ELDK_FS}/usr/work/fsgpp/Button.cpp