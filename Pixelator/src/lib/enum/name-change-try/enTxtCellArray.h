#ifndef	_TxtCellArray_
#define	_TxtCellArray_

//
//   eat an image away based on different rules, and different seed points
//

#include	"enCellArray.h"

class	txtCellArray : public enCellArray {
public:

	txtCellArray( int nDim, int dims[] );

	virtual	void	print();
};


#endif	/* _enTxtCellArray_ */
