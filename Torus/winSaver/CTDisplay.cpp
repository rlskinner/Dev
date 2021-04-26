#include "CTDisplay.h"

#include "spaceSampler.h"
#include "HilbertColorSequence.h"
#include "TorusTableAttractor.h"
#include "TorusTiler.h" 
#include <fstream>

using namespace std;

ofstream CTout("c:/temp/CT.out");

CTDisplay::CTDisplay(bool fullScreen, WId window)
	: QGLWidget()
	, settings_()
	, torusEval_(2)
	{
// CTout << "CTDisplay::CTDisplay(full=" << fullScreen << ", WId=" << window << ")" << endl;
// Sleep(5);
// 	if(window != 0)
// 		QWidget::create(window, false, TRUE);
// 
// CTout << "CTDisplay::CTDisplay window created" << endl;
// Sleep(5);
// 
//     startTimer(timer_interval);

    //
    //  create samplers for the parameter and color spaces
    //
    float	colorStep = 1.0/32;		// don't configure this
    colorSequence = new HilbertColorSequence( colorStep );
    torusParamSampler = new spaceSampler( paramStepSize, 3 );
    torusParamSampler->setBounds( torusParameterBounds[0], 
				 torusParameterBounds[1] );

#if	0
    //
    //  do graphics initialization
    //
    long	xPixels = getMaxXPixelSize();
    long	yPixels = getMaxYPixelSize();

    //
    // set up for full screen,
    //	and clear screen to black
    //
    foreground();
    prefposition( 0, xPixels-1, 0, yPixels-1 );
    winopen( "Chaos Morph" );
    RGBmode();
    // doublebuffer();
    gconfig();

    ortho2(-0.5,xPixels-0.5,-0.5,yPixels-0.5);
    cpack( 0xff000000 );
    clear();

    //
    //  calculate tiling, given screen size and tile size
    //
    long numColumns = xPixels/tileSize;		// let it truncate for now
    long numRows = yPixels/tileSize;

    //
    //  create the attractor function and a tiler for it
    //
    attractor = new TorusTableAttractor( int(tileScale*tileSize), 
				   int(tileScale*tileSize) );
    tiler = new TorusTiler( tileSize, tileSize, int(numColumns), int(numRows) );
    tiler->setBackgroundColor( 0xff000000 );	// black
    if( maxIntensity > 0 ) {
	tiler->setMaxIntensity( maxIntensity );
    } else {
	tiler->setNumIterations( numIterations );
    }
#endif
	}


int CTDisplay::exec()
	{
	return -1;
	}


void CTDisplay::initializeGL()
	{
CTout << "CTDisplay::initializeGL()" << endl;
Sleep(5);

	}


void CTDisplay::resizeGL(int width, int height)
	{
CTout << "CTDisplay::resizeGL()" << endl;
Sleep(5);

	}


void CTDisplay::paintGL()
	{
CTout << "CTDisplay::paintGL()" << endl;
Sleep(5);

// 	static int c = 7;
// 
// 	float r = (c & 1) ? 1.0 : 0.0;
// 	float g = (c & 2) ? 1.0 : 0.0;
// 	float b = (c & 4) ? 1.0 : 0.0;
// 
// 	c = (c+1) % 8;
// 
// 	glClearColor(r, g, b, 1.0);
// 	glClear(GL_COLOR_BUFFER_BIT);
// 
    float	parameters[3];
    torusParamSampler->getSample( parameters );
    
    attractor->setOmega1( parameters[0] );
    attractor->setOmega2( parameters[1] );
    attractor->setEpsilon( parameters[2] );

    unsigned long	color;
    colorSequence->getABGRColor( color );
    tiler->setDrawingColor( color );

    float	frameTime = tiler->drawTiledImage( attractor );

    torusParamSampler->stepSample();
    colorSequence->stepColor();
	}


void CTDisplay::timerEvent(QTimerEvent*)
	{
	updateGL();
	}


