#ifndef	_action_
#define	_action_

#include	<stdio.h>
#include	<string>
#include	<sys/types.h>

#include	"CellArray.h"
#include	"Dimensions.h"
#include	"weight.h"

#ifndef	TRUE
#define	TRUE	1
#define	FALSE	0
#endif


//
//  define classifications we can do on sets of weights
//
enum	ActionWeightSelect 
	{
	    awAll,			// take them all
	    awMax,			// take only Max
	    awMin,			// or Min
	    awPositive,			// only positive values
	    awNegative,			// only negative values
	};

class	Action 
	{
	protected:
		Dimensions	m_dims;
		Weight  	*m_wgt;

		//
		//  actions keep a list of relative positions to affect 
		//	and their relative weights
		//
		IndexArray			m_nbors;		// list of relative cell indexes affected 
		std::vector<float>	m_relNborWgts;		// relative wgts of affected cells
		std::vector<double>	m_newNborWgts;		// temp buffer for resultant weights
		std::vector<bool>	m_nborEnable;		// enable flags, depending on classify
		CellStateVector		m_nborStates;	// cell states for selection
		std::vector<int>	m_nborValues;		// cell values for selection

		void	setNumNbors(int n);
		virtual	void	makeNbors() = 0;
		void	setConstWgts()	{ m_relNborWgts.clear(); /* XXX BAD BAD BAD -- should use a flag */ }

		//
		//  select weights depending on numerical properties
		//
		ActionWeightSelect	m_selectWgts;
		void	selectWgtValues();

		//
		//  select Positions depending on cell states
		//
		int		m_selectStates;		// bit OR of states
		void	selectCellStates(CellArray *cells, Index const& index);

		// CellState	addState;	// if == csEmpty, cell must be empty
		// to add in doAction;

		//
		//  function we want performed on cell's weight
		//	does the MULTIPLY function imply selectStates == csWaiting?
		//
		CellFunction	m_function;

		// Searching Operations
		virtual bool findLastNborPicked(Index& index);

	public:
		Action	*m_next;
		Action(Weight *weight);
		virtual ~Action();

		virtual std::string name() = 0;

		size_t numNbors() { return m_nbors.size(); }
		int numDimensions() { return m_dims.numDimensions(); }

		virtual	void	init(/* Dimensions const& dims */);
		virtual void	doAction(CellArray *cells, Index const& index);

		virtual	void	setWeightSelection(ActionWeightSelect aws)
			{ m_selectWgts = aws; }

		virtual	void	setStateSelection(int sss)
			{ m_selectStates = sss; }

		virtual	void	setWeightFunction(CellFunction f)
			{ m_function = f; }
	};
	
#endif	/* _action_ */

