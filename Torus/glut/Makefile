#!smake

OBJECT_STYLE=32

include	/usr/include/make/commondefs

LC++INCS = 
LCOPTS = -g 
LC++OPTS = -g -I$(HOME)/include -I../include
LLDLIBS = ../lib/libtorus.a -lglut -lGLU -lGL -lm -lXmu -lX11
LLDOPTS = -L$(HOME)/lib

C++FILES = \
	torus.c++	\
	glutApp.c++	\
	cell2D.c++	\
	$(NULL)

TARGETS= torus

default all::
	@$(MAKE) targets

targets: $(TARGETS) 

torus: $(OBJECTS) 
	$(C++F) -o $@ $(OBJECTS) $(LDFLAGS) $(C++FILT)

include $(COMMONRULES)

install: default


