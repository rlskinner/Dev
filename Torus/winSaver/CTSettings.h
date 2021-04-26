#ifndef _CTSettings_h_
#define _CTSettings_h_

#include <qdialog.h>
#include <qsettings.h>
#include "FormSettingsDialog.h"

// 
// Settings object:
// 		- holds the application settings
// 		- fetches values from the registry 
// 		- saves values to the registry
// 		- initializes default settings values
//
class CTSettings
	{
	// Data Members
	private:
		int     maxCellHits_;		// # of attractor hits in one cell to stop
		int     maxIterations_;		// stop after # of attractor iterations
		float	paramStepSize_;		// step size in param space
		int		tileSize_;			// size of tile in pixels
		float	lookupTableSize_;	// size of lookup table (* tile size)
		QSettings registry_;		// registry setting object

		// Registry paths -- nothing fancy for now
		static QString	applicationPath_;
		static QString	attractorPath_;
		static QString	maxCellHitsKey_;
		static QString	maxIterationsKey_;
		static QString	paramStepSizeKey_;
		static QString	tileSizeKey_;
		static QString	lookupTableSizeKey_;

	// Constructors
	public:
		CTSettings();

	// Get Operations
	public:
		int maxCellHits() { return maxCellHits_; }
		int maxIterations() { return maxIterations_; }
		float paramStepSize() { return paramStepSize_; }
		int tileSize() { return tileSize_; }
		float lookupTableSize() { return lookupTableSize_; }

	// Set Operations
	public:
		void setMaxCellHits(int v) { maxCellHits_ = v; }
		void setMaxIterations(int v) { maxIterations_ = v; }
		void setParamStepSize(float v) { paramStepSize_ = v; }
		void setTileSize(int v) { tileSize_ = v; }
		void setLookupTableSize(float v) { lookupTableSize_ = v; }

	// Registry Management
	public:
		void readSettings();
		void saveSettings();

	// Value Management
	public:
		void defaultValues();

	// Value Access

	};


// 
// QDialog for saving the settings in the registry
//
class CTSettingsDialog : public FormSettingsDialog
	{
	Q_OBJECT;

	public:
		const static int cNumParamStepDecimals = 5;
		const static int cNumLookupTableDecimals = 2;

	private:
		CTSettings settings_; // values for the user to change

	public:
		CTSettingsDialog(bool modal);

	public slots:
		virtual void slotMaxNumCellHits(int value);
		virtual void slotMaxIterPerFrame(const QString &);
		void slotParamStepSize(const QString &);
		void slotTileSize(const QString &);
		void slotLookupTableSize(const QString &);

		virtual void accept();
		virtual void reject();

	};

#endif // _CTSettings_h_
