#ifndef _Pbn2DWidget_h_
#define _Pbn2DWidget_h_

#include "PbnMdi.h"

#include "PixelEnumerator.h"

class Pbn2DWidget : public PbnMdi
	{
    Q_OBJECT;

	public:
		Pbn2DWidget(PixelEnumerator *pixelEnumerator);
		virtual ~Pbn2DWidget();

		virtual QSize imageSize() { return m_imageSize; }

	public slots:
		virtual void slotSetSize();
		virtual void slotResequenceAndPlay();
		virtual void slotPlaySequence();

	protected:
		virtual void initializeGL();
		virtual void paintGL();
		virtual void resizeGL(int width, int height);
		virtual void paintEvent(QPaintEvent *e);

		virtual void buildToolBar(QToolBar* toolbar);

	private:
		QSize		m_imageSize; // paint-by-numbers image size
		QColor		m_backgroundColor;
		QPixmap		m_pixmap; // pre-rendered image

		CellArray		*m_cellArray;
		PixelEnumerator	*m_enumerator;

		// drawing controls
		bool		m_sequenceValid; // has sequence been computed?
		bool		m_playRepaint; // repaint by "playing" the sequence?


	}; // class Pbn2DWidget

#endif 	// _Pbn2DWidget_h_
