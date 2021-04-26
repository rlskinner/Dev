//
//   eat an image away based on different rules, and different seed points
//

#include	"cornerAction.h"


void
cornerAction::makeNbors()
{
    setNumNbors( 4 );
    setConstWgts();
    addState = csWaiting;
	int	*corner = nbors;
	corner[0] = -1;	corner[1] = -1;    corner += 2;
	corner[0] = +1;	corner[1] = -1;    corner += 2;
	corner[0] = -1;	corner[1] = +1;    corner += 2;
	corner[0] = +1;	corner[1] = +1;    corner += 2;
}



