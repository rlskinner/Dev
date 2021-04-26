#ifndef	_GlCellArray_
#define	_GlCellArray_

//
//   eat an image away based on different rules, and different seed points
//

#include	<math.h>
#include	<GL/glut.h>

#include	"enCellArray.h"

class	glCellArray : public enCellArray {
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
	int		getCI( int val, int count )
				{ return startCI + 1 + 
					rint(val*(double(rangeCI-1)/
						  double(count-1))); }
};


#endif	/* _GlCellArray_ */
