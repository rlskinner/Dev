#!	smake

#
# Modify to suit your environment
#

include	/usr/include/make/commondefs

TK_LIB_PATH= -L/usr/local/lib
TK_INCLUDE_PATH= -I/usr/local/include/tk
TCL_INCLUDE_PATH= -I/usr/local/include/tcl
TKGLX_INCLUDE_PATH= -I/usr/local/include/tkGLX

TKGLX_LIBS= -ltkGLX -ltk -ltcl -lgl_s -lXext -lX11_s -lm 
TKGLX_INCLUDES = $(TK_INCLUDE_PATH) $(TCL_INCLUDE_PATH) $(TKGLX_INCLUDE_PATH)

OPTIMIZER = -g
LC++INCS = -I../include -I$(HOME)/include

LLDOPTS = -L../lib -L$(HOME)/lib
LLDLIBS = -ltorus -lutil -lGLU -lGL -lGLw -lXm -lXt -lX11 -lm

END = 

C++FILES = \
	drawTest.c++ \
	perfTest.c++ \
	screenSave.c++ \
	main.c++ \
	attractorMorph.c++ \
	shape.c++ \
	circleShape.c++ \
	gridShape.c++ \
	$(END)

CFILES = \
	glwrappers.c \
	tkAppInit.c  \
	torus.c  \
	$(END)

LIBS= $(TKGLX_LIBS)

DFLAGS=-g 
LCFLAGS=$(DFLAGS) -D__STDC__ $(TKGLX_INCLUDES)

LLDFLAGS=$(DFLAGS) $(TK_LIB_PATH) $(LIBS)

TORUS_OBJS=tkAppInit.o torus.o glwrappers.o

OBJS=$(TORUS_OBJS) 

all: torusWish perfTest

torusWish: $(OBJS)
	$(CC) -o $@ $(OBJS) $(LDFLAGS)

PERF_OBJS = perfTest.o

perfTest:	$(PERF_OBJS) ../lib/libtorus.a
	$(C++) -o $@ $(PERF_OBJS) $(LDFLAGS)

DRAW_OBJS = drawTest.o

drawTest:	$(DRAW_OBJS)
	$(C++) -o $@ $(DRAW_OBJS) $(LDFLAGS)

SAVER_OBJS = screenSave.o

screenSave:	$(SAVER_OBJS) ../lib/libtorus.a $(HOME)/lib/libutil.a
	$(C++) -o $@ $(SAVER_OBJS) $(LDFLAGS)

CHAOS_MORPH_OBJS = attractorMorph.o main.o

chaosMorph:	$(CHAOS_MORPH_OBJS) ../lib/libtorus.a $(HOME)/lib/libutil.a
	$(C++) -o $@ $(CHAOS_MORPH_OBJS)  $(LDFLAGS)

CHAOS_DANCE_OBJS = shapeMorph.o shape.o circleShape.o gridShape.o main.o

chaosDance:	$(CHAOS_DANCE_OBJS) ../lib/libtorus.a $(HOME)/lib/libutil.a
	$(C++) -o $@ $(CHAOS_DANCE_OBJS)  $(LDFLAGS)

include $(COMMONRULES)

TARGETS = chaosDance chaosMorph

install: default

MANPAGES = chaosDance.1 chaosMorph.1 

DISTDIR = /usr/dist/savers

dist:	$(TARGETS)
	cp $(TARGETS) $(MANPAGES) $(DISTDIR)

