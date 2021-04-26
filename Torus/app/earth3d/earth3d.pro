#
# See www.earth3d.org
#

win32 {
  INCLUDEPATH	+= H:\\Studium\\uEngine\\earth\\visualization\\QT\\libxml\\libxml2-2.6.6.win32\\include "C:\\include"
  LIBS	+= -LC:/lib libpng.a libz.a
#  DEFINES += WIN32_ZBUFFER_BUG
#  CONFIG += console
#  DEFINES += LINUX
  DEFINES += GENERATE_FONTS
  SOURCES += draw/wingl.cpp
  RC_FILE = earthviewer.rc
}

unix {
  UI_DIR = .ui
  MOC_DIR = .moc
  OBJECTS_DIR = .obj
!mac {
  DEFINES	+= LINUX
#  LIBS += -ljsw
#  QMAKE_CXXFLAGS_RELEASE += -march=pentium4 -O2 -pipe -fomit-frame-pointer
#  QMAKE_CXXFLAGS_RELEASE += -march=athlon-xp -O2 -pipe -fomit-frame-pointer
#  QMAKE_CXXFLAGS_RELEASE += -march=pentium3 -O2 -pipe -fomit-frame-pointer
#  QMAKE_CXXFLAGS_RELEASE += -mcpu=pentium -march=pentium -O2 -pipe -fomit-frame-pointer
}
}

mac {
  QMAKE_CXXFLAGS_RELEASE += -mcpu=7400 -maltivec
  DEFINES       += MYMACOS
#  DEFINES += GENERATE_FONTS
  RC_FILE = earth3d.icns
}

# -lMallocDebug
#  -bind_at_load
# -lqmmslog
# `fc-config --libs`
# QMAKE_CXXFLAGS_DEBUG += `fc-config --cflags`
# QMAKE_CXXFLAGS_DEBUG += -pg
# QMAKE_LFLAGS_DEBUG += -pg

# DEFINES     += DEPTH_STATISTIC

DEFINES += FORWARD_VIEW

DEFINES += QT_THREAD_SUPPORT
# DEFINES += NO_MULTITEXTURE
# DEFINES += DAVE
# DEFINES += FORWARD_VIEW_DRAW
DEFINES += USE_GL_TEXTURE_COMPRESSION
# DEFINES += SCREENSHOT_ALWAY_BIND_TEXTURE
# DEFINES += DEBUG_SPHERES
# # DEFINES += USE_ICON_BLENDING
# DEFINES += JOYSTICK
# DEFINES += ATMOSPHERE


# DEFINES	+= RELATIVETRANSFORM


TEMPLATE	= app
LANGUAGE	= C++

# QMAKE_CXXFLAGS_DEBUG += -D EARTH3DDEBUG -D DEBUG
CONFIG	+= qt thread opengl warn_on release stl

# LIBS	+= -lglut
# DEFINES	+= STATISTIC_NODECOUNT
INCLUDEPATH	+= /usr/include/libxml2/libxml /usr/include/libxml2 ../../network/rubyAgents/c ../../dataserver /sw/include /usr/X11R6/include/ /sw/include/libxml2 geometry/ network/ draw/ tree/ ./

HEADERS	+= network/qServiceLib.h \
	network/connectNetworkService.h \
	listBoxServiceItem.h \
	network/urlDownload.h \
        network/proxyUrlOperator.h \
	network/urlRawDownload.h \
        network/md5.h \
        network/fileCache.h \
	gltest.h \
	geometry/geometry2d3dSphere.h \
	geometry/geometry2d3d.h \
	pngutils.h \
	globalsettings.h \
	draw/qGLWidgetDrawScene.h
SOURCES	+= main.cpp \
	gltest.cpp \
	glcontext.cpp \
	globalsettings.cpp \
	listBoxServiceItem.cpp \
	listBoxDrawItem.cpp \
	listViewServiceItem.cpp \
	resources.cpp \
        serviceListDownload.cpp \
	network/qServiceLib.cpp \
	network/urlDownload.cpp \
	network/downloadFinishedEvent.cpp \
	network/urlRawDownload.cpp \
	network/urlRawDownloadEvent.cpp \
	network/urlTools.cpp \
	network/connectNetworkServiceRequestQueue.cpp \
	network/connectNetworkServiceRequestQueueObject.cpp \
	network/connectNetworkService.cpp \
	network/serviceFoundPrinter.cpp \
	network/serviceFoundLister.cpp \
	network/stopableDownload.cpp \
	network/dataReceivedListener.cpp \
	network/dataReceivedMapTile.cpp \
	network/downloadable.cpp \
	network/insertListViewItemEvent.cpp \
	network/insertListDrawItemEvent.cpp \
        network/proxyUrlOperator.cpp \
        network/fileCache.cpp \
        network/md5.cpp \
	tree/mapTile.cpp \
	tree/mapTileTree.cpp \
	tree/mapTileTreeNode.cpp \
	tree/mapTileTreeNodeCore.cpp \
	tree/heightfieldTree.cpp \
	tree/heightfieldTreeNode.cpp \
	tree/requestIDNode.cpp \
	tree/textureTreeNodeCore.cpp \
	draw/draw.cpp \
	draw/treeDraw.cpp \
	draw/treeDrawSphere.cpp \
	draw/treeDrawPOI.cpp \
	draw/treeDrawPOISign.cpp \
	draw/treeDrawFactory.cpp \
	draw/drawScene.cpp \
	draw/drawSceneObject.cpp \
	draw/drawSceneObjectTriangle.cpp \
	draw/drawSceneObjectSphere.cpp \
	draw/drawSceneObjectQuad.cpp \
	draw/drawSceneObjectTexture.cpp \
	draw/drawSceneObjectTransform.cpp \
	draw/drawSceneObjectTranslate.cpp \
	draw/drawSceneObjectScale.cpp \
	draw/drawSceneObjectRotatequaternion.cpp \
	draw/drawSceneObjectGroup.cpp \
	draw/drawSceneObjectUseGroup.cpp \
	draw/qGLWidgetDrawScene.cpp \
	draw/moveToPositionEvent.cpp \
	draw/imageList.cpp \
	graphicsObjectsContainer.cpp \
	tree/heightfieldTreeNodeCore.cpp \
	geometry/geometry2d3dFactory.cpp \
	geometry/geometry2d3dSphere.cpp \
	geometry/geometry2d3dplane.cpp \
	geometry/matrix.cpp \
	tree/mapTileUncompressed.cpp \
	tree/mapTileUncompressedFloat.cpp \
	tree/statusObserver.cpp \
	tree/statusObserverQT.cpp \
	tree/mutex.cpp \
	tree/globaltimer.cpp \
	geometry/frustum.cpp \
	navigator.cpp \
	geometry/quaternion.cpp \
	pngutils.cpp \
	jpgutils.cpp
FORMS	= formview.ui \
	formstatus.ui \
	forminfo.ui \
	formaddsource.ui \
	formagentform.ui \
	formoptions.ui
IMAGES	= images/filenew \
	images/fileopen \
	images/filesave \
	images/print \
	images/undo \
	images/redo \
	images/editcut \
	images/editcopy \
	images/editpaste \
	images/searchfind \
	images/filenew_1 \
	images/fileopen_1 \
	images/filesave_1 \
	images/print_1 \
	images/undo_1 \
	images/redo_1 \
	images/editcut_1 \
	images/editcopy_1 \
	images/editpaste_1 \
	images/searchfind_1 \
	images/earth_rotate_icon.png \
	images/earth_fly_icon.png \
	images/filenew_2 \
	images/fileopen_2 \
	images/filesave_2 \
	images/print_2 \
	images/undo_2 \
	images/redo_2 \
	images/editcut_2 \
	images/editcopy_2 \
	images/editpaste_2 \
	images/searchfind_2 \
	images/earthatmosphere.png \
	images/edit_picture.png \
	images/help.png \
	images/find.png \
	images/webpres.png \
	images/frame_image.png \
	images/find2.png \
	images/agenticon2.png \
	images/agenticon.png \
	images/video.png \
	images/view_text.png

