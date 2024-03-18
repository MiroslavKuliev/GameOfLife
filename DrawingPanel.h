#pragma once
#include "wx/wx.h"
#include "Settings.h"
class DrawingPanel : public wxPanel
{
private:
	int grize = 15;
	std::vector<std::vector<bool>>* cellStates = nullptr;
	struct settings set;
	struct settings* set_ptr = &set;
public:
	DrawingPanel(wxFrame* parent);
	~DrawingPanel();
	void OnPaint(wxPaintEvent& event);
	void SetPanelSize(wxSize& size);
	void OnMouseUp(wxMouseEvent& event);
	void setColor(int deadColor, int livingColor)
	{
		set_ptr->colorLivingCells = livingColor;
		set_ptr->colorDeadCells = deadColor;

	}
	void setGridSize(int size)
	{
		grize = size;
	}
	void setStates(std::vector<std::vector<bool>>* states)
	{
		cellStates = states;
	}
	wxDECLARE_EVENT_TABLE();
};

