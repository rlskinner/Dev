//
//   eat an image away based on different rules, and different seed points
//

#include	<stdio.h>
#include	<stdlib.h>
#include	<unistd.h>

#include	"txtEat.h"
#include	"txtCellArray.h"

void
txtEat::processEvent( int block ) 
{
    cells->print();

    while( block ) {
       sleep( 1 ); 
    }
}


void
txtEat::makeCellArray( int nDim, int dims[] )
{
    cells = new txtCellArray( nDim, dims );
}

int
main( int argc, char *argv[] )
{
    eatApp = new txtEat;
    eatApp->parseInput( argc, argv );
    eatApp->init();
    eatApp->doActions();		// don't block when done
}
