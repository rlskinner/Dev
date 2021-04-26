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

#include "mainwindow.h"
#include "PbnMdi.h"
#include "Pbn2DWidget.h"

#include	"diskSeed.h"
#include	"edgeSeed.h"
#include	"lineSeed.h"

#include	"coneAction.h"
#include	"contourAction.h"
#include	"cornerAction.h"
#include	"crossAction.h"
#include	"dirAction.h"
#include	"nborAction.h"
#include	"ringAction.h"
#include	"SwirlAction.h"

MainWindow* MainWindow::s_instance = 0;

MainWindow::MainWindow()
	: QMainWindow()
{
	s_instance = this;

    mdiArea = new QMdiArea;
    mdiArea->setHorizontalScrollBarPolicy(Qt::ScrollBarAsNeeded);
    mdiArea->setVerticalScrollBarPolicy(Qt::ScrollBarAsNeeded);
    setCentralWidget(mdiArea);
    connect(mdiArea, SIGNAL(subWindowActivated(QMdiSubWindow *)),
            this, SLOT(updateMenus()));
    windowMapper = new QSignalMapper(this);
    connect(windowMapper, SIGNAL(mapped(QWidget *)),
            this, SLOT(setActiveSubWindow(QWidget *)));

    createActions();
    createMenus();
    createToolBars();
    createStatusBar();
    updateMenus();

    readSettings();

    setWindowTitle(tr("Paint By Numbers"));
}


// 
// MainWindow puts the active window's toolbar in a fixed location.
// The previously active window's toolbar is removed and replaced by
// the newly active window's toolbar.
//
// The user should be able to move it around, but I'll bet it gets
// moved when a different window is activated.
//
void MainWindow::setActiveWindowToolBar(QToolBar *windowToolBar)
	{
	}


void MainWindow::closeEvent(QCloseEvent *event)
{
    mdiArea->closeAllSubWindows();
    if (activePbnMdi()) {
        event->ignore();
    } else {
        writeSettings();
        event->accept();
    }
}

// void MainWindow::newFile()
// {
//     PbnMdi *child = createPbnMdi();
//     child->newFile();
//     child->show();
// }

void MainWindow::open()
	{
	QString fileName = "bogus"; // QFileDialog::getOpenFileName(this);
	if (!fileName.isEmpty()) 
		{
		PbnMdi *child = PbnMdi::createPbnWidget(fileName);
		QMdiSubWindow* mdiSubWindow = mdiArea->addSubWindow(child);

		if (child->open(fileName)) 
			{
			statusBar()->showMessage(tr("File loaded"), 2000);
			child->show();
			if(child->imageSize().isValid())
				{
				mdiSubWindow->resize(child->imageSize());
				}
			} 
		else 
			{
			child->close();
			}
		}
	}


// void MainWindow::save()
// {
//     if (activePbnMdi() && activePbnMdi()->save())
//         statusBar()->showMessage(tr("File saved"), 2000);
// }
// 
// void MainWindow::saveAs()
// {
//     if (activePbnMdi() && activePbnMdi()->saveAs())
//         statusBar()->showMessage(tr("File saved"), 2000);
// }
// 
// void MainWindow::cut()
// {
//     if (activePbnMdi())
//         activePbnMdi()->cut();
// }
// 
// void MainWindow::copy()
// {
//     if (activePbnMdi())
//         activePbnMdi()->copy();
// }
// 
// void MainWindow::paste()
// {
//     if (activePbnMdi())
//         activePbnMdi()->paste();
// }

void MainWindow::about()
{
   QMessageBox::about(this, tr("About MDI"),
            tr("The <b>MDI</b> example demonstrates how to write multiple "
               "document interface applications using Qt."));
}

void MainWindow::updateMenus()
{
    bool hasPbnMdi = (activePbnMdi() != 0);
    closeAct->setEnabled(hasPbnMdi);
    closeAllAct->setEnabled(hasPbnMdi);
    tileAct->setEnabled(hasPbnMdi);
    cascadeAct->setEnabled(hasPbnMdi);
    separatorAct->setVisible(hasPbnMdi);

#if	0
    bool hasSelection = (activePbnMdi() &&
                         activePbnMdi()->textCursor().hasSelection());
#endif
}

