//
//  generate and return a Hilbert sequence
//

struct	HilbertPoint {
    unsigned short	i, j;
};


class	HilbertSequence {
public:
		HilbertSequence( int resolution = 2 );
		~HilbertSequence();

    void	setResolution( int res );
    void	computeSequence();
    int		getSequence( HilbertPoint **seq );

protected:
    int			resolution;
    int			numberPoints;
    HilbertPoint	*points;
    int			allocedPoints;


    void	hilbert( int orient, int level );
    void	step();
    void	setPoint();
    int		currentPoint;
    int		currentI, currentJ;
    int		angle;

    void	reallocPoints();
};
