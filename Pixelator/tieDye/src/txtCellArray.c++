//
//   eat an image away based on different rules, and different seed points
//

#include	<stdio.h>

#include	"txtCellArray.h"

txtCellArray::txtCellArray( int nd, int d[] )
	: cellArray( nd, d )
{
}


void
txtCellArray::print()
{
	if( nDim != 2 ) {
		printf( "sorry, can't print %dD version", nDim );
	}
	
	printf( "\n    " );
	for( int i=0; i<dims[0]; i++ ) {
	    printf( "%4d", i );
	}
	printf( "\n" );

	int	ii[2];
	for( int j=dims[1]-1; j>=0; j-- ) {
		ii[1] = j;
		printf( "%3d ", j );
		for( int i=0; i<dims[0]; i++ ) {
			ii[0] = i;
			cellState	s;
			int		d;
			getState( ii, s, d );
			switch( s ) {
				case csEmpty:
					printf( "   ." );
					break;
				case csWaiting:
					printf( "%4d", -d );
					break;
				case csFilled:
					printf( "%4d", d );
					break;
				case csOutside:
				    break;
			}
		}
		printf( "\n" );
	}
}



