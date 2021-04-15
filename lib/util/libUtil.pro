#
#  Build libUtil.lib
#
END =

TEMPLATE = vclib
TARGET = libUtil

CONFIG += static debug exceptions rtti stl

HEADERS +=					\
	colorSequence.h			\
	hilbertColorSequence.h	\
	hilbertSequence.h		\
	interval.h				\
	randomUtil.h			\
	spaceSampler.h			\
	unistd.h				\
	$$END

SOURCES +=						\
	colorSequence.cpp			\
	hilbertColorSequence.cpp	\
	hilbertSequence.cpp			\
	interval.cpp				\
	drand48.cpp					\
	spaceSampler.cpp			\
	unistd.cpp					\
	$$END

INCLUDEPATH += $(DEVROOT)/include/boost_1_33_1

OBJECTS_DIR	= ./Debug
