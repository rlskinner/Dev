#####################################################################
# Paint-by-Numbers projectfile
#####################################################################

END_LIST	=

TARGET = pbn

TEMPLATE = vcapp

CONFIG += ordered
CONFIG += qt warn_on debug 
CONFIG -= release

QT += opengl

DEFINES += 						\
	QT_DLL 						\
	_HAS_ITERATOR_DEBUGGING=0 	\
	_SECURE_SCL=0 				\
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


HEADERS += 			\
	Colormap.h		\
	mainWindow.h	\
	Pbn2DWidget.h	\
	PbnMdi.h		\
	$$END_LIST

SOURCES += 			\
	Colormap.cpp	\
	main.cpp		\
	mainWindow.cpp	\
	Pbn2DWidget.cpp	\
	PbnMdi.cpp		\
	$$END_LIST

RESOURCES	+= mdi.qrc

