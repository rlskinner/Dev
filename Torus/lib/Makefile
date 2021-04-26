#!	smake 

# $Revision: 1.3 $
# $Date: 1993/09/16 23:40:18 $

OBJECT_STYLE=32

include	/usr/include/make/commondefs

LC++OPTS  = -g 
LC++INCS =  -I$(HOME)/include -I../include

END = 

C++FILES = \
	TorusEvaluator.c++		\
	TorusAttractor.c++		\
	TorusTableAttractor.c++		\
	TorusTiler.c++			\
	oglTorusTiler.c++			\
	$(END)


TARGETS= libtorus.a

default all::
	@$(MAKE) targets

targets: $(TARGETS)

# include	/usr/include/make/commonrules

libtorus.a:	$(OBJECTS)
	rm -f $@
	ar q $@ $(OBJECTS)

install:	default


