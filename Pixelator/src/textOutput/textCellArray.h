#ifndef	_textCellArray_
#define	_textCellArray_

//
//   eat an image away based on different rules, and different seed points
//

#include	"cellArray.h"

class	TextCellArray : public CellArray {
public:

	TextCellArray(Dimensions const& dims);

	virtual	void	print();
};


#endif	/* _textCellArray_ */
