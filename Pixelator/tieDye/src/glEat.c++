//
//   eat an image away based on different rules, and different seed points
//

#include	<stdio.h>
#include	<stdlib.h>
#include	<unistd.h>

#include	<GL/glu.h>
#include	"glEat.h"
#include	"glCellArray.h"

void
keybd( unsigned char key, int, int )
{
    if( 0x1b == key  )
	exit( 0 );
}

void
display()
{
    glMatrixMode( GL_PROJECTION );
    glLoadIdentity();
    gluOrtho2D( 0.0, eatApp->cells->dims[0], 0.0, eatApp->cells->dims[1] );
    glMatrixMode( GL_MODELVIEW );
    glLoadIdentity();
    glTranslatef( 0.375, 0.375, 0.0 );
    eatApp->cells->print();
}

void
idle()
{
    if( eatApp->cells->numWaiting() > 0 ) {
	eatApp->doActions();
    } else {
	eatApp->writeImage();			// XXX doesn't seem belong here
	glutIdleFunc( NULL );			// kill idle loop
    }
}


//
//  process queue events
//
void
glEat::processEvent( int block )
{
#if	0
	if( !qtest() && !block )
	    return;

	short	data;
	while( qtest() || block ) {
		long dev = qread( &data );
		switch( dev ) {
			case REDRAW:
				cells->print();
				break;
			case ESCKEY:
				exit( 0 );
				break;
		}
	}
#endif
}


void
glEat::makeCellArray( int nDim, int dims[] )
{
    cells = new glCellArray( nDim, dims );
}


main( int argc, char *argv[] )
{
	eatApp = new glEat( argc, argv );
	eatApp->parseInput( argc, argv );
	eatApp->init();
	// eatApp->doActions( TRUE );
	glutDisplayFunc( display );
	glutIdleFunc( idle );
	glutKeyboardFunc( keybd );
	glutMainLoop();
}
		
		
	

