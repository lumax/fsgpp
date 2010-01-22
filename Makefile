PROJECT_NAME=libfsg
MAJOR=1
MINOR=0
VERSION=$(MAJOR).$(MINOR)

DEFS+=-D_GNU_SOURCE=1 -D_REENTRANT
INCLUDES+=-I/usr/include/SDL -I$(INCLUDE_DIR)/libruputils
LIBS+=


CFLAGS+=-g -c -Wall -fPIC
LDFLAGS+= -lSDL -lSDL_ttf -lSDL_image -lruputils -shared -Wl

OBJS = fsgButton.o fsgEvent.o fsgTools.o fsgGlobals.o fsgMain.o fsgScreen.o fsgLabel.o fsgLL.o fsgCheckBox.o

EXE_ANHANG = .so.$(VERSION)

include $(MAKE_DIR)/global.mak
