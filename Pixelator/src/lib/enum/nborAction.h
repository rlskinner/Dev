#ifndef	_nborAction_
#define	_nborAction_

#include	"action.h"

class	NborAction : public Action 
	{
	protected:
		int	m_connectedness;

		virtual	void	makeNbors();

	public:
		NborAction( Weight *wgt, int connect );

		virtual std::string name();

	};
	
#endif	/* _nborAction_ */

