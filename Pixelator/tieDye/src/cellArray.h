#ifndef	_cellArray_
#define	_cellArray_

//
//   eat an image away based on different rules, and different seed points
//

#include	<stdio.h>
#include	<sys/types.h>

class	eat;

//
//  states that cells can be in
//
enum	cellState { 
	    csEmpty = 0x01, 		// not touched
	    csWaiting = 0x02,		// in rand array
	    csFilled = 0x04,		// filled
	    csOutside = 0x08,		// outside cell array
	};

//
//  functions that can be performed on a cell's weight
//
enum	cellFunction {
	    cfSet,			// set value
	    cfAdd,			// add values
	    cfMultiply,			// multiply weights
	};

//
//  allocate all arrays to size+1, and use 1-based indexing
//
struct	randArray {
	size_t	dataSize;
	int	maxSize;
	int	size;
	u_char	*data;
	double	*wts;
	double	*cumWts;
	int	indUsed;
	int	indSize;
	int	*inds;
	int	autoUpdate;

	//
	//  debug flags
	//
	int	printSets;

	randArray( size_t dataSize );
	int	numWaiting()	{ return size-indUsed; }
	void	pick( void *pickedData );
	int	addData( void *data, double weight );	// returns index
	void	setWt( int index, double wt );
	void	clearWt( int index );		// remove from array
	double	getWt( int index )	{ return wts[index]; }

	double	getTotalWt()	{ return cumWts[1]; }

	void	assertHeap();

	void	setAutoUpdate( int on )	
			{ autoUpdate = on; }
	void	incUpdate( int index );		// this array element changed
	void	update();
};



class	cellArray {
public:
	int	nDim;
	int	*dims;
	int	*indexOffsets;
	char	*states;
	union cellDataUnion {
	    int		waitIndex;	// index in waitList array when waiting
	    float	weight;		// inhibited weight 
	    int		fillOrder;	// filled order
	} *cellData;

	int	setCntr;
	int	totalCount;
	randArray	*waitList;

	//
	//  debug flags
	//
	int	printPicks;

	cellArray( int nDim, int dims[] );
	virtual void	init( eat* );

	int		getTotalCount()	{ return totalCount; }

	int		offset( int index[] );

	void		getState( int index[], cellState &s, int &d );
	void		getStates( int index[], int n, int relNbors[], 
					cellState states[], int values[] );


	void		seed( int index[], double weight );
	// void		add( int index[], double weight );
	virtual	void	set( int index[] );

	void		opPos( cellFunction func, int n, int index[], int *relNbors, 
				float wgts[], u_char *enabled = NULL );

	void		pick( int index[] );
	int		numWaiting();

	virtual void	print() = 0;

	void	setAutoUpdate( int on )	{ waitList->setAutoUpdate( on ); }
	void	update()		{ waitList->update(); }
};

#endif	/* _cellArray_ */
