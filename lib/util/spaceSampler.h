//
//  sample some N dimensional space randomly by firing 
//	vectors into it at random
//


class	spaceSampler {
public:
    spaceSampler( float step, int ndim );		// ndim x [0-1]
    spaceSampler( float step, int ndim, float lowBound[], float upBound[] );
    ~spaceSampler();
    
    void	setBounds( float lowBound[], float upBound[] );
    void	setStepSize( float size );

    void	getSample( float sample[] );

    void	stepSample();
    void	operator++() { stepSample(); }

protected:
    int		ndim;
    float	*lowerBound, *upperBound;
    float	sampleSize;
    float	*currentSample;
    float	*startPoint;		// ray starting point
    float	*targetPoint;		// point ray hits on some cube face
    int		numRaySamples;		// number of samples in this ray
    int		numSamplesLeft;		// number of samples left to do

    void	init( float step, int ndim );
    void	startNewSequence();
    void	randomPointInInterval( float lower[], float upper[], float result[] );
    void	clipRayToBox( float from[], float to[] );
    float	getRayLength( float from[], float to[] );

};
