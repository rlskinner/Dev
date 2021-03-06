//
//	class to enable better code sharing and modularity
//	for torus algorithms & GLUT
//

#ifdef WIN32
#include <windows.h>
#endif

#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glut.h>

#include "glutApp.h"
#include "cell2D.h"

glutApp	*glutApp::_theApp = NULL;


//
//  This is the gross part, the parent class implementation needs
//	to know every child class
//
glutApp*
glutApp::createApp( int &argc, char *argv[] )
{
    _theApp = new cell2D;
    _theApp->init( argc, argv );
    return _theApp;
}

glutApp*
glutApp::getApp()
{
    return _theApp;
}

glutApp::glutApp()
    : _width( 256 )
    , _height( 256 )
    , _wid( 0 )
{
}

void
glutApp::init( int &argc, char *argv[] )
{
    // _width & _height are logical sizes for the program,
    // subclasses may change the actual window size
    if( glutGet( GLUT_INIT_WINDOW_WIDTH ) != 1999 ) {
	// size must have been set on command line, set w & h accordingly
	_width  = glutGet( GLUT_INIT_WINDOW_WIDTH );
	_height = glutGet( GLUT_INIT_WINDOW_HEIGHT );
    }

    // setup callbacks
    createWindows();
    glutDisplayFunc( displayFuncCB );
    glutIdleFunc( idleFuncCB );
    glutKeyboardFunc( keyboardFuncCB );
    glutMouseFunc( mouseFuncCB );
}

void	
glutApp::defaultKeyboardCB( unsigned char key, int x, int y )
{
    switch( key ) {
	case 0x1b:	// escape
	    exit( 0 );
	    break;
    }
}

void
glutApp::displayFuncCB()
{
    glutApp	*app = getApp();
    if( app ) {
	static	int	firstDisplay = 1;
	if( firstDisplay ) {
	    app->displayInit();
	    firstDisplay = 0;
	} else {
	    app->display();
	}
    }
}

void
glutApp::idleFuncCB()
{
    glutApp	*app = getApp();
    if( app ) {
	static	int	firstIdle = 1;
	if( firstIdle ) {
	    app->idleInit();
	    firstIdle = 0;
	} else {
	    app->idle();
	}
    }
}

void
glutApp::keyboardFuncCB( unsigned char key, int x, int y )
{
    glutApp	*app = getApp();
    if( app ) {
	app->keyboard( key, x, y );
    }
}


void
glutApp::mouseFuncCB( int button, int state, int x, int y )
{
    glutApp	*app = getApp();
    if( app ) {
	app->mouse( button, state, x, y );
    }
}

