#!smake

# These go *before* commondefs
NO_STARTOPT	=

include	/usr/include/make/commondefs

END	=

OPTIMIZER = -g

LC++INCS	= -I/usr/include/il -I../util -I../enum
LLDLIBS		= -lil 
LLDOPTS		=
DSOVERSIONOPT 	= 
LD_QUICKSTART_INFO=

C++FILES = \
	parse.cxx \
	$(END)

YFILES = gmr.y
YFLAGS = -d

LFILES = lex.l

TARGETS= libparse.so

default all:: 
	@$(MAKE) targets
#	@$(MAKE) incdepend

targets: $(TARGETS) 

parse.o: gmr.o
lex.o:	gmr.o

libparse.so: $(OBJECTS)
	$(C++) $(LDDSOOPTS) $(LDOPTS) $(OBJECTS) $(LDLIBS) -o $@

include $(COMMONRULES)
install: default


