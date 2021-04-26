//
//   eat an image away based on different rules, and different seed points
//

#include	"newEdgeAction.h"


void
newEdgeAction::makeNbors()
{
}

void
newEdgeAction::doAction( cellArray *cells, int index[] )
{
	//
	//  every neighbor sharing an newEdge now gets greater weight
	//
	cellState       s;
	int             d;

	int	newEdge[2];
	newEdge[0] = index[0]-1;	newEdge[1] = index[1];
		cells->getState( newEdge, s, d );
			if( s == csEmpty ) {
				cells->add( newEdge, weight );
			}
	newEdge[0] = index[0]+1;	newEdge[1] = index[1];
		cells->getState( newEdge, s, d );
			if( s == csEmpty ) {
				cells->add( newEdge, weight );
			}
	newEdge[0] = index[0];	newEdge[1] = index[1]-1;
		cells->getState( newEdge, s, d );
			if( s == csEmpty ) {
				cells->add( newEdge, weight );
			}
	newEdge[0] = index[0];	newEdge[1] = index[1]+1;
		cells->getState( newEdge, s, d );
			if( s == csEmpty ) {
				cells->add( newEdge, weight );
			}

	newEdge[0] = index[0]-1;	newEdge[1] = index[1]-1;
		cells->getState( newEdge, s, d );
			if( s == csEmpty ) {
				cells->add( newEdge, weight );
			}
	newEdge[0] = index[0]+1;	newEdge[1] = index[1]+1;
		cells->getState( newEdge, s, d );
			if( s == csEmpty ) {
				cells->add( newEdge, weight );
			}
	newEdge[0] = index[0]+1;	newEdge[1] = index[1]-1;
		cells->getState( newEdge, s, d );
			if( s == csEmpty ) {
				cells->add( newEdge, weight );
			}
	newEdge[0] = index[0]-1;	newEdge[1] = index[1]+1;
		cells->getState( newEdge, s, d );
			if( s == csEmpty ) {
				cells->add( newEdge, weight );
			}

	weight += wtGain;
}



