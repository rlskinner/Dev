//
//  abstract class to generate different color sequences.
//	It returns colors that are no more than stepSize apart
//	(in RGB space).  
//

#include	<colorSequence.h>

ColorSequence::ColorSequence()
{
    rgb[ColorSequence::red] = rgb[ColorSequence::green] = rgb[ColorSequence::blue] = 1.0;
}

ColorSequence::ColorSequence( float step )
{
    rgb[ColorSequence::red] = rgb[ColorSequence::green] = rgb[ColorSequence::blue] = 1.0;
    setStepSize( step );
}


void
ColorSequence::setStepSize( float step )
{
    stepSize = step;
}

//
//  get color in different formats
//
void
ColorSequence::getFloatColor( float outputRGB[3] )
{
    outputRGB[ColorSequence::red] = rgb[ColorSequence::red];
    outputRGB[ColorSequence::green] = rgb[ColorSequence::green];
    outputRGB[ColorSequence::blue] = rgb[ColorSequence::blue];
}

//
// IRIS GL format
//
void
ColorSequence::getABGRColor( unsigned long &abgr )
{
    abgr = (255 << 24)
	 | (int(255.0*rgb[ColorSequence::blue]) << 16)
	 | (int(255.0*rgb[ColorSequence::green]) << 8)
	 |  int(255.0*rgb[ColorSequence::red]);
}

//
// OPEN GL format
//
void
ColorSequence::getRGBAColor( unsigned char rgba[4] )
{
    rgba[ColorSequence::red] = int(255.0*rgb[ColorSequence::red]);
    rgba[ColorSequence::green] = int(255.0*rgb[ColorSequence::green]);
    rgba[ColorSequence::blue] = int(255.0*rgb[ColorSequence::blue]);
    rgba[ColorSequence::alpha] = 255;
}

