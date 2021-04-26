#ifndef	_CellArray_
#define	_CellArray_

//
//   Enumerate the pixels in an image away based on different rules, and
//   different seed points
//

#include	"Dimensions.h"
#include	"Index.h"

#include	<stdio.h>
#include	<sys/types.h>

#include	<UnixCompat.h>

class	PixelEnumerator;

//
//  states that cells can be in
//
enum	CellState
	{ 
	csEmpty = 0x01, 		// not touched
	csWaiting = 0x02,		// in rand array
	csFilled = 0x04,		// filled
	csOutside = 0x08,		// outside cell array
	};

typedef std::vector<CellState>	CellStateVector;
typedef CellStateVector::iterator CellStateVectorIter;

//
//  functions that can be performed on a cell's weight
//
enum	CellFunction
	{
	cfSet,			// set value
	cfAdd,			// add values
	cfMultiply,			// multiply weights
	};

//
//  allocate all arrays to size+1, and use 1-based indexing
//
class	RandArray 
	{
	private:
		size_t	m_dataSize;
		int		m_maxSize;
		int		m_size;
		u_char*	m_data;
		double*	m_wts;
		double*	m_cumWts;
		int		m_indUsed;
		int		m_indSize;
		int*	m_inds;
		int		m_autoUpdate;

		//
		//  debug flags
		//
		int		m_printSets;

		void	clearWt( int index );		// remove from array


		double	getTotalWt()	{ return m_cumWts[1]; }

		void	assertHeap();

		void	incUpdate( int index );		// this array element changed

	public:
		RandArray( size_t m_dataSize );
		~RandArray();

		int		numWaiting()	{ return m_size-m_indUsed; }

		int		addData( void *data, double weight );	// returns index
		double	getWt( int index )	{ return m_wts[index]; }
		void	setWt( int index, double wt );

		void	pick( void *m_pickedData );

		void	setAutoUpdate( int on )	{ m_autoUpdate = on; }
		void	update();
	}; // struct RandArray



class	CellArray 
	{
	public:
		enum SavePickSequence
			{
			cSavePickSequence, // maintain history of picked indexes
			cNoSavePickSequence
			};

		CellArray(Dimensions const& dims, SavePickSequence savePicks = cNoSavePickSequence);
		virtual ~CellArray();

		// Access Operations
		int numDimensions() { return m_dims.numDimensions(); }
		Dimensions const&		getDims() const { return m_dims; }

		int		numWaiting();
		IndexArray const & getPickSequence() const { return m_pickSequence; }

		// Picking operations
		void		pick(Index& index);

		void		getStates(Index const& cellIndex,
							  IndexArray const& relIndexes,
							  CellStateVector& states,
							  std::vector<int>& values);

		void		opPos(CellFunction func,
						  Index const& index,
						  IndexArray const& relNbors,
						  std::vector<double>& wgts,
						  std::vector<bool>& enabled);

		void		opPos(CellFunction func,
						  Index const& index,
						  IndexArray const& relNbors,
						  std::vector<double>& wgts)
			{
			opPos(func, index, relNbors, wgts, std::vector<bool>(0));
			}

		// Debugging Operations
		virtual void	print();

	protected:
		Dimensions	m_dims;
		int*	m_indexOffsets;
		char*	m_states;
		union CellDataUnion 
			{
			int		waitIndex;	// index in waitList array when waiting
			float	weight;		// inhibited weight 
			int		fillOrder;	// filled order
			} *m_cellData;

		int			m_setCntr;
		int			m_totalCount;
		RandArray	*m_waitList;
		SavePickSequence	m_savePickSequence;
		IndexArray	m_pickSequence; // sequence of Index's picked

		//
		//  debug flags
		//
		int	m_printPicks;

		virtual void	init();

		int		getTotalCount()	{ return m_totalCount; }

		int		offset(Index const& index);
		Index offsetToIndex(int offset);

		void		getState(Index const& index, CellState &s, int &d);


		void		seed(Index const& index, double weight);
		// void		add(Index const& index, double weight);
		virtual	void	set(Index const& index);

		void	setAutoUpdate( int on )	{ m_waitList->setAutoUpdate( on ); }
		void	update()		{ m_waitList->update(); }

	}; // class CellArray


#if	0
// Functions formerly in PixelEnumerator, but that should really apply to
// CellArray (I think)

// Fit images to the CellArray size
//
#include	<il/ilImage.h>
struct	fitZoom {
    ilImage	*img;
    fitZoom	*next;

    fitZoom( ilImage *_img )    { img = _img;  next = NULL; }
    ~fitZoom() { next = NULL; }
};
    fitZoom	*fitImages;

// methods
    		void	addZoomToFit( ilImage *img );

// write result to an (image?) file
    int	writeFile;
    char	*writeFilename;
		void	setWriteImage( char *file, char *type );
		void	writeImage();

// Associate a colormap 
    int		loadCmap;
    char	*cmapFilename;
		void	loadColormap( char *file );
#endif

#endif	/* _CellArray_ */

