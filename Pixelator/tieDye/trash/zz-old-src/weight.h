#ifndef	_weight_h_
#define	_weight_h_

//
//  define a anstract weight class that can change the weight based
//	on location (absolute or relative), or history, etc.
//

class	weight {
protected:
	int	isConst;
	double	constWgt;
	virtual	double	getFunctionalWgt( int nDim, int abs[], int rel[] );

public:
	weight() { isConst = 0; }
	virtual	~weight();

	virtual	void init( int nDim, int dims[] );

	double	getWgt( int nDim, int abs[], int rel[] )
			{ return isConst ? constWgt 
					 : getFunctionalWgt( nDim, abs, rel ); }
};

#endif	/* _weight_h_ */
