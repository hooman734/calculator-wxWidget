#include "App.h"
#include "MainFrame.h"
#include <wx/wx.h>

wxIMPLEMENT_APP(App);

bool App::OnInit() {
	auto* mainFrame = new MainFrame("Calculator - Hooman");
	mainFrame->SetClientSize(450, 500);
	mainFrame->Show();

	return true;
}