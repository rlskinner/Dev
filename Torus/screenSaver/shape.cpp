//
//  generic shape for the ShapeMorph class
//

#include	"shape.h"

#include	<unistd.h>

Shape::Shape()
{
    numIterations = 1;
    numShapes = 10;
    numActiveShapes = 0;
    curShape = 0;

    fade = 1.0;

    tmplate = NULL;
    shapes = NULL;
    shapeColors = NULL;

    //
    //  These values are dependent on the subclass, but can
    //	be used by this class.
    //
    complexity = -1;
    numTemplatePts = -1;
}

Shape::~Shape()
{
    delete tmplate;
    for( int i=0; i<numShapes; i++ ) {
	delete shapes[i];
    }
    delete shapes;
    delete shapeColors;
}

void
Shape::draw( TorusAttractor *torus, u_long color )
{
    xformTemplate( torus );

    shapeColors[curShape] = color;
    for( int i=0; i<numActiveShapes; i++ ) {
	int	s = ( curShape+1 + i ) % numActiveShapes;
	drawShape( shapes[s], shapeColors[s] );
	shapeColors[s] = fadeColor( shapeColors[s], fade );
    }

    incrementCurrentShape();
}

void
Shape::init()
{
    allocateResources();
    initTemplateShape();
    initCurrentShape();
}

void
Shape::redraw()
{
    initCurrentShape();
}

void
Shape::xformTemplate( TorusAttractor *torus )
{
    for( int i=0; i<numTemplatePts; i++ ) {
	double theta = tmplate[i].getX();
	double psi = tmplate[i].getY();

	for( int n=0; n<numIterations; n++ ) {
	    torus->mapPoint( theta, psi, &theta, &psi );
	}

	shapes[curShape][i].setX( theta );
	shapes[curShape][i].setY( psi );
    }
}

u_long
Shape::fadeColor( u_long color, float fadeFactor )
{
    u_long newColor = color & 0xff000000;
    for( int c = 0; c<3; c++ ) {
	u_long	byteColor = 0xff & (color >> (c*8));
	byteColor = u_long(255.0*( (byteColor/255.0)*fadeFactor) );
	newColor |= byteColor << (c*8);
    }
    return newColor;
}

void
Shape::initCurrentShape()
{
    numActiveShapes = 0;
    curShape = 0;
}

void
Shape::incrementCurrentShape()
{
    if( numActiveShapes < numShapes ) 
	numActiveShapes++;

    curShape = (curShape+1) % numShapes;
}

void
Shape::allocateResources()
{
    setShapeParameters();

    tmplate = new ShapePoint[numTemplatePts];
    shapes = new ShapePoint*[numShapes];
    for( int i=0; i<numShapes; i++ ) {
	shapes[i] = new ShapePoint[numTemplatePts];
    }
    shapeColors = new u_long[numTemplatePts];
}

