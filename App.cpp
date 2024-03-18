#include "App.h"

wxIMPLEMENT_APP(App);

App::App() {

}

App::~App() {

}

bool App::OnInit() {
	m_frame = new MainWindow();
	m_frame->Show();

	return true;
}