void MainWindow::updateWindowMenu()
{
    windowMenu->clear();
    windowMenu->addAction(closeAct);
    windowMenu->addAction(closeAllAct);
    windowMenu->addSeparator();
    windowMenu->addAction(tileAct);
    windowMenu->addAction(cascadeAct);
    windowMenu->addSeparator();
    windowMenu->addAction(separatorAct);

    QList<QMdiSubWindow *> windows = mdiArea->subWindowList();
    separatorAct->setVisible(!windows.isEmpty());

	// do anything here for each window?
	// windowMapper routes names in the Window menu to the setActiveSubWindow
	// slot with the window widget pointer.
#if	0
    for (int i = 0; i < windows.size(); ++i) {
        PbnMdi *child = qobject_cast<PbnMdi *>(windows.at(i)->widget());

        QString text;
        if (i < 9) {
            text = tr("&%1 %2").arg(i + 1)
                               .arg(child->userFriendlyCurrentFile());
        } else {
            text = tr("%1 %2").arg(i + 1)
                              .arg(child->userFriendlyCurrentFile());
        }
        QAction *action  = windowMenu->addAction(text);
        action->setCheckable(true);
        action ->setChecked(child == activePbnMdi());
        connect(action, SIGNAL(triggered()), windowMapper, SLOT(map()));
        windowMapper->setMapping(action, windows.at(i));
    }
#endif
}

