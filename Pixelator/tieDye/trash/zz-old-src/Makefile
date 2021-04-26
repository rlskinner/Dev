#!smake

include	/usr/include/make/commondefs

LC++INCS = -I/usr/include/il
LC++OPTS = -g 
LLDLIBS = -lil -lm -lgl
LLDOPTS = 

WEIGHT_SRCS = \
	weight.c++ \
	gradWeight.c++ \
	imageWeight.c++

IMAGE_SRCS = 

ACTION_SRCS = \
	action.c++ \
	nborAction.c++ \
	dirAction.c++ \
	edgeAction.c++ \
	ringAction.c++ \
	coneAction.c++ \
	crossAction.c++ \
	cornerAction.c++ 

SEED_SRCS = \
	seed.c++ \
	edgeSeed.c++ \
	lineSeed.c++ \
	randomSeed.c++ \
	imageSeed.c++ 

PROGRAM_SRCS = \
	txtCellArray.c++ \
	txtEat.c++ \
	glCellArray.c++ \
	glEat.c++

MISC_SRCS = \
	cellArray.c++ \
	eat.c++ \
	parse.c++ 

C++FILES = \
	$(WEIGHT_SRCS) \
	$(IMAGE_SRCS) \
	$(ACTION_SRCS) \
	$(SEED_SRCS) \
	$(MISC_SRCS)

YYFILES = gmr.y
YFLAGS = -d

LLFILES = lex.l

$(WEIGHT_OBJS).o:$(WEIGHT_SRCS).c++

GENERIC_OBJS = \
	lex.o \
	gmr.o \
	${C++FILES:.c++=.o}

TXT_OBJS = \
	txtCellArray.o \
	txtEat.o

GL_OBJS = \
	glCellArray.o \
	glEat.o

OBJS = $(GENERIC_OBJS) $(TXT_OBJS) $(GL_OBJS)

TARGETS= txtEat glEat


default all::
	@$(MAKE) targets
#	@$(MAKE) incdepend

targets: incdepend $(TARGETS) 

txtEat: $(TXT_OBJS) $(GENERIC_OBJS)
	$(C++F) -o $@ $(TXT_OBJS) $(GENERIC_OBJS) $(LDFLAGS) $(C++FILT)

glEat: $(GL_OBJS) $(GENERIC_OBJS)
	$(C++F) -o $@ $(GL_OBJS) $(GENERIC_OBJS) $(LDFLAGS) $(C++FILT)


imgRead: imgRead.o
	$(C++F) -o $@ imgRead.o $(LDFLAGS) $(C++FILT)

include $(COMMONRULES)
install: default


