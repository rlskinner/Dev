#include "CTSettings.h"

#include <qlineedit.h>
#include <qpushbutton.h>
#include <qspinbox.h>
#include <qvalidator.h>

#include <iostream>

using namespace std;

/////////////////////////////////////////////////////////////////////////////
//
//  Class CTSettings
//
QString CTSettings::applicationPath_	= "/Chaotic Torus";
QString CTSettings::attractorPath_		= "/Attractor";
QString CTSettings::maxCellHitsKey_		= "/Max Cell Hits";
QString CTSettings::maxIterationsKey_	= "/Max Iterations";
QString CTSettings::paramStepSizeKey_	= "/Param Step Size";
QString CTSettings::tileSizeKey_		= "/Tile Size";
QString CTSettings::lookupTableSizeKey_	= "/Lookup Table Size";

// Constructors
//
// Construct the Chaotic Torus settings structure.  
// The contents will be the default values replaced by values read from the
// registry, if any.
CTSettings::CTSettings()
	: registry_()
	{
	// initialize registry setting
	// NOTE 1:  this puts the registry settings in 
	// 		HKEY_LOCAL_MACHINE\SOFTWARE\<applicationPath_>
	// 	I would like to have them in CURRENT_USER, but it looks like 
	// 	QSettings just won't do that if the user can write to LOCAL_MACHINE.
	// NOTE 2:  when debugging QSettings with regedit, be sure to hit
	// 	"Refresh" after the program makes changes.
	registry_.insertSearchPath(QSettings::Windows, applicationPath_);
	
	// start with default values and overlay the values from the registry
	defaultValues();
	readSettings();
	}


// Registry Management
//
// Read values from registry
//
void CTSettings::readSettings()
	{
	registry_.beginGroup(attractorPath_); // 'Attractor' style / tab
		{
		maxCellHits_ = registry_.readNumEntry(maxCellHitsKey_, 100);
		maxIterations_ = registry_.readNumEntry(maxIterationsKey_, 10000);
		paramStepSize_ = registry_.readDoubleEntry(paramStepSizeKey_, 0.05);
		tileSize_ = registry_.readNumEntry(tileSizeKey_, 256);
		lookupTableSize_ = registry_.readDoubleEntry(lookupTableSizeKey_, 2.0);
		}
	registry_.endGroup(); // Attractor style / tab
	}


// Registry Management
//
// Save values to registry
//
void CTSettings::saveSettings()
	{
	registry_.beginGroup(attractorPath_); // 'Attractor' style / tab
		{
		registry_.writeEntry(maxCellHitsKey_, maxCellHits_);
		registry_.writeEntry(maxIterationsKey_, maxIterations_);
		registry_.writeEntry(paramStepSizeKey_, paramStepSize_);
		registry_.writeEntry(tileSizeKey_, tileSize_);
		registry_.writeEntry(lookupTableSizeKey_, lookupTableSize_);
		}
	registry_.endGroup(); // Attractor style / tab
	}


// Value Management
//
// Save all values in registry
//
void CTSettings::defaultValues()
	{
    maxIterations_   = 10000;
    maxCellHits_     = 100;
    paramStepSize_   = .05f;
    tileSize_        = 256;
    lookupTableSize_ = 2.0;
	}


/****************************************************************************/
CTSettingsDialog::CTSettingsDialog(bool modal)
	: FormSettingsDialog(0, "CTSettingsDialog", modal)
	, settings_()
	{
	// initialize dialog from the registry
	
	// layout
	adjustSize();

	// connections
	connect(maxNumCellHitsSpinBox_, SIGNAL(valueChanged(int)), this, SLOT(slotMaxNumCellHits(int)));
	connect(maxIterPerFrameLineEdit_, SIGNAL(textChanged(const QString &)), this, SLOT(slotMaxIterPerFrame(const QString &)));
	connect(paramStepSizeLineEdit_, SIGNAL(textChanged(const QString &)), this, SLOT(slotParamStepSize(const QString &)));
	connect(tileSizeLineEdit_, SIGNAL(textChanged(const QString &)), this, SLOT(slotTileSize(const QString &)));
	QObject::connect(lookupTableSizeLineEdit_, SIGNAL(textChanged(const QString &)), this, SLOT(slotLookupTableSize(const QString &)));

	// validators
	QIntValidator *intValidtor;
	intValidtor = new QIntValidator(maxIterPerFrameLineEdit_);
	intValidtor->setRange(1, 1 << 16);
	maxIterPerFrameLineEdit_->setValidator(intValidtor);

	intValidtor = new QIntValidator(tileSizeLineEdit_);
	intValidtor->setRange(5, 4000);
	tileSizeLineEdit_->setValidator(intValidtor);

	QDoubleValidator *dblValidtor;
	dblValidtor = new QDoubleValidator(paramStepSizeLineEdit_);
	dblValidtor->setRange(0.0001, 1.0);
	dblValidtor->setDecimals(cNumParamStepDecimals);
	paramStepSizeLineEdit_->setValidator(dblValidtor);

	dblValidtor = new QDoubleValidator(lookupTableSizeLineEdit_);
	dblValidtor->setRange(1.0, 10.0);
	dblValidtor->setDecimals(cNumLookupTableDecimals);
	lookupTableSizeLineEdit_->setValidator(dblValidtor);

	// initialize values
	maxNumCellHitsSpinBox_->setValue(settings_.maxCellHits());
	maxIterPerFrameLineEdit_->setText(QString::number(settings_.maxIterations()));
	tileSizeLineEdit_->setText(QString::number(settings_.tileSize()));
	paramStepSizeLineEdit_->setText(QString::number(settings_.paramStepSize(), 'g', cNumParamStepDecimals));
	lookupTableSizeLineEdit_->setText(QString::number(settings_.lookupTableSize(), 'g', cNumLookupTableDecimals));
	}

void CTSettingsDialog::slotMaxNumCellHits(int value)
	{
	cout << "slotMaxNumCellHits: " << value << endl;
	settings_.setMaxCellHits(value);
	}


void CTSettingsDialog::slotMaxIterPerFrame(const QString &str)
	{
	if(maxIterPerFrameLineEdit_->hasAcceptableInput())
		{
		cout << "slotMaxIterPerFrame: " << str << endl;
		settings_.setMaxIterations(str.toInt());
		}
	}


void CTSettingsDialog::slotParamStepSize(const QString &str)
	{
	if(paramStepSizeLineEdit_->hasAcceptableInput())
		{
		cout << "slotParamStepSize: " << str << endl;
		settings_.setParamStepSize(str.toDouble());
		}
	}


void CTSettingsDialog::slotTileSize(const QString &str)
	{
	if(tileSizeLineEdit_->hasAcceptableInput())
		{
		cout << "slotTileSize: " << str << endl;
		settings_.setTileSize(str.toInt());
		}
	}


void CTSettingsDialog::slotLookupTableSize(const QString &str)
	{
	if(lookupTableSizeLineEdit_->hasAcceptableInput())
		{
		cout << "slotLookupTableSize: " << str << endl;
		settings_.setLookupTableSize(str.toDouble());
		}
	}


// Accept the dialog: write the new values out to the registry
void CTSettingsDialog::accept()
	{
	QDialog::done(Accepted);
	settings_.saveSettings();
	}


// Reject the dialog: just go away
void CTSettingsDialog::reject()
	{
	QDialog::done(Rejected);
	}


