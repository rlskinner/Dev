/****************************************************************************
**
** Copyright (C) 2005-2008 Trolltech ASA. All rights reserved.
**
** This file is part of the example classes of the Qt Toolkit.
**
** Licensees holding a valid Qt License Agreement may use this file in
** accordance with the rights, responsibilities and obligations
** contained therein.  Please consult your licensing agreement or
** contact sales@trolltech.com if any conditions of this licensing
** agreement are not clear to you.
**
** Further information about Qt licensing is available at:
** http://www.trolltech.com/products/qt/licensing.html or by
** contacting info@trolltech.com.
**
** This file is provided AS IS with NO WARRANTY OF ANY KIND, INCLUDING THE
** WARRANTY OF DESIGN, MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE.
**
****************************************************************************/

#ifndef _PbnMdi_h_
#define _PbnMdi_h_

#include <QGLWidget>

#include "Colormap.h"

class QToolBar;

class PbnMdi : public QGLWidget
	{
	Q_OBJECT;

	public:
		// 2D/3D factory method
		static PbnMdi* createPbnWidget(QString filename);

		virtual QSize imageSize() = 0; // size in pixels if 2D

	public slots:
		virtual bool open(QString filename); // may not need slot with factory method
		virtual void play();
		virtual void setColormap(Colormap const& colormap);

		virtual void slotSetSize();
		virtual void slotResequenceAndPlay();
		virtual void slotPlaySequence();

		QToolBar* getToolBar();

	protected:
		PbnMdi();

		Colormap	m_colormap; // per-cell colormap, need more for 3D?
		QToolBar	*m_toolbar; // created by this class customized by subclasses

		virtual void buildToolBar(QToolBar* toolbar);

	private:

	}; // class PbnMdi

#endif // _PbnMdi_h_
