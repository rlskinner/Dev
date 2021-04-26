#include	"action.h"

using namespace std;

Action::Action( Weight *_wgt )
	: m_next(NULL)	// XXX are these in order?
	, m_wgt(_wgt)
	, m_dims(_wgt->dims())
	, m_nbors(_wgt->dims())
	, m_relNborWgts()
	, m_newNborWgts()
	, m_nborEnable()
	, m_nborStates()
	, m_nborValues()
	, m_selectWgts(awAll)
	, m_selectStates(int(csEmpty|csWaiting))
	, m_function(cfAdd)
	{ 
	// addState = csEmpty;
	}


Action::~Action()
	{
	}


string Action::name()
	{
	return string("Action");
	}


//
// Initialize the Action and its Weight for the dimensions of the cell array
//
void	Action::init(// Dimensions const& dims // dimensions
					)
	{
// 	m_dims = dims;

// 	m_wgt->init(m_dims);
	makeNbors();
	}


//
// Set the number of neighbors for this action and initialize internal data
// accordingly.
//
void Action::setNumNbors(int nb // number of neighbors for this Action
						 )
	{
	m_nbors.resize(nb);
	m_relNborWgts.resize(nb);
	m_newNborWgts.resize(nb);
	m_nborEnable.resize(nb);
	m_nborStates.resize(nb);
	m_nborValues.resize(nb);
	}


//
//  select weights depending on numerical properties
//
void   Action::selectWgtValues()
	{
	size_t	i;

#define	SELECT(EXPR)				\
	for( i=0; i<numNbors(); i++ )	\
		{							\
		m_nborEnable[i] = EXPR;		\
		}

	double	min, max;
	int		minI, maxI;
	switch( m_selectWgts ) 
		{
		case awAll:
			break;

		case awMin:
			m_nborEnable[0] = FALSE;
			minI = 0;
			min = m_newNborWgts[0];
			for( i=1; i<numNbors(); i++ ) 
				{
				m_nborEnable[i] = FALSE;
				if( m_newNborWgts[i] < min )
					{
					min = m_newNborWgts[i];
					minI = i;
					}
				}
			m_nborEnable[minI] = TRUE;
			break;

		case awMax:
			m_nborEnable[0] = FALSE;
			maxI = 0;
			max = m_newNborWgts[0];
			for( i=1; i<numNbors(); i++ )
				{
				m_nborEnable[i] = FALSE;
				if( m_newNborWgts[i] > max )
					{
					max = m_newNborWgts[i];
					maxI = i;
					}
				}
			m_nborEnable[maxI] = TRUE;
			break;

		case awPositive:
			SELECT(m_newNborWgts[i] >= 0.0);
			break;

		case awNegative:
			SELECT(m_newNborWgts[i] <= 0.0);
			break;
		}

#undef	SELECT
	}


//
//  Set the neighbor enabled flags for those cells that are in one of our
//  selected states
//
void Action::selectCellStates(CellArray *cells, // the cell array
							  Index const& index // index of the cell to query
							  )
	{
	cells->getStates(index, m_nbors, m_nborStates, m_nborValues);

	// OPT: user iterators for m_nborEnable
	for(size_t i=0; i<numNbors(); i++ )
		{
		if( m_nborEnable[i] )
			m_nborEnable[i] = (m_nborStates[i] & m_selectStates) != 0;
		}
	}


// 
// Find the last neighbor cell picked and return it's index.  
// Return false if no neighbor picked.
//
bool Action::findLastNborPicked(Index& index // out: index set to last nbor picked
								)
	{
    // 
    //  now find the last neighbor to be filled
    //
    int	maxVal = -1;
    for(size_t i=0; i<m_nbors.size(); i++) 
		{
		if( m_nborStates[i] == csFilled && m_nborValues[i] > maxVal ) 
			{
#if	0
			if( maxVal == -1 ) 
				{
				printf( "DirAction::doAction( index = [" );
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
			maxVal = m_nborValues[i];
			m_nbors.get(i, index);
			}
		}

	return maxVal != -1;
	}

//
//  Apply the default action to the cell array: 
//  	foreach neighbor, apply its relative weight and add it to the cells
//
void Action::doAction(CellArray *cells, // the cell array
					  Index const& index // cell index action centered on the cell picked
					 )
	{
	size_t	i;

	for( i=0; i<numNbors(); i++ )
		m_nborEnable[i] = TRUE;

	m_wgt->getWgts(index, m_nbors, m_newNborWgts);

	// modify by relative neighbor weights, if there are any
	if(m_relNborWgts.size() > 0)
		{
		for( i=0; i<numNbors(); i++ )
			m_newNborWgts[i] *= m_relNborWgts[i];
		}

	selectWgtValues();
	selectCellStates( cells, index );
	cells->opPos(m_function, index, m_nbors, m_newNborWgts, m_nborEnable);
	}




