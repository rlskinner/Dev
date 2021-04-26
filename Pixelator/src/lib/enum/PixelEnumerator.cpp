//
//   PixelEnumerator an image away based on different rules, and different seed points
//

#include	<stdio.h>
#include	<stdlib.h>
// #include	<unistd.h>
// #include        <libc.h>
#include        <string.h>

// #include	<il/ilFileImg.h>
// #include	<il/ilRotZoomImg.h>

#include	"PixelEnumerator.h"

PixelEnumerator::PixelEnumerator()
    : m_dims()
    {
    m_cells = NULL;
    m_seeds = NULL;
    m_actions = NULL;
    }


PixelEnumerator::~PixelEnumerator()
    {
    }


void	PixelEnumerator::init(CellArray *cellArray)
    {
    setCellArray(cellArray);

    // 
    //  first, reverse the order of the seeds and actions,
    //	so that they will be executed in the order given in
    //	the script.
    //
    Seed	*newSeeds = NULL;
    while( m_seeds != NULL )
	{
	Seed	*s = m_seeds;		// remove from original list
	m_seeds = m_seeds->m_next;
	s->m_next = newSeeds;		// place on new list
	newSeeds = s;
	}
    m_seeds = newSeeds;			// replace reordered list

    Action	*newActions = NULL;
    while( m_actions != NULL )
	{
	Action	*a = m_actions;		// remove from original list
	m_actions = m_actions->m_next;
	a->m_next = newActions;		// place on new list
	newActions = a;
	}
    m_actions = newActions;		// replace reordered list


    //  
    //  init m_cells, seeds, and actions 
    //
    Seed	*s = m_seeds;
    while( s != NULL )
	{
	s->init(cellArray->getDims());
	s->seedArray( m_cells, cellArray->getDims());
	s = s->m_next;
	}
    Action	*a = m_actions;
    while( a != NULL )
	{
	a->init(/* cellArray->getDims() */);
	a = a->m_next;
	}


    }


//
//  do at most 'count' selections and return
//
void	PixelEnumerator::doActions(Index& index)
    {
    Action	*a = m_actions;
    while( a != NULL ) 
	{
	a->doAction( m_cells, index );
	a = a->m_next;
	}
    }


void PixelEnumerator::setCellArray(CellArray *cellArray
				  )
    {
    m_cells = cellArray;
    setDims(m_cells->getDims());
    }


//
// Pick one index
// XXX make it any number of indexes later
//
void PixelEnumerator::pick(Index& index)
    {
    int count = 1;
    while( m_cells->numWaiting() > 0 && count > 0 ) 
	{
	m_cells->pick(index);
	doActions(index);
	count--;
	}
    }


void PixelEnumerator::setDims(Dimensions const& dims)
    {
    m_dims = dims;
    }




// vim:ts=8:
