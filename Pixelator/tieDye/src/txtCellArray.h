#ifndef	_txtCellArray_
#define	_txtCellArray_

//
//   eat an image away based on different rules, and different seed points
//

#include	"cellArray.h"

class	txtCellArray : public cellArray {
public:

	txtCellArray( int nDim, int dims[] );

	virtual	void	print();
};


#endif	/* _txtCellArray_ */
