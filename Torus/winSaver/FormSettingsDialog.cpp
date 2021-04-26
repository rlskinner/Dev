/****************************************************************************
** Form implementation generated from reading ui file 'FormSettingsDialog.ui'
**
** Created: Mon Oct 16 21:39:53 2006
**      by: The User Interface Compiler ($Id: qt/main.cpp   3.3.6   edited Aug 31 2005 $)
**
** WARNING! All changes made in this file will be lost!
****************************************************************************/

#include "FormSettingsDialog.h"

#include <qvariant.h>
#include <qlineedit.h>
#include <qlabel.h>
#include <qspinbox.h>
#include <qpushbutton.h>
#include <qlayout.h>
#include <qtooltip.h>
#include <qwhatsthis.h>
#include <qimage.h>
#include <qpixmap.h>

/*
 *  Constructs a FormSettingsDialog as a child of 'parent', with the
 *  name 'name' and widget flags set to 'f'.
 *
 *  The dialog will by default be modeless, unless you set 'modal' to
 *  TRUE to construct a modal dialog.
 */
FormSettingsDialog::FormSettingsDialog( QWidget* parent, const char* name, bool modal, WFlags fl )
    : QDialog( parent, name, modal, fl )
{
    if ( !name )
	setName( "FormSettingsDialog" );

    QWidget* privateLayoutWidget = new QWidget( this, "layout5" );
    privateLayoutWidget->setGeometry( QRect( 12, 12, 220, 151 ) );
    layout5 = new QVBoxLayout( privateLayoutWidget, 0, 5, "layout5"); 

    layout2 = new QGridLayout( 0, 1, 1, 0, 6, "layout2"); 

    lookupTableSizeLineEdit_ = new QLineEdit( privateLayoutWidget, "lookupTableSizeLineEdit_" );
    lookupTableSizeLineEdit_->setFrameShape( QLineEdit::LineEditPanel );
    lookupTableSizeLineEdit_->setFrameShadow( QLineEdit::Sunken );

    layout2->addWidget( lookupTableSizeLineEdit_, 4, 1 );

    maxIterPerFrameLineEdit_ = new QLineEdit( privateLayoutWidget, "maxIterPerFrameLineEdit_" );

    layout2->addWidget( maxIterPerFrameLineEdit_, 1, 1 );

    lookupTableSizeLabel_ = new QLabel( privateLayoutWidget, "lookupTableSizeLabel_" );

    layout2->addWidget( lookupTableSizeLabel_, 4, 0 );

    paramStepSizeLineEdit_ = new QLineEdit( privateLayoutWidget, "paramStepSizeLineEdit_" );

    layout2->addWidget( paramStepSizeLineEdit_, 2, 1 );

    tileSizeLineEdit_ = new QLineEdit( privateLayoutWidget, "tileSizeLineEdit_" );

    layout2->addWidget( tileSizeLineEdit_, 3, 1 );

    paramStepSizeLabel_ = new QLabel( privateLayoutWidget, "paramStepSizeLabel_" );

    layout2->addWidget( paramStepSizeLabel_, 2, 0 );

    maxIterPerFrameLabel_ = new QLabel( privateLayoutWidget, "maxIterPerFrameLabel_" );

    layout2->addWidget( maxIterPerFrameLabel_, 1, 0 );

    tileSizeLabel_ = new QLabel( privateLayoutWidget, "tileSizeLabel_" );

    layout2->addWidget( tileSizeLabel_, 3, 0 );

    maxNumCellHitsSpinBox_ = new QSpinBox( privateLayoutWidget, "maxNumCellHitsSpinBox_" );
    maxNumCellHitsSpinBox_->setMaxValue( 255 );
    maxNumCellHitsSpinBox_->setMinValue( 1 );
    maxNumCellHitsSpinBox_->setValue( 100 );

    layout2->addWidget( maxNumCellHitsSpinBox_, 0, 1 );

    maxNumCellHitsLabel_ = new QLabel( privateLayoutWidget, "maxNumCellHitsLabel_" );

    layout2->addWidget( maxNumCellHitsLabel_, 0, 0 );
    layout5->addLayout( layout2 );

    layout4 = new QHBoxLayout( 0, 0, 6, "layout4"); 

    okPB_ = new QPushButton( privateLayoutWidget, "okPB_" );
    layout4->addWidget( okPB_ );

    cancelPB_ = new QPushButton( privateLayoutWidget, "cancelPB_" );
    layout4->addWidget( cancelPB_ );
    spacer1 = new QSpacerItem( 40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum );
    layout4->addItem( spacer1 );
    layout5->addLayout( layout4 );
    languageChange();
    resize( QSize(244, 175).expandedTo(minimumSizeHint()) );
    clearWState( WState_Polished );

    // signals and slots connections
    connect( okPB_, SIGNAL( clicked() ), this, SLOT( accept() ) );
    connect( cancelPB_, SIGNAL( clicked() ), this, SLOT( reject() ) );

    // tab order
    setTabOrder( maxNumCellHitsSpinBox_, maxIterPerFrameLineEdit_ );
    setTabOrder( maxIterPerFrameLineEdit_, paramStepSizeLineEdit_ );
    setTabOrder( paramStepSizeLineEdit_, tileSizeLineEdit_ );
    setTabOrder( tileSizeLineEdit_, lookupTableSizeLineEdit_ );
    setTabOrder( lookupTableSizeLineEdit_, okPB_ );
    setTabOrder( okPB_, cancelPB_ );
}

/*
 *  Destroys the object and frees any allocated resources
 */
FormSettingsDialog::~FormSettingsDialog()
{
    // no need to delete child widgets, Qt does it all for us
}

/*
 *  Sets the strings of the subwidgets using the current
 *  language.
 */
void FormSettingsDialog::languageChange()
{
    setCaption( tr( "ChaosTorus Settings" ) );
    lookupTableSizeLabel_->setText( tr( "Lookup Table Size" ) );
    paramStepSizeLabel_->setText( tr( "Parameter Step Size" ) );
    maxIterPerFrameLabel_->setText( tr( "Max Iterations / Frame" ) );
    tileSizeLabel_->setText( tr( "Tile Size (pixels)" ) );
    maxNumCellHitsLabel_->setText( tr( "Max Number of Cell Hits" ) );
    okPB_->setText( tr( "Ok" ) );
    cancelPB_->setText( tr( "Cancel" ) );
}

