#ifndef	_dirAction_
#define	_dirAction_

#include	"action.h"

class	DirAction : public Action 
	{
	protected:
		Weight	*m_primary;

		virtual	void	makeNbors();

	public:
		DirAction( Weight *_primary, Weight *_wgt )
			: Action( _wgt )
			{ m_primary = _primary; }

		virtual std::string name();

		virtual	void	init(/* Dimensions const& dims */);
		virtual void	doAction( CellArray *cells, Index const& index);
	};
	
#endif	/* _dirAction_ */

