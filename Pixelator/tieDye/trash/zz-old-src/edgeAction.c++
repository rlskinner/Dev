//
//   eat an image away based on different rules, and different seed points
//

#include	"edgeAction.h"


void
edgeAction::makeNbors()
{
    addState = csWaiting;
    setNumNbors( 4 );
    setConstWgts();
    int	*edge = nbors;
	edge[0] = -1;	edge[1] = 0;	edge += 2;
	edge[0] = +1;	edge[1] = 0;	edge += 2;
	edge[0] = 0;	edge[1] = -1;	edge += 2;
	edge[0] = 0;	edge[1] = +1;	edge += 2;
}

