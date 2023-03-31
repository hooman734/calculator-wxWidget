#include "MainFrame.h"
#include "MathParser.h"
#include <wx/wx.h>


MainFrame::MainFrame(const wxString& title) : wxFrame(nullptr, wxID_ANY, title) {
    const auto size = 60;
    const auto gap = 15;
    const auto sides = 45;
    const auto top = 200;
    const auto displayWidth = 360;
    const auto displayHeight = 70;

	auto* panel = new wxPanel(this, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxWANTS_CHARS);

    // Keys
	auto* one = new wxButton(panel, wxID_ANY, "1", wxPoint(sides, top), wxSize(size, size));
    auto* two = new wxButton(panel, wxID_ANY, "2", wxPoint(sides + (size + gap), top), wxSize(size, size));
    auto* three = new wxButton(panel, wxID_ANY, "3", wxPoint(sides + 2 * (size + gap), top), wxSize(size, size));
    auto* openBracket = new wxButton(panel, wxID_ANY, "(", wxPoint(sides + 3 * (size + gap), top), wxSize(size, size));
    auto* four = new wxButton(panel, wxID_ANY, "4", wxPoint(sides, top + (size + gap)), wxSize(size, size));
    auto* five = new wxButton(panel, wxID_ANY, "5", wxPoint(sides + (size + gap), top + (size + gap)), wxSize(size, size));
    auto* six = new wxButton(panel, wxID_ANY, "6", wxPoint(sides + 2 * (size + gap), top + (size + gap)), wxSize(size, size));
    auto* add = new wxButton(panel, wxID_ANY, "+", wxPoint(sides + 3 * (size + gap), top + (size + gap)), wxSize(size, size));
    auto* seven = new wxButton(panel, wxID_ANY, "7", wxPoint(sides, top + 2 * (size + gap)), wxSize(size, size));
    auto* eight = new wxButton(panel, wxID_ANY, "8", wxPoint(sides + (size + gap), top + 2 * (size + gap)), wxSize(size, size));
    auto* nine = new wxButton(panel, wxID_ANY, "9", wxPoint(sides + 2 * (size + gap), top + 2 * (size + gap)), wxSize(size, size));
    auto* divide = new wxButton(panel, wxID_ANY, "/", wxPoint(sides + 3 * (size + gap), top + 2 * (size + gap)), wxSize(size, size));
    auto* closeBracket = new wxButton(panel, wxID_ANY, ")", wxPoint(sides + 4 * (size + gap), top), wxSize(size, size));
    auto* subtract = new wxButton(panel, wxID_ANY, "-", wxPoint(sides + 4 * (size + gap), top + (size + gap)), wxSize(size, size));
    auto* multiply = new wxButton(panel, wxID_ANY, "x", wxPoint(sides + 4 * (size + gap), top + 2 * (size + gap)), wxSize(size, size));
    auto* execute = new wxButton(panel, wxID_ANY, "EXE", wxPoint(sides + 4 * (size + gap), top + 3 * (size + gap)), wxSize(size, size));
    auto* zero = new wxButton(panel, wxID_ANY, "0", wxPoint(sides + (size + gap), top + 3 * (size + gap)), wxSize(size, size));
    auto* del = new wxButton(panel, wxID_ANY, "Del", wxPoint(sides + 2 * (size + gap), top + 3 * (size + gap)), wxSize(size, size));
    auto* power = new wxButton(panel, wxID_ANY, "^", wxPoint(sides + 3 * (size + gap), top + 3 * (size + gap)), wxSize(size, size));
    auto* point = new wxButton(panel, wxID_ANY, ".", wxPoint(sides, top + 3 * (size + gap)), wxSize(size, size));

    // Bind Keys
    one->Bind(wxEVT_COMMAND_BUTTON_CLICKED, [this](auto evt) { MainFrame::OnHitKey(evt, "1"); });
    two->Bind(wxEVT_COMMAND_BUTTON_CLICKED, [this](auto evt) { MainFrame::OnHitKey(evt, "2"); });
    three->Bind(wxEVT_COMMAND_BUTTON_CLICKED, [this](auto evt) { MainFrame::OnHitKey(evt, "3"); });
    four->Bind(wxEVT_COMMAND_BUTTON_CLICKED, [this](auto evt) { MainFrame::OnHitKey(evt, "4"); });
    five->Bind(wxEVT_COMMAND_BUTTON_CLICKED, [this](auto evt) { MainFrame::OnHitKey(evt, "5"); });
    six->Bind(wxEVT_COMMAND_BUTTON_CLICKED, [this](auto evt) { MainFrame::OnHitKey(evt, "6"); });
    seven->Bind(wxEVT_COMMAND_BUTTON_CLICKED, [this](auto evt) { MainFrame::OnHitKey(evt, "7"); });
    eight->Bind(wxEVT_COMMAND_BUTTON_CLICKED, [this](auto evt) { MainFrame::OnHitKey(evt, "8"); });
    nine->Bind(wxEVT_COMMAND_BUTTON_CLICKED, [this](auto evt) { MainFrame::OnHitKey(evt, "9"); });
    zero->Bind(wxEVT_COMMAND_BUTTON_CLICKED, [this](auto evt) { MainFrame::OnHitKey(evt, "0"); });
    point->Bind(wxEVT_COMMAND_BUTTON_CLICKED, [this](auto evt) { MainFrame::OnHitKey(evt, "."); });
    add->Bind(wxEVT_COMMAND_BUTTON_CLICKED, [this](auto evt) { MainFrame::OnHitKey(evt, "+"); });
    subtract->Bind(wxEVT_COMMAND_BUTTON_CLICKED, [this](auto evt) { MainFrame::OnHitKey(evt, "-"); });
    divide->Bind(wxEVT_COMMAND_BUTTON_CLICKED, [this](auto evt) { MainFrame::OnHitKey(evt, "/"); });
    openBracket->Bind(wxEVT_COMMAND_BUTTON_CLICKED, [this](auto evt) { MainFrame::OnHitKey(evt, "("); });
    closeBracket->Bind(wxEVT_COMMAND_BUTTON_CLICKED, [this](auto evt) { MainFrame::OnHitKey(evt, ")"); });
    power->Bind(wxEVT_COMMAND_BUTTON_CLICKED, [this](auto evt) { MainFrame::OnHitKey(evt, "^"); });
    multiply->Bind(wxEVT_COMMAND_BUTTON_CLICKED, [this](auto evt) { MainFrame::OnHitKey(evt, "*"); });

    // Bind Function Keys
    del->Bind(wxEVT_COMMAND_BUTTON_CLICKED, &MainFrame::OnDelete, this);
    execute->Bind(wxEVT_COMMAND_BUTTON_CLICKED, &MainFrame::OnExecute, this);
    panel->Bind(wxEVT_CHAR_HOOK, &MainFrame::OnHitKeyboard, this);


    // Input
    input = new wxTextCtrl(panel, wxID_ANY, "", wxPoint(sides, sides), wxSize(displayWidth, displayHeight));


    // Status Bar
	auto* statusBar = CreateStatusBar();
	statusBar->SetDoubleBuffered(true);

}

