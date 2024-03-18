#pragma once
#include "wx/wx.h"
#include "Settings.h"
#include "wx/spinctrl.h"
#include "wx/clrpicker.h"

class SettingsDialog : public wxDialog
{
private:
	settings set;
	settings* set_ptr;
	wxBoxSizer* mainBox;
	wxBoxSizer* childBox1;
	wxBoxSizer* childBox2;
	wxStaticText* label1;
	wxStaticText* label2;
	wxSpinCtrl* spinControl;
	wxColourPickerCtrl* colorControl;
	wxSizer* buttons;
public:
	SettingsDialog(wxWindow* parent);
	~SettingsDialog();
	void OnSpinControl(wxSpinEvent& evt);
	void OnColorControl(wxColourPickerEvent& evt);
	wxDECLARE_EVENT_TABLE();
};

