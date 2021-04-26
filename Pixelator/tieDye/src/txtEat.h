//
//  eat application class "renders" to stdout
//

#include	"eat.h"

class	txtEat : public eat {
protected:

public:
    virtual	void	makeCellArray( int nDim, int dims[] );
    virtual	void	processEvent( int block = 0 );
};

