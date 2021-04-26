/****************************************************************************
** Form interface generated from reading ui file 'FormSettingsDialog.ui'
**
** Created: Mon Oct 16 21:39:52 2006
**      by: The User Interface Compiler ($Id: qt/main.cpp   3.3.6   edited Aug 31 2005 $)
**
** WARNING! All changes made in this file will be lost!
****************************************************************************/

#ifndef FORMSETTINGSDIALOG_H
#define FORMSETTINGSDIALOG_H

#include <qvariant.h>
#include <qdialog.h>

class QVBoxLayout;
class QHBoxLayout;
class QGridLayout;
class QSpacerItem;
class QLineEdit;
class QLabel;
class QSpinBox;
class QPushButton;

class FormSettingsDialog : public QDialog
{
    Q_OBJECT

public:
    FormSettingsDialog( QWidget* parent = 0, const char* name = 0, bool modal = FALSE, WFlags fl = 0 );
    ~FormSettingsDialog();

    QLineEdit* lookupTableSizeLineEdit_;
    QLineEdit* maxIterPerFrameLineEdit_;
    QLabel* lookupTableSizeLabel_;
    QLineEdit* paramStepSizeLineEdit_;
    QLineEdit* tileSizeLineEdit_;
    QLabel* paramStepSizeLabel_;
    QLabel* maxIterPerFrameLabel_;
    QLabel* tileSizeLabel_;
    QSpinBox* maxNumCellHitsSpinBox_;
    QLabel* maxNumCellHitsLabel_;
    QPushButton* okPB_;
    QPushButton* cancelPB_;

protected:
    QVBoxLayout* layout5;
    QGridLayout* layout2;
    QHBoxLayout* layout4;
    QSpacerItem* spacer1;

protected slots:
    virtual void languageChange();

};

#endif // FORMSETTINGSDIALOG_H
