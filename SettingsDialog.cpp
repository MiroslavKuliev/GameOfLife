#include "SettingsDialog.h"

wxBEGIN_EVENT_TABLE(SettingsDialog, wxDialog)
EVT_SPINCTRL(30000, SettingsDialog::OnSpinControl)
EVT_COLOURPICKER_CHANGED(30001, SettingsDialog::OnColorControl)
wxEND_EVENT_TABLE()

SettingsDialog::SettingsDialog(wxWindow* parent) : wxDialog(parent, wxID_ANY, "Settings")
{
	set_ptr = &set;
	mainBox = new wxBoxSizer(wxVERTICAL);
	this->SetSizer(mainBox);
	childBox1 = new wxBoxSizer(wxHORIZONTAL);
	childBox2 = new wxBoxSizer(wxHORIZONTAL);
	label1 = new wxStaticText(this, wxID_ANY, "1234");
	label2 = new wxStaticText(this, wxID_ANY, "4321");
	spinControl = new wxSpinCtrl(this, 30000);
	colorControl = new wxColourPickerCtrl(this, 30001);

	mainBox->Add(childBox1);
	mainBox->Add(childBox2);

	buttons = CreateButtonSizer(wxOK | wxCANCEL);

	childBox1->Add(label1, 1, wxEXPAND | wxALL);
	childBox1->Add(spinControl, 1, wxEXPAND | wxALL);
	childBox1->Add(buttons, 1, wxEXPAND | wxALL);

	childBox2->Add(label2, 1, wxEXPAND | wxALL);
	childBox2->Add(colorControl, 1, wxEXPAND | wxALL);
	childBox2->Add(buttons, 1, wxEXPAND | wxALL);
}

void SettingsDialog::OnSpinControl(wxSpinEvent& evt)
{
	set_ptr->interval = evt.GetValue();
}

void SettingsDialog::OnColorControl(wxColourPickerEvent& evt)
{
	if (evt.GetColour() == *wxWHITE)
		set_ptr->colorDeadCells = 1;

	if (evt.GetColour() == *wxBLACK)
		set_ptr->colorDeadCells = 2;
}

SettingsDialog::~SettingsDialog() 
{

}

