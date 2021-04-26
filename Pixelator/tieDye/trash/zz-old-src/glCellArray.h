#ifndef	_glCellArray_
#define	_glCellArray_

//
//   eat an image away based on different rules, and different seed points
//

#include	<gl.h>
#include	<math.h>

#include	"cellArray.h"

class	glCellArray : public cellArray {
protected:
	int	startCI;
	int	rangeCI;

public:

	glCellArray( int nDim, int dims[] );
	virtual void	init( eat* );

	void		set( int index[] );
	virtual	void	print();

	void		setIndexRange( int start, int size )
				{ startCI = start; rangeCI = size; }
	Colorindex	getCI( int val, int count )
				{ return startCI + 1 + 
					rint(val*(double(rangeCI-1)/
						  double(count-1))); }
};


#endif	/* _glCellArray_ */
