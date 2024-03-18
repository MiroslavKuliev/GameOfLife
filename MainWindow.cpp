#include "MainWindow.h"

wxBEGIN_EVENT_TABLE(MainWindow, wxFrame)
EVT_SIZE(MainWindow::OnSizeChange)
EVT_MENU(10001, MainWindow::OnGameStart)
EVT_MENU(10002, MainWindow::OnPauseGame)
EVT_MENU(10003, MainWindow::OnNextGame)
EVT_MENU(10004, MainWindow::OnTrashClean)
EVT_TIMER(20000, MainWindow::OnTimerStart)
EVT_MENU(25000, MainWindow::MenuEvent)
wxEND_EVENT_TABLE()

MainWindow::MainWindow() : wxFrame(nullptr, wxID_ANY, "Game Of Life", wxPoint(450, 450), wxSize(600, 600))
{
	menu = new wxMenu();
	menuBar = new wxMenuBar();

	statusBar = CreateStatusBar();
	statusBar->SetStatusText("Living Cells: " + std::to_string(livingCells) + ". Generation: " + std::to_string(generation) + ".");

	toolBar = CreateToolBar();

	wxBitmap playIcon(play_xpm);
	wxBitmap pauseIcon(pause_xpm);
	wxBitmap nextIcon(next_xpm);
	wxBitmap trashIcon(trash_xpm);

	toolBar->AddTool(10001, "Play", playIcon);
	toolBar->AddTool(10002, "Pause", pauseIcon);
	toolBar->AddTool(10003, "Next", nextIcon);
	toolBar->AddTool(10004, "Clean", trashIcon);

	_drawingPanel = new DrawingPanel(this);


	boxSizer = new wxBoxSizer(wxVERTICAL);
	boxSizer->Add(_drawingPanel, 1, wxEXPAND | wxALL);

	timer = new wxTimer(this, 20000);

	this->SetSizer(boxSizer);
	this->Bind(wxEVT_SIZE, &MainWindow::OnSizeChange, this);

	states.resize(sizeGrid);
	for (int i = 0; i < states.size(); i++)
	{
		states[i].resize(sizeGrid);
	}
	
	initGrid();

	this->Layout();

	toolBar->Realize();


	menu->Append(25000, "random");
	menuBar->Append(menu, "Menu");

	SetMenuBar(menuBar);
}

void MainWindow::OnSizeChange(wxSizeEvent& evt)
{
	wxSize windowSize = this->GetSize();
	_drawingPanel->SetPanelSize(windowSize);
	evt.Skip();
}

void MainWindow::initGrid()
{
	srand(time(NULL));

	for (int i = 0; i < states.size(); i++) {
		for (int j = 0; j < states[i].size(); j++) {
			int num = rand();
			states[i][j] = num % 100 < 45;
		}
	}
	_drawingPanel->setGridSize(sizeGrid);
	_drawingPanel->setStates(&states);
}

int MainWindow::NeighborCount(int row, int column)
{
	int NeighborNumber = 0;
	if (row != sizeGrid - 1)
	{
		if (states[row + 1][column])
			NeighborNumber++;
		if (column != sizeGrid - 1)
		{
			if (states[row + 1][column + 1])
				NeighborNumber++;
		}
	}
	if (row != 0)
	{
		if (states[row - 1][column])
			NeighborNumber++;
		if (column != 0)
		{
			if (states[row - 1][column - 1])
				NeighborNumber++;
		}
	}
	
	if (column != 0 && states[row][column - 1])
		NeighborNumber++;
	if (column != sizeGrid - 1 && states[row][column + 1])
		NeighborNumber++;

	if (row != 0 && column != sizeGrid - 1)
	{
		if (states[row - 1][column + 1])
			NeighborNumber++;
	}
	if (row != sizeGrid - 1 && column != 0)
	{
		if (states[row + 1][column - 1])
			NeighborNumber++;
	}

	return NeighborNumber;
}

void MainWindow::NextGeneration()
{
	std::vector<std::vector<bool>> sandBox;
	sandBox.resize(sizeGrid);

	for (size_t i = 0; i < sandBox.size(); i++)
	{
		sandBox[i].resize(sizeGrid);
	}

	livingCells = 0;
	for (size_t i = 0; i < sizeGrid; i++)
	{
		for (size_t j = 0; j < sizeGrid; j++)
		{
			int num = NeighborCount(i, j);
			if (states[i][j] && num < 2)
			{
				sandBox[i][j] = false;
			}
			if (states[i][j] && num > 3)
			{
				sandBox[i][j] = false;
			}
			if (states[i][j] && (num == 2 || num == 3))
			{
				sandBox[i][j] = true;
				livingCells++;
			}
			if (!states[i][j] && num == 3)
			{
				sandBox[i][j] = true;
				livingCells++;
			}
		}
	}
	states.swap(sandBox);
	generation++;
	statusBar->SetStatusText("Living Cells: " + std::to_string(livingCells) + ". Generation: " + std::to_string(generation) + ".");
	_drawingPanel->Refresh();
}

void MainWindow::OnGameStart(wxCommandEvent& evt)
{
	timer->Start(timerms);
}

void MainWindow::OnTrashClean(wxCommandEvent& evt)
{
	livingCells = 0;
	generation = 0;
	for (size_t i = 0; i < sizeGrid; i++)
	{
		for (size_t j = 0; j < sizeGrid; j++)
		{
			states[i][j] = false;			
		}
	}
	statusBar->SetStatusText("Living Cells: " + std::to_string(livingCells) + ". Generation: " + std::to_string(generation) + ".");
	_drawingPanel->Refresh();
}

void MainWindow::OnNextGame(wxCommandEvent& evt)
{
	NextGeneration();
}

void MainWindow::OnPauseGame(wxCommandEvent& evt)
{
	timer->Stop();
}

void MainWindow::OnTimerStart(wxTimerEvent& evt) 
{
	NextGeneration();
}

void MainWindow::MenuEvent(wxCommandEvent& evt)
{
	_settingsDialog = new SettingsDialog(this);

	if (_settingsDialog->ShowModal() == wxID_OK)
	{
		initGrid();
		_drawingPanel->Refresh();
	}
	evt.Skip();
}

MainWindow::~MainWindow()
{

}
