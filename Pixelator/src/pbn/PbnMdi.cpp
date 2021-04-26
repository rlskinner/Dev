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

#include <QtGui>

#include "PbnMdi.h"
#include "Pbn2DWidget.h"

PbnMdi::PbnMdi()
	: QGLWidget(QGLFormat(QGL::SingleBuffer | QGL::NoDepthBuffer))
	{
	setAttribute(Qt::WA_DeleteOnClose);
	}


// 2D/3D factory method
PbnMdi*
PbnMdi::createPbnWidget(QString filename)
	{
	// read the PBN specification
	// determine 2D/3D type
	// create PbnMdi 
	return new Pbn2DWidget(0);
	}


bool
PbnMdi::open(QString filename)
	{
	return true;
	}


void
PbnMdi::play()
	{
	}


void
PbnMdi::setColormap(Colormap const& colormap)
	{
	m_colormap = colormap;
	}


void PbnMdi::slotSetSize()
	{
	}


void PbnMdi::slotResequenceAndPlay()
	{
	}


void PbnMdi::slotPlaySequence()
	{
	}


//
// Return this window's toolbar, create and build it if necessary
//
QToolBar* PbnMdi::getToolBar()
	{
	return NULL;
	}


// 
// Add actions for this class to the toolbar and 
//
void PbnMdi::buildToolBar(QToolBar* toolbar)
	{
	}
