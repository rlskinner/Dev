// 
// GLUT program to get the ball rolling in several directions:
//
//	1. seperate computation of the attractor from drawing
//
//	2. get away from IRIS GL
//
//	3. experiment with 3 dimensional attractor
//
//	4. multithreading?
//

#include	<iostream>
#include	<math.h>
#include	<string.h>

#include	<boost/random/uniform_real.hpp>
#include	<boost/random/uniform_01.hpp>
#include	<boost/random/linear_congruential.hpp>
#include	<boost/random/variate_generator.hpp>

#include	<GL/glut.h>

#include	<TorusEvaluator.h>

#include	"glutApp.h"

#define	NUM_PTS	16

struct	GlobalData	{
    GlobalData();

    GLubyte	*cells;
    int		cellWidth;
    int		cellHeight;
    int		cellWindow;

    float	*pts;

	// boost random number generator as a replacement for drand48
	boost::rand48 rng;
	boost::uniform_real<> uni_01;
	boost::variate_generator<boost::rand48&, boost::uniform_real<> > rand;
	double drand48() { return rand(); }
} global;


GlobalData::GlobalData()
	: rng()
	, uni_01(0,1)
	, rand(rng, uni_01)
{
    cellWidth = 300;
    cellHeight = 300;
    cells = new GLubyte[cellWidth*cellHeight];
    memset( cells, 0, cellWidth*cellHeight*sizeof(GLubyte) );

    pts = new float[2*NUM_PTS];
    for( int i=0; i<2*NUM_PTS; i++ ) {
	pts[i] = drand48();
    }
}

TorusEvaluator	*torus;

void
display()
{
    static	int firstTime = 1;
    if( firstTime ) {
	firstTime = 0;

	for( int i=0; i<256; i++ ) {
	    glutSetColor( i, float(i)/255.0, float(i)/255.0, float(i)/255.0 );
	}

	glViewport( 0, 0, 2*global.cellWidth-1, 2*global.cellHeight-1 );

	glMatrixMode( GL_PROJECTION );
	glLoadIdentity();
	glOrtho( 0.0, 2*global.cellWidth-1.0, 
		 0.0, 2*global.cellHeight-1.0, 
		 -1.0, 1.0 );

	glMatrixMode( GL_MODELVIEW );
	glLoadIdentity();

	glClearIndex( 0 );
	glClear( GL_COLOR_BUFFER_BIT );
    }

    glRasterPos2f( 0, 0 );
    glDrawPixels( global.cellWidth, global.cellHeight, 
    		GL_COLOR_INDEX, GL_UNSIGNED_BYTE, global.cells );

    glRasterPos2i( global.cellWidth, 0 );
    glDrawPixels( global.cellWidth, global.cellHeight, 
    		GL_COLOR_INDEX, GL_UNSIGNED_BYTE, global.cells );

    glRasterPos2i( 0, global.cellHeight );
    glDrawPixels( global.cellWidth, global.cellHeight, 
    		GL_COLOR_INDEX, GL_UNSIGNED_BYTE, global.cells );

    glRasterPos2i( global.cellWidth, global.cellHeight );
    glDrawPixels( global.cellWidth, global.cellHeight, 
    		GL_COLOR_INDEX, GL_UNSIGNED_BYTE, global.cells );
}

void
idle()
{
    torus->eval( NUM_PTS, global.pts, global.pts );

    glBegin( GL_POINTS );
    for( int i=0; i<2*NUM_PTS; i += 2 ) {
	int	x = global.pts[i]*global.cellWidth;
	int	y = global.pts[i+1]*global.cellHeight;

	GLubyte	*c = &global.cells[y*global.cellWidth+x];
	if( *c < 255 ) {
	    glIndexub( ++(*c) );
	    glVertex2i( x, y );
	    glVertex2i( x+global.cellWidth, y );
	    glVertex2i( x, y+global.cellHeight );
	    glVertex2i( x+global.cellWidth, y+global.cellHeight );
	}
    }
    glEnd();
}

int main( int argc, char *argv[] )
{
    glutApp	*app = glutApp::createApp( argc, argv );
    glutInitWindowSize( 1999, 1999 );		// magic numbers
    glutInitWindowPosition(100, 100);

    glutMainLoop();
}
