#pragma once
#include <wx/wx.h>
#include <wx/grid.h>

class MainFrame : public wxFrame
{
public:
	MainFrame(const wxString& title);
private:
	void CreateControls();
	void SetupSizers();
	void BindEventHandlers();

	
	void OnSaveButtonClicked(wxCommandEvent& event);
	void OnLoadButtonClicked(wxCommandEvent& event);

	void OnHelpButtonClicked(wxCommandEvent& event);

	void OnAddRowButtonClicked(wxCommandEvent& event);
	void OnRowInputEnterPress(wxCommandEvent& event);
	void OnAddColumnButtonClicked(wxCommandEvent& event);
	void OnColumnInputEnterPress(wxKeyEvent& event);

	void OnDeleteButtonClicked(wxCommandEvent& event);

	void OnCellValueChanged(wxGridEvent& event);
	void OnLabelDoubleClick(wxGridEvent& event);

	wxFrame* helpSectionFrame;

	wxPanel* panel;
	wxButton* saveButton;
	wxButton* loadButton;
	wxButton* helpButton;
	wxGrid* grid;
	wxButton* addRowButton;
	wxStaticText* rowInputFieldLabel;
	wxTextCtrl* rowInputField;
	wxButton* addColumnButton;
	wxStaticText* columnInputFieldLabel;
	wxTextCtrl* columnInputField;
	wxButton* deleteButton;
	wxStaticText* deleteLabel;
};