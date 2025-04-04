#pragma once
#include <wx/wx.h>
#include <vector>

class HelpSectionFrame : public wxFrame
{
public:
	HelpSectionFrame(const wxString& title);
private:

	void CreateControls();
	void SetupSizers();
	void BindEventHandlers();


	wxPanel* panel;
	
	wxScrolledWindow* scrollWindow;

	std::vector<std::pair<wxStaticText*, wxStaticText*>> questionsAndAnswers;

};

