TEMPLATE = vclib
CONFIG += static
TARGET = lib_enum

HEADERS = 							\
	src/lib/enum/action.h			\
	src/lib/enum/cellArray.h		\
	src/lib/enum/coneAction.h		\
	src/lib/enum/contourAction.h	\
	src/lib/enum/contourWeight.h	\
	src/lib/enum/cornerAction.h		\
	src/lib/enum/crossAction.h		\
	src/lib/enum/dirAction.h		\
	src/lib/enum/diskSeed.h			\
	src/lib/enum/edgeSeed.h			\
	src/lib/enum/gradWeight.h		\
	src/lib/enum/imageSeed.h		\
	src/lib/enum/imageWeight.h		\
	src/lib/enum/linearWeight.h		\
	src/lib/enum/lineSeed.h			\
	src/lib/enum/nborAction.h		\
	src/lib/enum/randomSeed.h		\
	src/lib/enum/ringAction.h		\
	src/lib/enum/seed.h				\
	src/lib/enum/weight.h
	

SOURCES = 							\
	src/lib/enum/action.cpp			\
	src/lib/enum/cellArray.cpp		\
	src/lib/enum/coneAction.cpp		\
	src/lib/enum/contourAction.cpp	\
	src/lib/enum/contourWeight.cpp	\
	src/lib/enum/cornerAction.cpp	\
	src/lib/enum/crossAction.cpp	\
	src/lib/enum/dirAction.cpp		\
	src/lib/enum/diskSeed.cpp		\
	src/lib/enum/edgeSeed.cpp		\
	src/lib/enum/gradWeight.cpp		\
	src/lib/enum/imageSeed.cpp		\
	src/lib/enum/imageWeight.cpp	\
	src/lib/enum/lineSeed.cpp		\
	src/lib/enum/nborAction.cpp		\
	src/lib/enum/randomSeed.cpp		\
	src/lib/enum/ringAction.cpp		\
	src/lib/enum/seed.cpp			\
	src/lib/enum/weight.cpp

