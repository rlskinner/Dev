#ifndef _CTDisplay_h_
#define _CTDisplay_h_

#include <qwidget.h>
#include <qgl.h>

#include "CTSettings.h"
#include "TorusEvaluator.h"

#include <GL/gl.h>

class TorusTableAttractor;
class TorusTiler;
class spaceSampler;
class HilbertColorSequence;

class CTDisplay : public QGLWidget
	{
	protected:
		CTSettings settings_; // display settings
		TorusEvaluator torusEval_; // evaluator for torus
		TorusTableAttractor *attractor; // computes torus attractor 
		TorusTiler *tiler; // tiles torus to display
		spaceSampler *torusParamSampler; // samples space of the torus parameters
		HilbertColorSequence *colorSequence; // iterates through a color sequence

		//  (From AttractorMorph)
		float	torusParameterBounds[2][3];	// range of omega1, 2, epsilon

		//
		//  (From AttractorMorph) configurable parameters
		//
		int     numIterations;			// # of attractor iterations
		float	paramStepSize;			// step size in param space
		float	tileScale;			// size of lookup table
		int		tileSize;			// size of tile in pixels
		int		maxIntensity;			// # of hits to stop

	public:
		CTDisplay(bool fullScreen, WId window = 0);

		int exec();

	protected:
		virtual void initializeGL();
		virtual void resizeGL(int width, int height);
		virtual void paintGL();
		virtual void timerEvent(QTimerEvent*);

		static const int timer_interval = 10;	// timer interval (millisec)
	};

#endif // _CTDisplay_h_
