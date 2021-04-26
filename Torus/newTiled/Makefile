#!smake

include	/usr/include/make/commondefs

LC++INCS = 
LCOPTS = -g 
LC++OPTS = -g -I$(HOME)/include
LLDLIBS = -lutil -lglut -lGLU -lGL -lm -lXmu -lX11
LLDOPTS = -L$(HOME)/lib

C++FILES = tile.C

CFILES = map.c

TARGETS= tiler

default all::
	@$(MAKE) targets

targets: $(TARGETS) 

tiler: $(OBJECTS) 
	$(C++F) -o $@ $(OBJECTS) $(LDFLAGS) $(C++FILT)

include $(COMMONRULES)

install: default


