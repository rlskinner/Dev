//
//	2D cell population counter
//
#ifdef WIN32
#include <windows.h>
#endif

#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glut.h>

#include <stdio.h>
#include <math.h>

#include <iostream>

#include <randomUtil.h>

#include "cell2D.h"

const	int	NUM_PTS = 16;

using namespace std;

cell2D::cell2D()
    : _cells( NULL )
    , _pts( NULL )
	, histogramMode_(cLinearMode)
	, gamma_(1.0)
	{
	// initialize the histogram lookup tables
	float scale;
	for(int i=0; i<cNumModes; ++i)
		{
		histogramTables_[i] = new float[cMaxHistogramValue+1];

		switch(i)
			{
			// linear histogram lookup
			case cLinearMode:
				for(int i=0; i<=cMaxHistogramValue; ++i)
					{
					histogramTables_[cLinearMode][i] = i/static_cast<float>(cMaxHistogramValue);
					}
				break;

			// logarithmic histogram lookup
			case cLogarithmicMode:
				scale = 1.0/log(static_cast<float>(cMaxHistogramValue));
				histogramTables_[cLogarithmicMode][0] = 0.0f; // special value
				for(int i=1; i<=cMaxHistogramValue; ++i)
					{
					histogramTables_[cLogarithmicMode][i] = scale*log(static_cast<float>(i));
					}
				break;

			// exponential histogram lookup
			case cExponentialMode:
				for(int i=0; i<=cMaxHistogramValue; ++i)
					{
					histogramTables_[cExponentialMode][i] = exp(static_cast<float>(i-cMaxHistogramValue));
					}
				break;

			case cGamma:
				computeGammaTable(histogramTables_[cGamma]);
				break;
			}
		}
	}

void
cell2D::init( int &argc, char *argv[] )
{
    glutApp::init( argc, argv );

    _cells = new int[_width*_height];
    memset( _cells, 0, _width*_height*sizeof(int) );

    _pts = new float[2*NUM_PTS];
    for( int i=0; i<2*NUM_PTS; i++ ) {
	_pts[i] = drand48();
    }

    _torus = new TorusEvaluator( 2 );
}

void
cell2D::createWindows()
{
//     glutInitDisplayMode( GLUT_INDEX | GLUT_SINGLE );
    glutInitDisplayMode( GLUT_RGBA | GLUT_SINGLE );
    glutInitWindowSize( 2*_width, 2*_height );
    _wid = glutCreateWindow( "OGL torus" );
}

void
cell2D::display()
{
#if	0
    glRasterPos2f( 0, 0 );
    glDrawPixels( _width, _height, 
    		GL_RGBA, GL_UNSIGNED_BYTE, _cells );

    glRasterPos2i( _width, 0 );
    glDrawPixels( _width, _height, 
    		GL_RGBA, GL_UNSIGNED_BYTE, _cells );

    glRasterPos2i( 0, _height );
    glDrawPixels( _width, _height, 
    		GL_RGBA, GL_UNSIGNED_BYTE, _cells );

    glRasterPos2i( _width, _height );
    glDrawPixels( _width, _height, 
    		GL_RGBA, GL_UNSIGNED_BYTE, _cells );
#endif
	glClear(GL_COLOR_BUFFER_BIT);
}

void
cell2D::displayInit()
{
// 	for( int i=0; i<256; i++ ) {
// 	    glutSetColor( i, float(i)/255.0, float(i)/255.0, float(i)/255.0 );
// 	}

    memset( _cells, 0, _width*_height*sizeof(int) );

	glViewport( 0, 0, 2*_width-1, 2*_height-1 );

	glMatrixMode( GL_PROJECTION );
	glLoadIdentity();
	glOrtho( 0.0, 2*_width-1.0, 
		 0.0, 2*_height-1.0, 
		 -1.0, 1.0 );

	glMatrixMode( GL_MODELVIEW );
	glLoadIdentity();

	glClearColor(0.0, 0.0, 0.0, 1.0);
	glClear( GL_COLOR_BUFFER_BIT );

	display();
}

void
cell2D::idle()
{
    _torus->eval( NUM_PTS, _pts, _pts );

    glBegin( GL_POINTS );
    for( int i=0; i<2*NUM_PTS; i += 2 ) {
	int	x = _pts[i]*_width;
	int	y = _pts[i+1]*_height;

	if( _cells[y*_width+x] < cMaxHistogramValue ) {
		_cells[y*_width+x]++;
		float r, g, b;
		histogramToColor(_cells[y*_width+x], &r, &g, &b);
		glColor3f(r, g, b);
// 	    glIndexub( ++(*c) );
	    glVertex2i( x,        y );
	    glVertex2i( x+_width, y );
	    glVertex2i( x,        y+_height );
	    glVertex2i( x+_width, y+_height );
	}
    }
    glEnd();
}

void
cell2D::idleInit()
{
    idle();
}

void
cell2D::keyboard( unsigned char key, int x, int y )
{
	float cGammaIncr = 0.1;

	switch( key ) {
		case 'm':
			{
			int m = histogramMode_+1;
			if(cNumModes == m)
				m = cLinearMode;
			histogramMode_ = static_cast<HistogramMode>(m);
			switch(histogramMode_)
				{
				case cLinearMode:		cout << "Linear display" << endl;	break;
				case cLogarithmicMode:	cout << "Log display" << endl;		break;
				case cExponentialMode:	cout << "Exp display" << endl;		break;
				case cGamma:			cout << "Gamma display" << endl;	break;
				}
			displayInit();
			}
			break;

		case 'g':
			gamma_ -= cGammaIncr;
			computeGammaTable(histogramTables_[cGamma]);
			displayInit();
			break;

		case 'G':
			gamma_ += cGammaIncr;
			computeGammaTable(histogramTables_[cGamma]);
			displayInit();
			break;

		default:
			defaultKeyboardCB( key, x, y );
			break;
	}
}

void
cell2D::mouse( int button, int state, int x, int y )
{
    if( state == GLUT_DOWN ) {
	float	omega[2] = { float(x)/_width, float(y)/_height };
	_torus->setOmega( omega );
	displayInit();
    }
}


//
//  convert the given histogram count to a color
//
//  Currently uses a logarithmic scale.
//
//  Return red, green and blue to allow for a color table
//
void
cell2D::histogramToColor(int count, float *red, float *green, float *blue)
	{
	if(0 <= count && count <= cMaxHistogramValue)
		{
		*red = *green = *blue = histogramTables_[histogramMode_][count];
		}
	else
		{
		*red = *green = *blue = 0.0f;
		}
	}


// 
// compute gamma correction lookup table for the current gamma value
//
void
cell2D::computeGammaTable(float table[])
	{
	cout << "gamma_ = " << gamma_ << endl;

	histogramTables_[cGamma][0] = 0.0;
	for(int i=1; i<=cMaxHistogramValue; ++i)
		{
		float r = i/static_cast<float>(cMaxHistogramValue);
		histogramTables_[cGamma][i] = pow(r, gamma_);
		}
	}
