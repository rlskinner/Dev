//
//  Generate a color sequence that traverses the 3 brightest
//	faces of the color cube in hilbert patterns
//

#include	<hilbertSequence.h>
#include	<colorSequence.h>

class	HilbertColorSequence : public ColorSequence {
public:
    	HilbertColorSequence();
	HilbertColorSequence( float step );
	~HilbertColorSequence();

    virtual	void	setStepSize( float stepSize );
    virtual	void	stepColor();

protected:
    void	init();			// do setup 

    HilbertSequence	*hilbertSequence;
    int			numHilbertPoints;	// number of points in sequence
    HilbertPoint	*hilbertPoints;		// actual sequence
    float		hilbertScale;		// scale factor ==> 0-1
    void		setHilbertResolution( int res );

    int		currentHilbertPoint;	// index of current Hilbert point
    int		currentFace;		// index into color transforms

    void	transformPointToColor( HilbertPoint &point, float rgb[3] );
};