#if	0
PbnMdi *MainWindow::createPbnMdi()
{
    PbnMdi *child = new Pbn2DWidget; // need a generator (by filename?) new PbnMdi;

    connect(child, SIGNAL(copyAvailable(bool)),

    return child;
}
#endif

void MainWindow::createActions()
{
	// Application Actions

    openAct = new QAction(QIcon(":/images/open.png"), tr("&Open..."), this);
    openAct->setShortcut(tr("Ctrl+O"));
    openAct->setStatusTip(tr("Open an existing file"));
    connect(openAct, SIGNAL(triggered()), this, SLOT(open()));

    exitAct = new QAction(tr("E&xit"), this);
    exitAct->setShortcut(tr("Ctrl+Q"));
    exitAct->setStatusTip(tr("Exit the application"));
    connect(exitAct, SIGNAL(triggered()), qApp, SLOT(closeAllWindows()));

    closeAct = new QAction(tr("Cl&ose"), this);
    closeAct->setShortcut(tr("Ctrl+F4"));
    closeAct->setStatusTip(tr("Close the active window"));
    connect(closeAct, SIGNAL(triggered()),
            mdiArea, SLOT(closeActiveSubWindow()));

    closeAllAct = new QAction(tr("Close &All"), this);
    closeAllAct->setStatusTip(tr("Close all the windows"));
    connect(closeAllAct, SIGNAL(triggered()),
            mdiArea, SLOT(closeAllSubWindows()));

    tileAct = new QAction(tr("&Tile"), this);
    tileAct->setStatusTip(tr("Tile the windows"));
    connect(tileAct, SIGNAL(triggered()), mdiArea, SLOT(tileSubWindows()));

    cascadeAct = new QAction(tr("&Cascade"), this);
    cascadeAct->setStatusTip(tr("Cascade the windows"));
    connect(cascadeAct, SIGNAL(triggered()), mdiArea, SLOT(cascadeSubWindows()));

    separatorAct = new QAction(this);
    separatorAct->setSeparator(true);

    aboutAct = new QAction(tr("&About"), this);
    aboutAct->setStatusTip(tr("Show the application's About box"));
    connect(aboutAct, SIGNAL(triggered()), this, SLOT(about()));

    aboutQtAct = new QAction(tr("About &Qt"), this);
    aboutQtAct->setStatusTip(tr("Show the Qt library's About box"));
    connect(aboutQtAct, SIGNAL(triggered()), qApp, SLOT(aboutQt()));

	//
	// Widget Control Actions
	//
	setSizeAct = new QAction(tr("Set Window Size"), this);
    setSizeAct->setStatusTip(tr("Show the Qt library's About box"));
    connect(setSizeAct, SIGNAL(triggered()), this, SLOT(slotActiveSubWindowSetSize()));

	recomputeAct = new QAction(tr("Resequence"), this);
    recomputeAct->setStatusTip(tr("Resequence"));
    connect(recomputeAct, SIGNAL(triggered()), this, SLOT(slotActiveSubWindowResequence()));

	drawAct = new QAction(tr("Play Sequence"), this);
    drawAct->setStatusTip(tr("Play Sequence"));
    connect(drawAct, SIGNAL(triggered()), this, SLOT(slotActiveSubWindowPlaySequence()));

	//
	// Test menu
	//
	testCenterPtNbor4Act = new QAction(tr("Center Seed (4-neighbor)"), this);
    connect(testCenterPtNbor4Act, SIGNAL(triggered()), this, SLOT(slotTestCenterPtNbor4Act(void)));

	testLineNbor4Act = new QAction(tr("Line Seed (4-neighbor)"), this);
    connect(testLineNbor4Act, SIGNAL(triggered()), this, SLOT(slotTestLineNbor4Act()));

	testEdgeNbor4Act = new QAction(tr("Edge Seed (4-neighbor)"), this);
    connect(testEdgeNbor4Act, SIGNAL(triggered()), this, SLOT(slotTestEdgeNbor4Act()));

	testDiskNbor4Act = new QAction(tr("Disk Seed (4-neighbor)"), this);
    connect(testDiskNbor4Act, SIGNAL(triggered()), this, SLOT(slotTestDiskNbor4Act()));

	testNbor8CenterPtAct = new QAction(tr("8-neighbor Action (1 pt seed)"), this);
    connect(testNbor8CenterPtAct, SIGNAL(triggered()), this, SLOT(slotTestNbor8CenterPtAct()));

	testConeCenterPtAct = new QAction(tr("Cone Action (1 pt seed)"), this);
    connect(testConeCenterPtAct, SIGNAL(triggered()), this, SLOT(slotTestConeCenterPtAct()));

	testCornerCenterPtAct = new QAction(tr("Corner Action (1 pt seed)"), this);
    connect(testCornerCenterPtAct, SIGNAL(triggered()), this, SLOT(slotTestCornerCenterPtAct()));

	testCrossCenterPtAct = new QAction(tr("Cross Action (1 pt seed)"), this);
    connect(testCrossCenterPtAct, SIGNAL(triggered()), this, SLOT(slotTestCrossCenterPtAct()));

	testDirCenterPtAct = new QAction(tr("Dir Action (1 pt seed)"), this);
    connect(testDirCenterPtAct, SIGNAL(triggered()), this, SLOT(slotTestDirCenterPtAct()));

	testRingCenterPtAct = new QAction(tr("Ring Action (1 pt seed)"), this);
    connect(testRingCenterPtAct, SIGNAL(triggered()), this, SLOT(slotTestRingCenterPtAct()));

	testSwirlCenterPtAct = new QAction(tr("Swirl Action (1 pt seed)"), this);
    connect(testSwirlCenterPtAct, SIGNAL(triggered()), this, SLOT(slotTestSwirlCenterPtAct()));

}

void MainWindow::createMenus()
{
    fileMenu = menuBar()->addMenu(tr("&File"));
    fileMenu->addAction(openAct);
    fileMenu->addSeparator();
    QAction *action = fileMenu->addAction(tr("Switch layout direction"));
    connect(action, SIGNAL(triggered()), this, SLOT(switchLayoutDirection()));
    fileMenu->addAction(exitAct);

    editMenu = menuBar()->addMenu(tr("&Edit"));

    windowMenu = menuBar()->addMenu(tr("&Window"));
    updateWindowMenu();
    connect(windowMenu, SIGNAL(aboutToShow()), this, SLOT(updateWindowMenu()));

    menuBar()->addSeparator();

    helpMenu = menuBar()->addMenu(tr("&Help"));
    helpMenu->addAction(aboutAct);
    helpMenu->addAction(aboutQtAct);

    testMenu = menuBar()->addMenu(tr("&Test"));
	testMenu->addAction(testCenterPtNbor4Act);
	testMenu->addAction(testLineNbor4Act);
	testMenu->addAction(testEdgeNbor4Act);
	testMenu->addAction(testDiskNbor4Act);
	testMenu->addAction(testNbor8CenterPtAct);
	testMenu->addAction(testConeCenterPtAct);
	testMenu->addAction(testCornerCenterPtAct);
	testMenu->addAction(testCrossCenterPtAct);
	testMenu->addAction(testDirCenterPtAct);
	testMenu->addAction(testRingCenterPtAct);
	testMenu->addAction(testSwirlCenterPtAct);
}

void MainWindow::createToolBars()
{
#if	1
    fileToolBar = addToolBar(tr("File"));
    fileToolBar->addAction(openAct);

    editToolBar = addToolBar(tr("Edit"));
	editToolBar->addAction(setSizeAct);
	editToolBar->addAction(recomputeAct);
	editToolBar->addAction(drawAct);
#endif
}

void MainWindow::createStatusBar()
{
    statusBar()->showMessage(tr("Ready"));
}

void MainWindow::readSettings()
{
    QSettings settings("Trolltech", "MDI Example");
    QPoint pos = settings.value("pos", QPoint(200, 200)).toPoint();
    QSize size = settings.value("size", QSize(400, 400)).toSize();
    move(pos);
    resize(size);
}

void MainWindow::writeSettings()
{
    QSettings settings("Trolltech", "MDI Example");
    settings.setValue("pos", pos());
    settings.setValue("size", size());
}

PbnMdi *MainWindow::activePbnMdi()
{
    if (QMdiSubWindow *activeSubWindow = mdiArea->activeSubWindow())
        return qobject_cast<PbnMdi *>(activeSubWindow->widget());
    return 0;
}

#if	0
QMdiSubWindow *MainWindow::findPbnMdi(const QString &fileName)
{
    QString canonicalFilePath = QFileInfo(fileName).canonicalFilePath();

    foreach (QMdiSubWindow *window, mdiArea->subWindowList()) {
        PbnMdi *mdiChild = qobject_cast<PbnMdi *>(window->widget());
        if (mdiChild->currentFile() == canonicalFilePath)
            return window;
    }
    return 0;
}
#endif

void MainWindow::switchLayoutDirection()
{
    if (layoutDirection() == Qt::LeftToRight)
        qApp->setLayoutDirection(Qt::RightToLeft);
    else
        qApp->setLayoutDirection(Qt::LeftToRight);
}

void MainWindow::setActiveSubWindow(QWidget *window)
{
    if (!window)
        return;
    mdiArea->setActiveSubWindow(qobject_cast<QMdiSubWindow *>(window));
}


// Widget Slots

void MainWindow::slotActiveSubWindowSetSize()
	{
	PbnMdi *pbn = activePbnMdi();
	if(!pbn)
		return;

	pbn->slotSetSize();
	}


void MainWindow::slotActiveSubWindowResequence()
	{
	PbnMdi *pbn = activePbnMdi();
	if(!pbn)
		return;

	pbn->slotResequenceAndPlay();
	}


void MainWindow::slotActiveSubWindowPlaySequence()
	{
	PbnMdi *pbn = activePbnMdi();
	if(!pbn)
		return;

	pbn->slotPlaySequence();
	}


void MainWindow::slotTestCenterPtNbor4Act()
	{
	Dimensions dims(1, 1); // XXX this proves that Dimensions is overused 
	PixelEnumerator *testEnum = new PixelEnumerator;
	testEnum->addSeed(new LineSeed(0.5, 0.5, 0.5, 0.5, new Weight(dims, 1.0)));
	testEnum->addAction(new NborAction(new Weight(dims, 1.0), 4));
	Pbn2DWidget *pbnWidget = new Pbn2DWidget(testEnum);
	makeMdiSubWindow(pbnWidget);
	}


void MainWindow::slotTestLineNbor4Act()
	{
	Dimensions dims(1, 1); // XXX this proves that Dimensions is overused 
	PixelEnumerator *testEnum = new PixelEnumerator;
	testEnum->addSeed(new LineSeed(0.25, 0.5, 0.75, 0.75, new Weight(dims, 1.0)));
	testEnum->addAction(new NborAction(new Weight(dims, 1.0), 4));
	Pbn2DWidget *pbnWidget = new Pbn2DWidget(testEnum);
	makeMdiSubWindow(pbnWidget);
	}


void MainWindow::slotTestEdgeNbor4Act()
	{
	Dimensions dims(1, 1); // XXX this proves that Dimensions is overused 
	PixelEnumerator *testEnum = new PixelEnumerator;
	testEnum->addSeed(new EdgeSeed(new Weight(dims, 1.0)));
	testEnum->addAction(new NborAction(new Weight(dims, 1.0), 4));
	Pbn2DWidget *pbnWidget = new Pbn2DWidget(testEnum);
	makeMdiSubWindow(pbnWidget);
	}


void MainWindow::slotTestDiskNbor4Act()
	{
	Dimensions dims(1, 1); // XXX this proves that Dimensions is overused 
	PixelEnumerator *testEnum = new PixelEnumerator;
	testEnum->addSeed(new DiskSeed(4, 4, 2, new Weight(dims, 1.0)));
	testEnum->addAction(new NborAction(new Weight(dims, 1.0), 4));
	Pbn2DWidget *pbnWidget = new Pbn2DWidget(testEnum);
	makeMdiSubWindow(pbnWidget);
	}


void MainWindow::slotTestNbor8CenterPtAct()
	{
	Dimensions dims(1, 1); // XXX this proves that Dimensions is overused 
	PixelEnumerator *testEnum = new PixelEnumerator;
	testEnum->addSeed(new LineSeed(0.5, 0.5, 0.5, 0.5, new Weight(dims, 1.0)));
	testEnum->addAction(new NborAction(new Weight(dims, 1.0), 8));
	Pbn2DWidget *pbnWidget = new Pbn2DWidget(testEnum);
	makeMdiSubWindow(pbnWidget);
	}


void MainWindow::slotTestConeCenterPtAct()
	{
	Dimensions dims(1, 1); // XXX this proves that Dimensions is overused 
	PixelEnumerator *testEnum = new PixelEnumerator;
	testEnum->addSeed(new LineSeed(0.5, 0.5, 0.5, 0.5, new Weight(dims, 1.0)));
	testEnum->addAction(new ConeAction(new Weight(dims, 1.0), 3));
	Pbn2DWidget *pbnWidget = new Pbn2DWidget(testEnum);
	makeMdiSubWindow(pbnWidget);
	}


void MainWindow::slotTestCornerCenterPtAct()
	{
	Dimensions dims(1, 1); // XXX this proves that Dimensions is overused 
	PixelEnumerator *testEnum = new PixelEnumerator;
	testEnum->addSeed(new LineSeed(0.5, 0.751, 0.5, 0.751, new Weight(dims, 1.0)));
	testEnum->addSeed(new LineSeed(0.5, 0.25, 0.5, 0.25, new Weight(dims, 1.0)));
	testEnum->addAction(new CornerAction(new Weight(dims, 1.0)));
	Pbn2DWidget *pbnWidget = new Pbn2DWidget(testEnum);
	makeMdiSubWindow(pbnWidget);
	}


void MainWindow::slotTestCrossCenterPtAct()
	{
	Dimensions dims(1, 1); // XXX this proves that Dimensions is overused 
	PixelEnumerator *testEnum = new PixelEnumerator;
	testEnum->addSeed(new LineSeed(0.5, 0.5, 0.5, 0.5, new Weight(dims, 1.0)));
	testEnum->addAction(new CrossAction(new Weight(dims, 1.0), 5));
	Pbn2DWidget *pbnWidget = new Pbn2DWidget(testEnum);
	makeMdiSubWindow(pbnWidget);
	}


void MainWindow::slotTestDirCenterPtAct()
	{
	Dimensions dims(1, 1); // XXX this proves that Dimensions is overused 
	PixelEnumerator *testEnum = new PixelEnumerator;
	testEnum->addSeed(new LineSeed(0.5, 0.5, 0.5, 0.5, new Weight(dims, 1.0)));
	testEnum->addAction(new DirAction(new Weight(dims, 100.0), new Weight(dims, 1.0)));
	Pbn2DWidget *pbnWidget = new Pbn2DWidget(testEnum);
	makeMdiSubWindow(pbnWidget);
	}


void MainWindow::slotTestRingCenterPtAct()
	{
	Dimensions dims(1, 1); // XXX this proves that Dimensions is overused 
	PixelEnumerator *testEnum = new PixelEnumerator;
	testEnum->addSeed(new LineSeed(0.5, 0.5, 0.5, 0.5, new Weight(dims, 1.0)));
	testEnum->addAction(new RingAction(new Weight(dims, 1.0), 3));
	Pbn2DWidget *pbnWidget = new Pbn2DWidget(testEnum);
	makeMdiSubWindow(pbnWidget);
	}


void MainWindow::slotTestSwirlCenterPtAct()
	{
	Dimensions dims(1, 1); // XXX this proves that Dimensions is overused 
	PixelEnumerator *testEnum = new PixelEnumerator;
	testEnum->addSeed(new LineSeed(0.5, 0.5, 0.5, 0.5, new Weight(dims, 1.0)));
	testEnum->addAction(new SwirlAction(new Weight(dims, 100.0), new Weight(dims, 1.0)));
	Pbn2DWidget *pbnWidget = new Pbn2DWidget(testEnum);
	makeMdiSubWindow(pbnWidget);
	}


//
// Create an MDI subwindow and make sure it gives the widget
// enough room to 
void MainWindow::makeMdiSubWindow(PbnMdi *pbnMdi
								 )
	{
	QMdiSubWindow* mdiSubWindow = mdiArea->addSubWindow(pbnMdi);
// 	pbnMdi->adjustSize();
	pbnMdi->show();
	mdiSubWindow->resize(pbnMdi->imageSize());
// 	mdiSubWindow->adjustSize();

	// The QMdiSubWjndow squeezes down the size of the PbnMdi
	// widget, find out by how much and expand it so it will be the
	// right size...
	QSize mdiSize = mdiSubWindow->size();
	QSize pbnSize = pbnMdi->size();
	QSize diffSize = mdiSize - pbnSize;

	mdiSubWindow->resize(mdiSize + diffSize);
	pbnMdi->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
	pbnMdi->setMinimumSize(pbnSize + diffSize);
	pbnMdi->setMaximumSize(pbnSize + diffSize);
	}


