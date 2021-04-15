#include	<interval.h>

inline
double	MIN( double a, double b )
{
	return a < b ? a : b;
}

inline
double	MAX( double a, double b )
{
	return a > b ? a : b;
}

Interval::Interval( double _min, double _max )
{
    min = MIN( _min, _max );
    max = MAX( _min, _max );
}


void
Interval::setMin( double v )
{
    min = v;
    if( min > max ) {
	double	t = min;
	min = max;
	max = t;
    }
}


void
Interval::setMax( double v )
{
    max = v;
    if( min > max ) {
	double	t = min;
	min = max;
	max = t;
    }
}


void
Interval::include( double v )
{
    if( v < min ) {
	min = v;
    }
    if( v > max ) { 
	max = v;
    }
}

//
//  operations with scalars
//
Interval&
Interval::operator+=( double v )
{
    min += v;
    max += v;
    return *this;
}


Interval&
Interval::operator-=( double v )
{
    min -= v;
    max -= v;
    return *this;
}


Interval&
Interval::operator*=( double v )
{
    double	mv = min*v;
    double	Mv = max*v;
    min = MIN( mv, Mv );
    max = MAX( mv, Mv );
    return *this;
}


Interval&
Interval::operator/=( double v )
{
    min /= v;
    max /= v;
    return *this;
}



//
//  operations with other Intervals
//
Interval&
Interval::operator+=( const Interval &other )
{
    min = min + other.min;
    max = max + other.max;
    return *this;
}


Interval&
Interval::operator-=( const Interval &other )
{
    min = min - other.max;
    max = max - other.min;
    return *this;
}


Interval&
Interval::operator*=( const Interval &other )
{
    double	mm = min*other.min;		// brute force
    double	mM = min*other.max;		// compare all cross-products
    double	Mm = max*other.min;
    double	MM = max*other.max;

    min = MIN( mm, MIN( mM, MIN( Mm, MM ) ) );
    max = MAX( mm, MAX( mM, MAX( Mm, MM ) ) );
    return *this;
}


//
//  XXX should really check that 0.0 not in other
//
Interval&
Interval::operator/=( const Interval &other )
{
    Interval	div( 1.0/other.max, 1.0/other.min );
    *this *= div;
    return *this;
}


