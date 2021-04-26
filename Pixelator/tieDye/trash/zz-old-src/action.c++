
#include	"action.h"

action::action( weight *_wgt )
{ 
    next = NULL; 
    wgt = _wgt; 
    dims = NULL;

    numNbors = 0;
    nbors = NULL;
    nborWgts = NULL;
    addState = csEmpty;
}


void	
action::init( int _nDim, int _dims[] )
{
	nDim = _nDim;
	dims = new int[nDim];
	for( int i=0; i<nDim; i++ ) 
		dims[i] = _dims[i];

	wgt->init( _nDim, dims );
	makeNbors();
}
	

void
action::setNumNbors( int nb )
{
    numNbors = nb;
    nbors = new int[2*nb];
    nborWgts = new float[nb];
}


//
//  default action: foreach neighbor, apply its relative weight and
//	add to cells
//
void
action::doAction( cellArray *cells, int index[] )
{
    int		*nb = nbors;
    for( int i=0; i<numNbors; i++, nb += 2 ) {
	int	addr[2];
	addr[0] = index[0] + nb[0];
	addr[1] = index[1] + nb[1];

	float	nwgt = (nborWgts == NULL) ? 1.0 : nborWgts[i];

	cellState	s;
	int		d;
	if( addState == csEmpty ) {	// cell state must be empty
	    cells->getState( addr, s, d );
	    if( s == csEmpty ) {
		cells->add( addr, nwgt*wgt->getWgt( nDim, addr, nb ) );
	    }
	} else {			// accumulate weights
	    cells->add( addr, nwgt*wgt->getWgt( nDim, addr, nb ) );
	}
    }
}



