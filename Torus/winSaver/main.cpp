#include <iostream>
#include <string>
#include <qapplication.h>

#include "CTSettings.h"
#include "CTDisplay.h"

using namespace std;

enum ExecutionMode 
	{
	cShowSettings, // show the Settings Dialog box
	cShowSettingsModal, // show the Settings Dialog box, modal to foreground window
	cPreview, // preview screen saver
	cRunSaver, // run the screen saver
	cRunDebugWindow, // run screen saver in a less-than-full-screen window
	};

ExecutionMode parseArgs(int argc, char **argv, WId &previewWindow)
	{
	--argc;
	++argv;

	for(; *argv; ++argv)
		{
		string arg(*argv);
		if(arg == "/c")
			return cShowSettingsModal;

		if(arg == "/s")
			return cRunSaver;

		if(arg == "/p")
			{
			++argv;
			cout << "/p " << *argv << endl;
			long wid = strtol(*argv, 0, 10);
			cout << "decimal wid = " << wid << endl;
			previewWindow = WId(wid);
			return cPreview;
			}

		if(arg == "/d")
			return cRunDebugWindow;
		}

	return cShowSettings;
	}


//
//  Show the Settings dialog
//
int showSettings(bool modal)
	{
	CTSettingsDialog *dialog = new CTSettingsDialog(modal);
	return dialog->exec();
	}


//
//  Run the saver as a child of the given window, if any
//
int runSaver(QApplication &app, bool fullScreen, WId window = 0)
	{
    if(!QGLFormat::hasOpenGL()) 
		{
		qWarning( "This system has no OpenGL support. Exiting." );
		return -1;
		}

	CTDisplay *display = new CTDisplay(fullScreen, window);
	app.setMainWidget(display);
	display->show();
	return app.exec();
	}


//
//  Main program: 
//  	- parse arguments
//  	- set modes
//  	- start application
//
int main(int argc, char **argv)
	{
	const bool cModal = true;
	const bool cFullScreen = true;

	WId previewWindow;
	ExecutionMode mode = parseArgs(argc, argv, previewWindow);
	QApplication app(argc, argv);

	switch(mode)
		{
		case cShowSettings:
			cout << "Show settings" << endl;
			showSettings(!cModal);
			break;
		case cShowSettingsModal:
			cout << "Show settings modal" << endl;
			showSettings(cModal);
			break;
		case cPreview:
			cout << "Preview, HWND = " << previewWindow << endl;
			printf("Preview, HWND = 0x%x\n", previewWindow);
			return runSaver(app, !cFullScreen, previewWindow);
			break;
		case cRunSaver:
			cout << "Run Saver" << endl;
			return runSaver(app, cFullScreen);
			break;
		case cRunDebugWindow:
			cout << "Run Saver in debug window" << endl;
			return runSaver(app, !cFullScreen);
			break;
		}

	return 0;
	}

