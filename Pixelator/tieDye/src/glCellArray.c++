//
//   eat an image away based on different rules, and different seed points
//

#include	<stdio.h>

#include	"eat.h"
#include	"glCellArray.h"


glCellArray::glCellArray( int nd, int d[] )
	: cellArray( nd, d )
{
	startCI = 0;
	rangeCI = 256;
}



//
//  look for non-standard options that I'm interested in
//
void
glCellArray::init( eat *e )
{
	cellArray::init( e );

	glutInit( &e->argc, e->argv );
	glutInitWindowSize( e->dims[0], e->dims[1] );
	if( e->setPosition ) {
		glutInitWindowPosition( dims[0], dims[1] );
	}
	glutInitDisplayMode( GLUT_INDEX );
	glutCreateWindow( "glEat" );

	// 
	//  XXX should get istartCI & rangeCI from the colormap command
	//
	setIndexRange( 1024, 3*1024 );		
	if( e->loadCmap ) {
		char	sys[1024];
		sprintf( sys, "loadmap %s\0", e->cmapFilename );
		system( sys );
	} else {
		// make black and white bands from 1024 to 4096

		int start = startCI;
		int range = rangeCI;
		setIndexRange( start, range );

		glutSetColor( start, 0.5, 0.5, 0.5 );
		for( int i=start+1; i<start+range; i++ ) {
			int	band = i / 128;
			if( band % 2 ) {
				glutSetColor( i, 1.0, 1.0, 1.0 );
			} else {
				glutSetColor( i, 0.0, 0.0, 0.0 );
			}
		}
	}
}


void
glCellArray::set( int index[] )
{
	GLint ci = getCI( setCntr, totalCount );
	glIndexi( ci );
	glBegin( GL_POINTS );
	    glVertex2i( index[0], index[1] );
	glEnd();
	cellArray::set( index );
}


void
glCellArray::print()
{
	if( nDim != 2 ) {
		printf( "sorry, can't print %dD version", nDim );
	}
	
	// int	total = dims[0]*dims[1];
	// int	cntr = 0;

	int	ii[2];
	for( int j=0; j<dims[1]; j++ ) {
		ii[1] = j;
		for( int i=0; i<dims[0]; i++ ) {

			ii[0] = i;
			cellState	s;
			int		d;
			getState( ii, s, d );

			switch( s ) {
				case csEmpty:
				case csWaiting:
					glIndexi( startCI );	
					break;
				case csFilled:
					glIndexi( getCI( d, totalCount ) );
					break;
				case csOutside:
				    break;
			}

			glBegin( GL_POINTS );
			    glVertex2i( ii[0], ii[1] );
			glEnd();
		}
	}
}

