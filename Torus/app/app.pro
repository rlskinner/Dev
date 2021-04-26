TEMPLATE = vcapp
TARGET = app

SOURCES = app.cpp

CONFIG += qt debug exceptions rtti stl opengl console thread
CONFIG -= dlopen_opengl

# INCLUDEPATH += ../../boost_1_33_1 ../../libUtil ../libTorus

# END = 

# LIBS += \
# 	glut32.lib \
# 	../libTorus/libTorus.lib \
# 	../../libUtil/libUtil.lib \
# 	$$END

