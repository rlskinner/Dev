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

#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

class PbnMdi;
QT_BEGIN_NAMESPACE
class QAction;
class QMenu;
class QMdiArea;
class QMdiSubWindow;
class QSignalMapper;
QT_END_NAMESPACE

class MainWindow : public QMainWindow
	{
	Q_OBJECT;

	public:
		MainWindow();

		static MainWindow* instance() { return s_instance; }

		void setActiveWindowToolBar(QToolBar *windowToolBar);

	protected:
		void closeEvent(QCloseEvent *event);

	private slots:
		//     void newFile();
		void open();
		//     void save();
		//     void saveAs();
		//     void cut();
		//     void copy();
		//     void paste();
		void about();
		void updateMenus();
		void updateWindowMenu();
// 		PbnMdi *createPbnMdi();
		void switchLayoutDirection();
		void setActiveSubWindow(QWidget *window);

		// Widget Slots
		void slotActiveSubWindowSetSize();
		void slotActiveSubWindowResequence();
		void slotActiveSubWindowPlaySequence();

		// Test slots
		void slotTestCenterPtNbor4Act();
		void slotTestLineNbor4Act();
		void slotTestEdgeNbor4Act();
		void slotTestDiskNbor4Act();
		void slotTestNbor8CenterPtAct();
		void slotTestConeCenterPtAct();
		void slotTestCornerCenterPtAct();
		void slotTestCrossCenterPtAct();
		void slotTestDirCenterPtAct();
		void slotTestRingCenterPtAct();
		void slotTestSwirlCenterPtAct();

	private:
		void createActions();
		void createMenus();
		void createToolBars();
		void createStatusBar();
		void readSettings();
		void writeSettings();
		PbnMdi *activePbnMdi();
		QMdiSubWindow *findPbnMdi(const QString &fileName);

		static MainWindow *s_instance;

		QMdiArea *mdiArea;
		QSignalMapper *windowMapper;

		QMenu *fileMenu;
		QMenu *editMenu;
		QMenu *windowMenu;
		QMenu *helpMenu;
		QToolBar *fileToolBar;
		QToolBar *editToolBar;
		QAction *openAct;
		QAction *exitAct;
		QAction *closeAct;
		QAction *closeAllAct;
		QAction *tileAct;
		QAction *cascadeAct;
		QAction *separatorAct;
		QAction *aboutAct;
		QAction *aboutQtAct;

		QAction *setSizeAct;
		QAction *recomputeAct;
		QAction *drawAct;

		QMenu	*testMenu;
		QAction *testCenterPtNbor4Act;
		QAction *testLineNbor4Act;
		QAction *testEdgeNbor4Act;
		QAction *testDiskNbor4Act;
		QAction *testNbor8CenterPtAct;
		QAction *testConeCenterPtAct;
		QAction *testCornerCenterPtAct;
		QAction *testCrossCenterPtAct;
		QAction *testDirCenterPtAct;
		QAction *testRingCenterPtAct;
		QAction *testSwirlCenterPtAct;

		void makeMdiSubWindow(PbnMdi *pbnWidget);
	}; // class MainWindow

#endif
