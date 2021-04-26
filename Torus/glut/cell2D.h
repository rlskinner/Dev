#ifndef	_cell2D_h_
#define	_cell2D_h_
//
//	class to enable better code sharing and modularity
//	for torus algorithms & GLUT
//

#include <GL/gl.h>

#include <TorusEvaluator.h>

#include "glutApp.h"


// we should really make this class completely abstract,
//	with no data, but cheat for now
class	cell2D : public glutApp {
public:
    cell2D();

protected:
    virtual void	createWindows();

    virtual	void	display();
    virtual	void	displayInit();
    virtual	void	idle();
    virtual	void	idleInit();
    virtual	void	keyboard( unsigned char key, int x, int y );
    virtual	void	mouse( int button, int state, int x, int y );

    virtual	void	init( int &argc, char *argv[] );

	enum { cMaxHistogramValue = 255 };
	enum HistogramMode
		{
		cLinearMode = 0,
		cLogarithmicMode = 1,
		cExponentialMode = 2,
		cGamma = 3,
		cNumModes
		};

	void histogramToColor(int count, float *red, float *green, float *blue);
	HistogramMode histogramMode_;
	float *histogramTables_[cNumModes];

	float gamma_;
	void computeGammaTable(float table[]);

    TorusEvaluator	*_torus;
    int		*_cells; // histogram
    float	*_pts;

private:

};

#endif	// _cell2D_h_
