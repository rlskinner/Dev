//
//   eat an image away based on different rules, and different seed points
//

#include	"nborAction.h"

nborAction::nborAction(weight *wgt, int connect )
	: action( wgt )
{
    connectedness = connect;
}


void
nborAction::makeNbors()
{
    if( connectedness == 8 )
        setNumNbors( 8 );
    else
        setNumNbors( 4 );
    setConstWgts();

    int		*nb = nbors;
    if( connectedness == 8 ) {
    	nb[0] = -1;	nb[1] = -1;	nb += 2;
    	nb[0] = +1;	nb[1] = +1;	nb += 2;
    	nb[0] = +1;	nb[1] = -1;	nb += 2;
    	nb[0] = -1;	nb[1] = +1;	nb += 2;
    }
    
    nb[0] = -1;	nb[1] = 0;	nb += 2;
    nb[0] = +1;	nb[1] = 0;	nb += 2;
    nb[0] = 0;	nb[1] = -1;	nb += 2;
    nb[0] = 0;	nb[1] = +1;	nb += 2;
}



