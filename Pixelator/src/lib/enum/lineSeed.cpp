//
//   Enumerate the pixels in an image away based on different rules, and
//   different seed points
//

#include	<math.h>

#include	"CellArray.h"
#include	"lineSeed.h"

using namespace std;

LineSeed::LineSeed( double _x0, double _y0, double _x1, double _y1, Weight *wgt )
	: Seed( wgt )
	{
	m_x0 = ( _x0 > 1.0 ) ? 1.0 : (( _x0 < 0.0 ) ? 0.0 : _x0);
	m_y0 = ( _y0 > 1.0 ) ? 1.0 : (( _y0 < 0.0 ) ? 0.0 : _y0);
	m_x1 = ( _x1 > 1.0 ) ? 1.0 : (( _x1 < 0.0 ) ? 0.0 : _x1);
	m_y1 = ( _y1 > 1.0 ) ? 1.0 : (( _y1 < 0.0 ) ? 0.0 : _y1);
	}


string LineSeed::name()
	{
	return string("LineSeed");
	}


// 
// Seed the CellArray along a line
//
void LineSeed::seedArray(CellArray *cells, // CellArray to seed
						 Dimensions const& dims
						)
	{
	//
	//  find number of points, and allocate a buffer for them
	//
	double	dx = m_x1 - m_x0;
	double	dy = m_y1 - m_y0;

	IndexArray indexes(dims);

	// don't need any of this with push_back
#if	0
	int	np;
	if( dx == 0.0 && dy == 0.0 ) 
		{
		np = 1;
		} else {
			if( fabs(dx) > fabs(dy) ) 
				{
				xMajor = 1;
				delta = (m_y1-m_y0)/(m_x1-m_x0);
				int	ix0 = roundToInt(m_x0*dims[0]);
				int	ix1 = roundToInt(m_x1*dims[0]);
				i = ( ix0 < ix1 ) ? ix0 : ix1;
				limit = ( ix0 > ix1 ) ? ix0 : ix1;
				} else {
					xMajor = 0;
					delta = (m_x1-m_x0)/(m_y1-m_y0);
					int	iy0 = roundToInt(m_y0*dims[1]);
					int	iy1 = roundToInt(m_y1*dims[1]);
					i = ( iy0 < iy1 ) ? iy0 : iy1;
					limit = ( iy0 > iy1 ) ? iy0 : iy1;
				}
			np = limit-i+1;
		}
#endif

	Index index(dims.numDimensions());

	if( dx == 0.0 && dy == 0.0 ) 
		{
		index[X] = roundToInt(m_x0*dims.size(X));
		index[Y] = roundToInt(m_y0*dims.size(Y));
		indexes.push_back(index);
		}
	else
		{
		int x0 = roundToInt(m_x0*dims.size(X));
		int y0 = roundToInt(m_y0*dims.size(Y));
		int x1 = roundToInt(m_x1*dims.size(X));
		int y1 = roundToInt(m_y1*dims.size(Y));

		if( fabs(dx) > fabs(dy) ) 
			{
			double delta = (m_y1-m_y0)/(m_x1-m_x0);
			for(int i=x0; i<=x1; ++i)
				{
				index[X] = i;
				index[Y] = roundToInt(y0 + (i - x0)*delta );
				indexes.push_back(index);
				}
			}
		else
			{
			double delta = (m_x1-m_x0)/(m_y1-m_y0);
			for(int i=y0; i<=y1; ++i)
				{
				index[X] = roundToInt(x0 + (i - y0)*delta );
				index[Y] = i;
				indexes.push_back(index);
				}
			}
		}


	// Get weights along this line
	Index origin(dims);
	origin.set(0); // XXX should zero be the default value?
	std::vector<double>	wgts(indexes.size());
	m_wgt->getWgts(origin, indexes, wgts);

	// Seed the cells
	cells->opPos(cfAdd, origin, indexes, wgts );
	}



