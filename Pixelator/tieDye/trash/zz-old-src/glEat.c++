//
//   eat an image away based on different rules, and different seed points
//

#include	<stdio.h>
#include	<stdlib.h>
#include	<unistd.h>

#include	<device.h>

#include	"glEat.h"
#include	"glCellArray.h"

//
//  process queue events
//
void
glEat::processEvent( int block )
{
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
}


void
glEat::makeCellArray( int nDim, int dims[] )
{
    cells = new glCellArray( nDim, dims );
}


main( int argc, char *argv[] )
{
	eatApp = new glEat;
	eatApp->parseInput( argc, argv );
	eatApp->init();
	eatApp->doActions( TRUE );
}
		
		
	

