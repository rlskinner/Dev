//
//  generic shape for the ShapeMorph class
//

#include	"circleShape.h"

#include	<math.h>
#include	<gl/gl.h>

CircleShape::CircleShape()
{
    complexity = 100;
}


CircleShape::~CircleShape()
{
}


void
CircleShape::drawShape( ShapePoint *shape, u_long color )
{
    cpack( color );
    bgnclosedline();
    for( int i=0; i<numTemplatePts; i++ ) {
	v2f( shape[i].xy );
    }
    endclosedline();
}


void
CircleShape::init( Interval &theta, Interval &psi )
{
    Shape::init();
    theta.setMin( -0.5 );
    theta.setMax( 0.5 );
    psi.setMin( -0.5 );
    psi.setMax( 0.5 );
}


void   
CircleShape::initTemplateShape()
{
    for( int i=0; i<numTemplatePts; i++ ) {
	float	theta = 2*M_PI*i/float(numTemplatePts);
	tmplate[i].setX( 0.0 + 0.5*cosf( theta ) );
	tmplate[i].setY( 0.0 + 0.5*sinf( theta ) );
    }
}


void   
CircleShape::setShapeParameters()
{
    numTemplatePts = numIterations*complexity;
}





