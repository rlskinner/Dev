#ifndef	_SLICESEQ_H_
#define	_SLICESEQ_H_
//
//  slice list:  manage and draw a list of slices
//
#include	<sys/types.h>

class	sliceSeq {
protected:
    int		allocDepth;			// deepest its ever gotten
    u_long	**maps;
    float	**mapCoords;
    float	*mapOmega;

    // need a holding pen for slice shifted off the end, since
    // we will insert a new one shortly 

public:
    sliceSeq();
    sliceSeq( sliceSeq& );

    int		resolution;
    int		maxBucket;

    float	major, minor;
    float	sliceInc;
    float	fade;

    int		saveDepth, displayDepth;

    void	setResolution( int res );		// its square
    void	setMaxBucketCount( int n );

    void	setMajorRadius( float major );
    void	setMinorRadius( float minor );
    void	setSliceIncrement( float inc );
    void	setFade( float a );			// per slice

    void	setDisplayDepth( int n );
    void	setSaveDepth( int n );

    void	shift();				// shift all slices down
    void	insertSlice( float o1, float o2 );	// insert new slice

    virtual	void	draw() = 0;
};
#endif	/* _SLICESEQ_H_ */
