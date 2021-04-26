#ifndef	_enWeight_h_
#define	_enWeight_h_

//
//  define a anstract weight class that can change the weight based
//	on location (absolute or relative), or history, etc.
//

class	enWeight {
protected:
	double	constWgt;
#ifdef	OLD_STYLE
	int	isConst;
	virtual	double	getFunctionalWgt( int nDim, int abs[], int rel[] );
#endif

public:
	enWeight( double val = 1.0 ) { constWgt = val; }
	virtual	~enWeight();

	virtual	void init( int nDim, int dims[] );

#ifdef	OLD_STYLE
	double	getWgt( int nDim, int abs[], int rel[] )
			{ return isConst ? constWgt 
					 : getFunctionalWgt( nDim, abs, rel ); }
#endif
	
	virtual	void	getWgts( int nDim, int n, int abs[], 
					int *rel, float wgts[] );
};

#endif	/* _enWeight_h_ */
