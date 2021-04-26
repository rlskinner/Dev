//
//   Enumerate the pixels in an image away based on different rules, and
//   different seed points
//

#include	"contourAction.h"
#include	<math.h>

//
//  precompute indexes of a contour Action, using 8-fold symetry
//
void ContourAction::init(// Dimensions const& dims // dimensions
						)
	{
	Action::init(/* dims */);
	m_primary->init(/* dims */);

	if(numDimensions() == 3) 
		{
		printf( "3D contour not implemented\n" );
		return;
		}
	}


//
// Initialize neighbor data for the ContourAction class
//
	void
ContourAction::makeNbors()
	{
	Index index(numDimensions());

	m_nbors.clear();
	for( int x=-1; x<=1; x++ ) 
		{
		for( int y=-1; y<=1; y++ ) 
			{
			if( x == 0 && y == 0 ) 
				continue;

			index.set(x, y);
			m_nbors.push_back(index);
			}
		}

	setNumNbors(m_nbors.size());
	}

//
//  move index by relative values in inds, and add weight to each one
//
	void
ContourAction::doAction( CellArray *cells, Index const& index )
	{
	//
	//	Add the default weight to all empty neighbor cells:
	//  	the default action rule does the right thing, if the 
	//		selection state is empty
	//
	Action::doAction( cells, index );

	// 
	//  now find the last neighbor to be filled
	//
	int	maxVal = -1;
	int	iMaxIndex = -1;
	for(size_t i=0; i<m_nbors.size(); i++ ) 
		{
		if(m_nborStates[i] == csFilled && m_nborValues[i] > maxVal) 
			{
#if	0
			if( maxVal == -1 ) 
				{
				printf( "ContourAction::doAction( index = [" );
				for( int ii=0; ii<numDimensions(); ii++ ) 
					{
					printf( "%d", index[ii] );
					if( ii < numDimensions()-1 )
						putchar( ',' );
					}
				puts( "]" );
				}
			printf( "new max of %d at nbor = [", m_nborValues[i] );
			for( int ii=0; ii<numDimensions(); ii++ ) 
				{
				printf( "%d", m_nbors[i*numDimensions()+ii] );
				if( ii < numDimensions()-1 )
					putchar( ',' );
				}
			puts( "]" );
#endif
			iMaxIndex = i;
			maxVal = m_nborValues[i];
			}
		}

	//
	//  and add the m_primary weight to the last filled
	//
	if(iMaxIndex >= 0)
		{
		//
		// add bigWgt to pixel OPPOSITE last one picked
		//	regardless of state
		//
		Index rel(m_dims), negRel(m_dims);

		m_nbors.get(iMaxIndex, rel);
		negRel[X] = -rel[X];
		negRel[Y] = -rel[Y];

		IndexArray indexes(m_dims);
		indexes.push_back(negRel);

		std::vector<double>	primWgt;
		m_primary->getWgts(index, indexes, primWgt);
		cells->opPos(cfAdd, index, indexes, primWgt);
		}
	}




