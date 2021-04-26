//
//   eat an image away based on different rules, and different seed points
//

#include	<stdio.h>
#include	<gl.h>
#include	<device.h>

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

	if( e->setPosition ) {
		prefposition( e->wx, e->wx+dims[0]-1, 
			      e->wy, e->wy+dims[1]-1 );
	}

	foreground();
	prefsize(  e->dims[0], e->dims[1] );
	winopen( "glEat" );
	winconstraints();
	cmode();

	qdevice( ESCKEY );

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

		mapcolor( start, 128, 128, 128 );
		for( int i=start+1; i<start+range; i++ ) {
			int	band = i / 128;
			if( band % 2 ) {
				mapcolor( i, 255, 255, 255 );
			} else {
				mapcolor( i, 0, 0, 0 );
			}
		}
	}
}


void
glCellArray::set( int index[] )
{
	Colorindex ci = getCI( setCntr, totalCount );
	color( ci );
	pnt2i( index[0], index[1] );
	cellArray::set( index );
}


void
glCellArray::print()
{
	if( nDim != 2 ) {
		printf( "sorry, can't print %dD version", nDim );
	}
	
	int	total = dims[0]*dims[1];
	int	cntr = 0;

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
					color( startCI );	
					break;
				case csFilled:
					color( getCI( d, totalCount ) );
					break;
			}

			pnt2i( ii[0], ii[1] );
		}
	}
}

