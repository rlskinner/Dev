#
#  Build glutTorus
#
END = 

TEMPLATE = vcapp
TARGET = glutTorus
OBJECTS_DIR	= ./Debug
DESTDIR		= .

CONFIG += debug exceptions rtti stl opengl console

INCLUDEPATH += ../../boost_1_33_1 ../../libUtil ../libTorus

LIBS += \
	glut32.lib \
	../libTorus/libTorus.lib \
	../../libUtil/libUtil.lib \
	$$END

HEADERS += \
	cell2D.h \
	glutApp.h \
	$$END

SOURCES += \
	cell2D.cpp \
	glutApp.cpp \
	torus.cpp \
	$$END

