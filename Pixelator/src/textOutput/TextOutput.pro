#####################################################################
# Text output test of PixelEnumerator
#####################################################################

END_LIST	=

TARGET = TextOutput

TEMPLATE = vcapp

CONFIG += ordered
CONFIG += qt warn_on debug
CONFIG -= release

DEFINES += 						\
	QT_DLL 						\
	_HAS_ITERATOR_DEBUGGING=0 	\
	_SECURE_SCL=0 				\
	$$END_LIST

HEADERS += 		\
	TextOutput.h	\
	$$END_LIST

SOURCES += 			\
	TextOutput.cpp		\
	$$END_LIST

INCLUDEPATH += 			\
	../lib/enum		\
	$(DEVROOT)/include	\
	$$END_LIST

release {
        OBJECTS_DIR     = Release
        DESTDIR         = Release
} else {
        OBJECTS_DIR     = Debug
        DESTDIR         = Debug
}

LIBPATH +=						\
	$(DEVROOT)/lib				\
	../lib/enum/$$OBJECTS_DIR	\
	$$END_LIST

LIBS	+=		\
	libUtil.lib	\
	lib_enum.lib	\
	$$END_LIST
