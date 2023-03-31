#pragma once
#include <wx/wx.h>

class MainFrame : public wxFrame {
public:
	explicit MainFrame(const wxString& title);
private:
    wxString expression;
    wxTextCtrl* input;
    void OnHitKey(wxCommandEvent& evt, const wxString& key);
    void OnExecute(wxCommandEvent& evt);
    void OnDelete(wxCommandEvent& evt);
    void OnHitKeyboard(wxKeyEvent& evt);
};