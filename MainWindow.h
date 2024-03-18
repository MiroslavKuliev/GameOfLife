#pragma once
#include "DrawingPanel.h"
#include "wx/wx.h"
#include "Settings.h"
#include "Icons/trash.xpm"
#include "Icons/pause.xpm"
#include "Icons/play.xpm"
#include "Icons/next.xpm"
#include "SettingsDialog.h"

class MainWindow : public wxFrame
{
private:
	DrawingPanel* _drawingPanel = nullptr;
	wxBoxSizer* boxSizer;
	SettingsDialog* _settingsDialog = nullptr;
	wxStatusBar* statusBar;
	wxMenuBar* menuBar;
	wxMenu* menu;
	wxToolBar* toolBar;
	wxTimer* timer;
	std::vector<std::vector<bool>> states;
	struct settings set;
	int sizeGrid = set.sizeGrid;
	int generation;
	int livingCells;
	int timerms = set.interval;
public:
	void initGrid();
	int NeighborCount(int row, int column);
	void NextGeneration();
	MainWindow();
	~MainWindow();
	void OnSizeChange(wxSizeEvent& evt);
	void OnGameStart(wxCommandEvent& evt);
	void OnTrashClean(wxCommandEvent& evt);
	void OnNextGame(wxCommandEvent& evt);
	void OnPauseGame(wxCommandEvent& evt);
	void OnTimerStart(wxTimerEvent& evt);
	void MenuEvent(wxCommandEvent& evt);
	wxDECLARE_EVENT_TABLE();
};

