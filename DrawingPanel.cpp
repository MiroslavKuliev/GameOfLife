#include "DrawingPanel.h"
#include "wx/graphics.h"
#include "wx/dcbuffer.h"

wxBEGIN_EVENT_TABLE(DrawingPanel, wxPanel)
		EVT_PAINT(DrawingPanel::OnPaint)
	    EVT_LEFT_UP(DrawingPanel::OnMouseUp)
wxEND_EVENT_TABLE()

DrawingPanel::DrawingPanel(wxFrame* parent) : wxPanel(parent, wxID_ANY, wxPoint(0, 0)) 
{
	this->SetBackgroundStyle(wxBG_STYLE_PAINT);
	this->Bind(wxEVT_PAINT, &DrawingPanel::OnPaint, this);
	this->Bind(wxEVT_LEFT_UP, &DrawingPanel::OnMouseUp, this);


}

void DrawingPanel::OnMouseUp(wxMouseEvent& event) 
{
	int x, y;
	int cellWidth = this->GetSize().GetWidth() / grize;
	int cellHeight = this->GetSize().GetHeight() / grize;

	x = event.GetX();
	y = event.GetY();

	x = x / cellWidth;
	y = y / cellHeight;

	(*cellStates)[x][y] = !(*cellStates)[x][y];

	Refresh();

}

void DrawingPanel::OnPaint(wxPaintEvent& event) {
	wxAutoBufferedPaintDC dc(this);
	dc.Clear();

	wxGraphicsContext* context = wxGraphicsContext::Create(dc);
	if (!context) { return; }

	context->SetPen(*wxBLACK);
	context->SetBrush(*wxWHITE);		
	
	int cellWidth = this->GetSize().GetWidth() / grize;
	int cellHeight = this->GetSize().GetHeight() / grize;

	wxDouble x = 0 - cellWidth;
	wxDouble y = 0 - cellHeight;

	for (size_t i = 0; i < grize; i++)
	{
		for (size_t i = 0; i < grize; i++)
		{
			if ((*cellStates)[(cellWidth + x) / cellWidth][(cellHeight + y) / cellHeight]) 
			{
				if (set_ptr->colorLivingCells == 1)
				{
					context->SetBrush(*wxLIGHT_GREY);
				}	
				if (set_ptr->colorLivingCells == 2)
				{
					context->SetBrush(*wxYELLOW);
				}
			}
			else	
			{
				if (set_ptr->colorDeadCells == 1)
				{
					context->SetBrush(*wxWHITE);
				}
				if (set_ptr->colorDeadCells == 2)
				{
					context->SetBrush(*wxBLACK);
				}
			}
			context->DrawRectangle(cellWidth + x, cellHeight + y, cellWidth, cellHeight);
			x += cellWidth;
		}
		x = 0 - cellWidth;
		y += cellHeight;
	}
}

void DrawingPanel::SetPanelSize(wxSize& size)
{
	this->SetSize(size);
	Refresh();
}

DrawingPanel::~DrawingPanel() 
{

}