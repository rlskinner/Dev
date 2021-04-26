TEMPLATE = vclib
CONFIG += static
TARGET = lib_enum

LISTEND =

INCLUDEPATH +=				\
	../../../../../include	\
	$$LISTEND

DEFINES += 						\
	QT_DLL 						\
	_HAS_ITERATOR_DEBUGGING=0 	\
	_SECURE_SCL=0 				\
	$$END_LIST

HEADERS += 				\
	action.h			\
		coneAction.h	\
		contourAction.h	\
		cornerAction.h	\
		crossAction.h	\
		dirAction.h		\
		nborAction.h	\
		ringAction.h	\
		swirlAction.h	\
	cellArray.h			\
	Dimensions.h		\
	Index.h				\
	PixelEnumerator.h	\
	seed.h				\
		diskSeed.h		\
		edgeSeed.h		\
		lineSeed.h		\
	weight.h			\
	$$LISTEND

#		contourWeight.h		\
#		gradWeight.h		\
#		imageWeight.h		\
#		linearWeight.h		\
#		imageSeed.h		\
#		randomSeed.h	\

SOURCES += 					\
	action.cpp				\
		coneAction.cpp		\
		contourAction.cpp	\
		cornerAction.cpp	\
		crossAction.cpp		\
		dirAction.cpp		\
		nborAction.cpp		\
		ringAction.cpp		\
		swirlAction.cpp		\
	cellArray.cpp			\
	Dimensions.cpp			\
	Index.cpp				\
	PixelEnumerator.cpp		\
	seed.cpp				\
		diskSeed.cpp		\
		edgeSeed.cpp		\
		lineSeed.cpp		\
	weight.cpp				\
	$$LISTEND


#		contourWeight.cpp		\
#		gradWeight.cpp		\
#		imageWeight.cpp		\
#		imageSeed.cpp	\
#		randomSeed.cpp	\

# demote compatibility warnings to level 4
ADDITIONAL_CXXFLAGS = -w44996 

QMAKE_CXXFLAGS_RELEASE += $$ADDITIONAL_CXXFLAGS
QMAKE_CXXFLAGS_DEBUG += $$ADDITIONAL_CXXFLAGS

