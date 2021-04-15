//
//  abstract class to generate different color sequences.
//	It returns colors that are no more than stepSize apart
//	(in RGB space).  
//


class	ColorSequence {
public:
		ColorSequence();
		ColorSequence( float stepSize );
    enum {
	red = 0,
	green = 1,
	blue = 2,
	alpha = 3,
    };

    virtual	void	setStepSize( float stepSize );

    //
    //  get color in different formats
    //
    virtual	void	getFloatColor( float rgb[3] );
    virtual	void	getABGRColor( unsigned long &abgr );	// for IRIS GL
    virtual	void	getRGBAColor( unsigned char rgba[4] );	// for OPEN GL

		void	operator++() { stepColor(); }
    virtual	void	stepColor() = 0;

protected:
    float	rgb[3];
    float	stepSize;
};
