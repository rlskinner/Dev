//
//  generic shape for the ShapeMorph class
//
#ifndef	__shape_h__
#define	__shape_h__

#include	<TorusAttractor.h>
#include	<interval.h>
#include	<sys/types.h>

struct	ShapePoint {
    float	xy[2];

    void	setX( float v ) { xy[0] = v; }
    float	getX() { return xy[0]; }

    void	setY( float v ) { xy[1] = v; }
    float	getY() { return xy[1]; }
};

class Shape {
public:
		Shape();
    virtual	~Shape();

    virtual	void	draw( TorusAttractor *torus, u_long color );
    virtual	void	init( Interval &theta, Interval &psi ) = 0;
    virtual	void	redraw();

    		void	setNumShapes( int n ) { numShapes = n; }
		void	setComplexity( int c ) { complexity = c; }
		void	setNumIterations( int n ) { numIterations = n; }
		void	setColorFade( float f ) { fade = f; }

protected:
    int		numIterations;		// number of iterations of each shape

    int		complexity;		// complexity of each shape implies
    int		numTemplatePts;		// the number of points in template
    ShapePoint	*tmplate;		// original shape

    int		numShapes;		// number of shapes there are
    int		numActiveShapes;	// gets reset on redraw()
    ShapePoint	**shapes;		// current and past shapes
    int		curShape;		// index of current shape

    u_long	*shapeColors;		// colors of each shape
    float	fade;

    virtual	void	drawShape( ShapePoint *shape, u_long color ) = 0;
		void	xformTemplate( TorusAttractor *torus );
		u_long	fadeColor( u_long color, float fadeFactor );

    virtual	void	setShapeParameters() = 0;

		void	incrementCurrentShape();

    virtual	void	init();
    virtual	void	allocateResources();
    virtual	void	initTemplateShape() = 0;
    virtual	void	initCurrentShape();
};

#endif	/* __shape_h__ */
