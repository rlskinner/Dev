#
#  Build libTorus.lib
#
TEMPLATE = vclib
TARGET = libTorus

CONFIG += debug exceptions rtti stl

END = 

HEADERS += \
	TorusAttractor.cpp \
	TorusEvaluator.cpp \
	TorusTableAttractor.cpp \
	$$END

SOURCES += \
	TorusAttractor.h \
	TorusEvaluator.h \
	TorusTableAttractor.h \
	$$END

INCLUDEPATH += ../../boost_1_33_1 ../../libUtil

OBJECTS_DIR	= ./Debug
DESTDIR		= .