void MainFrame::OnHitKey(wxCommandEvent &evt, const wxString& key) {
    expression.append(key);
    input->Clear();
    input->WriteText(expression);
    wxLogStatus(expression);
}

void MainFrame::OnExecute(wxCommandEvent &evt) {
    MathParser mp;
    auto answer = mp.eval_exp(wxStrdup(expression.c_str()));
    if (isfinite(answer)) {
        expression = "";
        input->Clear();
        input->WriteText(to_string(answer));
    }
}

void MainFrame::OnDelete(wxCommandEvent &evt) {
    expression.RemoveLast();
    input->Clear();
    input->WriteText(expression);
    wxLogStatus(expression);
}

void MainFrame::OnHitKeyboard(wxKeyEvent &evt) {
    if (evt.GetKeyCode() == WXK_NUMPAD_ENTER || evt.GetKeyCode() == WXK_RETURN) {
        expression = input->GetValue();
        wxLogStatus(expression);
        MathParser mp;
        auto answer = mp.eval_exp(wxStrdup(expression.c_str()));
        if (isfinite(answer)) {
            expression = "";
            input->Clear();
            input->WriteText(to_string(answer));
        }
    } else if (evt.GetKeyCode() == WXK_DELETE) {
        expression = "";
        wxLogStatus("");
        input->Clear();
    }
    evt.Skip();
}






