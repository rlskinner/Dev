//
//  generic shape for the ShapeMorph class
//

#include	"shape.h"

const	int	numGrids = 5;

class GridShape : public Shape {
public:
		GridShape();
    virtual	~GridShape();

protected:
    virtual	void    drawShape( ShapePoint *shape, u_long color );
    virtual	void	init( Interval &theta, Interval &psi );
    virtual	void	initTemplateShape();
    virtual     void    setShapeParameters();

    int numLines;     			// number of lines to draw
    int numPtsPerLine;			// complex = # points on grid side

};
