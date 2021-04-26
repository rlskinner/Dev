#ifndef	_cellArray_
#define	_cellArray_

//
//   eat an image away based on different rules, and different seed points
//


class	eat;

enum	cellState
	{ csEmpty, 			// not touched
	  csWaiting,			// in rand array
	  csFilled			// filled
	};

//
//  allocate all arrays to size+1, and use 1-based indexing
//
struct	randArray {
	int	nDim;
	int	maxSize;
	int	size;
	int	*data;
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

	randArray( int nDim );
	int	numWaiting()	{ return size-indUsed; }
	void	pick( int index[] );
	int	add( int cell[], double weight = 1.0 );
	void	add( int heap, double weight = 1.0 );
	void	setWt( int heap, double wt );
	void	clearWt( int heap );		// "remove" from heap

	double	getTotalWt()	{ return cumWts[1]; }

	void	assertHeap();

	void	setAutoUpdate( int on )	
			{ autoUpdate = on; }
	void	incUpdate( int heap );
	void	update();
};



class	cellArray {
public:
	int	nDim;
	int	*dims;
	int	*offsets;
	int	*data;
	char	*states;
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

	void		seed( int index[], double weight );
	void		add( int index[], double weight );
	virtual	void	set( int index[] );

	void		pick( int index[] );
	int		numWaiting();

	virtual void	print() = 0;

	void	setAutoUpdate( int on )	{ waitList->setAutoUpdate( on ); }
	void	update()		{ waitList->update(); }
};

#endif	/* _cellArray_ */
