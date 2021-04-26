#!smake

include	/usr/include/make/commondefs

LC++INCS = -I$(HOME)/include
LCOPTS = -g 
LC++OPTS = -g 
LLDLIBS = -L$(HOME)/lib -lutil -lgl -lm 
LLDOPTS = -g

END = 

C++FILES = \
	app.c++ \
	sliceSeq.c++ \
	sphere.c++ \
	$(END)

CFILES = \
	$(END)

TARGETS= 3DTorus

default all::
	@$(MAKE) targets
#	@$(MAKE) incdepend

targets: incdepend $(TARGETS) 

3DTorus: $(OBJECTS) 
	$(C++F) -o $@ $(OBJECTS) $(LDFLAGS) $(C++FILT)

include $(COMMONRULES)

install: default


