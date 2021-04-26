#!smake

include	/usr/include/make/commondefs

LC++INCS = -I$(HOME)/include
LCOPTS = -g 
LC++OPTS = -g 
LLDLIBS = -L$(HOME)/lib -lutil -lgl -lm 
LLDOPTS = -g

C++FILES = \
	main.c++

CFILES = \
	map.c

TARGETS= torus

default all::
	@$(MAKE) targets
#	@$(MAKE) incdepend

targets: incdepend $(TARGETS) 

torus: $(OBJECTS) 
	$(C++F) -o $@ $(OBJECTS) $(LDFLAGS) $(C++FILT)

include $(COMMONRULES)

install: default


