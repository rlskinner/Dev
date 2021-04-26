//
//  generic shape for the ShapeMorph class
//

#include	"shape.h"

class CircleShape : public Shape {
public:
		CircleShape();
    virtual	~CircleShape();

protected:
    virtual	void    drawShape( ShapePoint *shape, u_long color );
    virtual	void	init( Interval &theta, Interval &psi );
    virtual	void	initTemplateShape();
    virtual     void    setShapeParameters();
};
