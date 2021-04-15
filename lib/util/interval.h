#ifndef	__interval__
#define	__interval__
//
//   Interval:  do interval arithmetic
//	XXX this should be a template, for now just do doubles
//

class	Interval {
public:
    inline	Interval();
    		Interval( double min, double max );
    inline	Interval( const Interval& other );

    double	getMin() { return min; }
    void	setMin( double v );

    double	getMax() { return max; }
    void	setMax( double v );

    void	include( double v );

    //
    //  operations with scalars
    //
    Interval& operator+=( double v );
    Interval& operator-=( double v );
    Interval& operator*=( double v );
    Interval& operator/=( double v );

    //
    //  operations with other Intervals
    //
    Interval& operator+=( const Interval &other );
    Interval& operator-=( const Interval &other );
    Interval& operator*=( const Interval &other );
    Interval& operator/=( const Interval &other );

    inline Interval& operator=( const Interval &other );
protected:
    double	min;
    double	max;
};


inline
Interval::Interval()
{
    min = 0.0;				// XXX ???
    max = 0.0;
}

inline
Interval::Interval( const Interval &other )
{
    min = other.min;
    max = other.max;
}


inline
Interval&
Interval::operator=( const Interval &other )
{
    min = other.min;
    max = other.max;
    return *this;
}

#endif	// __interval__
