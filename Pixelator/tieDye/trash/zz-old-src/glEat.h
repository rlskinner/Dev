//
//  eat application class renders to gl window
//

#include	"eat.h"

class	glEat : public eat {
protected:

public:
    virtual	void	makeCellArray( int nDim, int dims[] );
    virtual	void	processEvent( int block = 0 );
};

