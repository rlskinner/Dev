#include "Pbn2DWidget.h"
#include "MainWindow.h"

#include "lineSeed.h"
#include "nborAction.h"

#include <QPainter>
#include <QTime>
#include <QTextStream>
#include <QStatusBar>

// XXX
//
// Multithreading notes:
// 	* Put all multithreading in a class (Foo, for now) that just drives the
// 	picking process.
// 	* *Foo* maintains the pick sequence so that it can protect accesses to the
// 	array without impacting other classes.
// 	* Foo could send a signal when it has more values, but normally it will
// 	have new values quite often.  Don't want to send millions of signals, one
// 	for each pick.
// 	* Can we do partial paints in Qt/OGL?
// 	* The painter could just wait on picks
// 	* Assuming the painter can render incrementally, then a paint event (or
// 	resize event, whatever triggers recomputation) simply starts the thread,
// 	then calls the incremental painting method.  The incremental paint method
// 	draws the picks now available (and keeps looping if new ones became
// 	available).  If the pick list stalls, it sends itself a oneshot signal to
// 	continue.  If another paint event comes along, it can restart the painting
// 	process.  If another resize event happens, it can trigger a recompute.
// 	XXX put it all in paintGL to start.

Pbn2DWidget::Pbn2DWidget(PixelEnumerator *pixelEnumerator)
	: PbnMdi()
	, m_backgroundColor()
	, m_imageSize(500, 500)
	, m_cellArray(0)
	, m_enumerator(0)
	, m_sequenceValid(false)
	, m_playRepaint(true)
	{
	m_backgroundColor.setRgbF(0.4, 0.4, 0.4);

	resize(m_imageSize);

	setColormap(Colormap(Colormap::Rainbow));

	m_enumerator = pixelEnumerator;

	slotResequenceAndPlay();
	}


Pbn2DWidget::~Pbn2DWidget()
	{
	delete m_cellArray;
	delete m_enumerator;
	}


void Pbn2DWidget::slotSetSize()
	{
	}


void Pbn2DWidget::slotResequenceAndPlay()
	{
	// set flags to resequence and play on next update
	m_sequenceValid = false;
	m_playRepaint = true;
	update();
	}


void Pbn2DWidget::slotPlaySequence()
	{
	// set flag to play on next update
	m_playRepaint = true;
	update();
	}


void Pbn2DWidget::initializeGL()
	{
	qglClearColor(m_backgroundColor);
	}


// paintGL will be used to refresh the current "image", NOT to replay the
// pixel sequence.  It makes sense then to implement it with textures, and
// we update the texture with the recent changes to the sequence.
void Pbn2DWidget::paintGL()
	{
	// Setup to paint
	glViewport(0, 0, width(), height());

	// standard world-to-screen pixel coordinate system transform
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluOrtho2D(0, m_imageSize.width(), 0, m_imageSize.height());

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	glTranslatef(0.375, 0.375, 0.0);

	// Clear
	glClear(GL_COLOR_BUFFER_BIT);

	if(m_playRepaint)
		{
		m_playRepaint = false;

		glBegin(GL_POINTS);

#if	0 // plain redraw should use a QImage or QPixmap
		int dims[2] = { m_imageSize.width(), m_imageSize.height() };
		for(int i=0; i<dims[0]; ++i)
			{
			for(int j=0; j<dims[1]; ++j)
				{
				CellState state;
				int value;
				Index index(2);
				index.set(i, j);
				m_cellArray->getState(index, state, value);

				// compute "color"
				float t = value/float(dims[0]*dims[1]);
				QColor color = m_colormap.lookup(t);
				qglColor(color);
				glVertex2i(i, j);
				}
			}
#endif

		if(m_sequenceValid)
			{
			// don't recompute
			IndexArray const& picks = m_cellArray->getPickSequence();
			int N = picks.size();
			Index index(2);
			for(int i=0; i<N; ++i)
				{
				float t = i/float(N);
				QColor color = m_colormap.lookup(t);
				qglColor(color);

				picks.get(i, index);
				glVertex2i(index[X], index[Y]);
				}
			}
		else // recompute
			{
			QTime execTime;
			execTime.start();

			// Save the image
			// XXX doesn't work with zoom
			QImage image(width(), height(), QImage::Format_ARGB32);

			Dimensions dims(m_imageSize.width(), m_imageSize.height());
			m_cellArray = new CellArray(dims, CellArray::cSavePickSequence);
			m_enumerator->init(m_cellArray);
			Index index(2);
			int N = m_cellArray->getDims().totalSize();
			for(int i=0; i<N; ++i)
				{
				m_enumerator->pick(index);

				float t = i/float(N);
				QColor color = m_colormap.lookup(t);
				qglColor(color);

				glVertex2i(index[X], index[Y]);

				// Qt's coordinate system flipped
				image.setPixel(index[X], height()-index[Y]-1, color.rgba());
				}

			QString timeStr;
			QTextStream(&timeStr) << "Generation Time: " << execTime.elapsed() << " msec";

			m_pixmap = QPixmap::fromImage(image);

			MainWindow::instance()->statusBar()->showMessage(timeStr);
			m_sequenceValid = true;
			}
		glEnd();
		}

	}


void Pbn2DWidget::resizeGL(int width, int height)
	{
	}


void Pbn2DWidget::paintEvent(QPaintEvent *e)
	{
	if(m_playRepaint)
		{
		QGLWidget::paintEvent(e);
		}
	else // don't need to replay painting, just draw the pixmap
		{
		QPainter painter(this);
		painter.drawPixmap(0, 0, m_pixmap);
		}
	}


void Pbn2DWidget::buildToolBar(QToolBar* toolbar)
	{
	}
