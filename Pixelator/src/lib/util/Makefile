#!smake

# These go *before* commondefs
NO_STARTOPT	=

include	/usr/include/make/commondefs

END	=

OPTIMIZER = -g

LC++INCS	= -I/usr/include/il
LLDLIBS		= -lil 
LLDOPTS		=
DSOVERSIONOPT 	= 
LD_QUICKSTART_INFO=

C++FILES = \
	image.cxx \
	$(END)


TARGETS= libutil.so


default all::
	@$(MAKE) targets
#	@$(MAKE) incdepend

targets: $(TARGETS) 

libutil.so: $(OBJECTS)
	$(C++) $(LDDSOOPTS) $(LDOPTS) $(OBJECTS) $(LDLIBS) -o $@

include $(COMMONRULES)
install: default


