TEMPLATE	= vcapp
LANGUAGE	= C++

END = 

CONFIG	+= qt debug exceptions rtti stl opengl console thread

SOURCES	+= main.cpp CTDisplay.cpp CTSettings.cpp

HEADERS	+= CTDisplay.h CTSettings.h

FORMS	= FormSettingsDialog.ui

INCLUDEPATH += ../../boost_1_33_1 ../../libUtil ../libTorus

LIBS += \
	../libTorus/libTorus.lib \
	../../libUtil/libUtil.lib \
	$$END

TARGET = ChaosTorus

CONFIG -= dlopen_opengl

# LIBS += \
# 	glut32.lib \
# 	../libTorus/libTorus.lib \
# 	../../libUtil/libUtil.lib \
# 	$$END

