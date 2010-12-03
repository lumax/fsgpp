#usage : make all -f ProgMakefile
PROJECT_NAME=fsgpp
DEFS+=-D_GNU_SOURCE=1 -D_REENTRANT
INCLUDES+=-I$(INCLUDE_DIR)/libfsg -I/usr/include/SDL
LIBS+=
#-L$(LIB_DIR)/


CPPFLAGS+=-g -Wall 
LDFLAGS+=-lfsg 

OBJS = 

include $(MAKE_DIR)/globalpp.mak

