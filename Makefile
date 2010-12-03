#usage : make all -f ProgMakefile
PROJECT_NAME=fsgpp
DEFS+=-D_GNU_SOURCE=1 -D_REENTRANT
INCLUDES+=-I/usr/include/SDL
LIBS+=
#-L$(LIB_DIR)/


CPPFLAGS+=-g -Wall 
LDFLAGS+=

OBJS = LL.o Screen.o Main.o 

include $(MAKE_DIR)/globalpp.mak

