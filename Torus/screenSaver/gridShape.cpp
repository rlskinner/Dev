//
//  generic shape for the ShapeMorph class
//

#include	"gridShape.h"

#include	<math.h>
#include	<gl/gl.h>

GridShape::GridShape()
{
    complexity = 1;
}


GridShape::~GridShape()
{
}


void
GridShape::drawShape( ShapePoint *shape, u_long color )
{
    cpack( color );
    int	ptIndex = 0;
    for( int nl=0; nl<numLines; nl++ ) {
	bgnline();
	for( int i=0; i<numPtsPerLine; i++ ) {
	    v2f( shape[ptIndex++].xy );
	}
	endline();
    }
}


void
GridShape::init( Interval &theta, Interval &psi )
{
    Shape::init();
    theta.setMin( -0.5 );
    theta.setMax( 0.5 );
    psi.setMin( -0.5 );
    psi.setMax( 0.5 );
}


void   
GridShape::initTemplateShape()
{
    int	ptIndex = 0;
    
    //  do horizontal lines
    int	i, j;
    for( j=0; j<numLines/2; j++ ) {
	float	y = -0.5 + float(j)/(numLines/2-1);
	for( i=0; i<numPtsPerLine; i++ ) {
	    tmplate[ptIndex].setX( -0.5 + float(i)/(numPtsPerLine-1) );
	    tmplate[ptIndex].setY( y );
	    ptIndex++;
	}
    }
    for( i=0; i<numLines/2; i++ ) {
	float	x = -0.5 + float(i)/(numLines/2-1);
	for( j=0; j<numPtsPerLine; j++ ) {
	    tmplate[ptIndex].setX( x );
	    tmplate[ptIndex].setY( -0.5 + float(j)/(numPtsPerLine-1) );
	    ptIndex++;
	}
    }

}


void   
GridShape::setShapeParameters()
{
    numLines = 2*(numGrids+1);		// number of lines to draw
    numPtsPerLine = complexity*numGrids+1;	// complex = # points on grid
    numTemplatePts = numLines*numPtsPerLine;
}





