
#include	"action.h"

action::action( weight *_wgt )
{ 
    next = NULL; 
    wgt = _wgt; 
    dims = NULL;

    numNbors = 0;
    nbors = NULL;
    relNborWgts = NULL;
    newNborWgts = NULL;
    nborEnable = NULL;
    nborStates = NULL;
    nborValues = NULL;

    // addState = csEmpty;

    selectWgts = awAll;
    selectStates = int(csEmpty|csWaiting);
    function = cfAdd;
}


action::~action()
{
    delete nbors;
    delete relNborWgts;
    delete newNborWgts;
    delete nborEnable;
    delete nborStates;
    delete nborValues;
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
    relNborWgts = new float[nb];
    newNborWgts = new float[nb];
    nborEnable = new u_char[nb];
    nborStates = new cellState[nb];
    nborValues = new int[nb];
}


//
//  select weights depending on numerical properties
//
void   
action::selectWgtValues()
{
    int	i;
#define	SELECT(EXPR)							\
    for( i=0; i<numNbors; i++ ) {					\
	nborEnable[i] = EXPR;						\
    }

    float	min, max;
    int		minI, maxI;
    switch( selectWgts ) {
	case awAll:
	    break;
	case awMin:
	    nborEnable[0] = FALSE;
	    minI = 0;
	    min = newNborWgts[0];
	    for( i=1; i<numNbors; i++ ) {
		nborEnable[i] = FALSE;
		if( newNborWgts[i] < min ) {
		    min = newNborWgts[i];
		    minI = i;
		}
	    }
	    nborEnable[minI] = TRUE;
	    break;
	case awMax:
	    nborEnable[0] = FALSE;
	    maxI = 0;
	    max = newNborWgts[0];
	    for( i=1; i<numNbors; i++ ) {
		nborEnable[i] = FALSE;
		if( newNborWgts[i] > max ) {
		    max = newNborWgts[i];
		    maxI = i;
		}
	    }
	    nborEnable[maxI] = TRUE;
	    break;
	case awPositive:
	    SELECT(newNborWgts[i] >= 0.0);
	    break;
	case awNegative:
	    SELECT(newNborWgts[i] <= 0.0);
	    break;
    }

#undef	SELECT
}


//
//  select Positions depending on cell states
//
void
action::selectCellStates( cellArray *cells, int index[] )
{
    cells->getStates( index, numNbors, nbors, nborStates, nborValues );
    for( int i=0; i<numNbors; i++ ) {
	if( nborEnable[i] )
	    nborEnable[i] = (nborStates[i] & selectStates) != 0;
    }
}

//
//  default action: foreach neighbor, apply its relative weight and
//	add to cells
//
void
action::doAction( cellArray *cells, int index[] )
{
    int	i;

    for( i=0; i<numNbors; i++ ) nborEnable[i] = TRUE;
    wgt->getWgts( nDim, numNbors, index, nbors, newNborWgts );
    if( relNborWgts != NULL )
	for( i=0; i<numNbors; i++ ) newNborWgts[i] *= relNborWgts[i];
    selectWgtValues();
    selectCellStates( cells, index );
    cells->opPos( function, numNbors, index, nbors, newNborWgts, nborEnable );
}




