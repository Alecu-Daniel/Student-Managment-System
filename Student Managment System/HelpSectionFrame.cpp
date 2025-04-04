#include "HelpSectionFrame.h"

HelpSectionFrame::HelpSectionFrame(const wxString& title) : wxFrame(nullptr, wxID_ANY, title)
{
	CreateControls();
	SetupSizers();
	BindEventHandlers();
}

void HelpSectionFrame::CreateControls()
{
	panel = new wxPanel(this);
	
	scrollWindow = new wxScrolledWindow(panel);

	questionsAndAnswers.push_back({
		new wxStaticText(scrollWindow, wxID_ANY, "How can I save my work?"),
		new wxStaticText(scrollWindow, wxID_ANY, "You can save your work by clicking the Save button, specifying a name for your table, and choosing a destination where it will be saved.")
		});

	questionsAndAnswers.push_back({
		new wxStaticText(scrollWindow, wxID_ANY, "How can I load my work?"),
		new wxStaticText(scrollWindow, wxID_ANY, "You can load your saved work by clicking the Load button and selecting the file you want to open.")
		});

	questionsAndAnswers.push_back({
		new wxStaticText(scrollWindow, wxID_ANY, "How can I add a row?"),
		new wxStaticText(scrollWindow, wxID_ANY, "You can add a row by clicking the Add Row button at the bottom of the screen. This will add exactly one row.")
		});

	questionsAndAnswers.push_back({
		new wxStaticText(scrollWindow, wxID_ANY, "Can I add multiple rows at once?"),
		new wxStaticText(scrollWindow, wxID_ANY, "Yes. By entering a number in the input field next to the Add Row button, you can specify how many rows you want to add.")
		});

	questionsAndAnswers.push_back({
		new wxStaticText(scrollWindow, wxID_ANY, "What happens if I enter invalid input when adding rows?"),
		new wxStaticText(scrollWindow, wxID_ANY, "If the input is not a positive number, the input field will be cleared and you will be asked to enter a valid number.")
		});

	questionsAndAnswers.push_back({
		new wxStaticText(scrollWindow, wxID_ANY, "How can I add a column?"),
		new wxStaticText(scrollWindow, wxID_ANY, "You can add a column by clicking the Add Column button at the bottom of the screen. This will add exactly one column. You can also give a name to the new column by filling in the input field to the right.")
		});

	questionsAndAnswers.push_back({
		new wxStaticText(scrollWindow, wxID_ANY, "How can I delete a row/column?"),
		new wxStaticText(scrollWindow, wxID_ANY, "You can delete a row or column by selecting it with a left-click, then clicking the Delete button at the bottom of the screen. You can also delete multiple rows or columns by selecting more than one at a time.")
		});

	questionsAndAnswers.push_back({
		new wxStaticText(scrollWindow, wxID_ANY, "Can I edit a column's name?"),
		new wxStaticText(scrollWindow, wxID_ANY, "Yes. You can rename a column by double-clicking its name. A box will appear where you can type in the new name.")
		});


	
}

void HelpSectionFrame::SetupSizers()
{
	wxBoxSizer* mainSizer = new wxBoxSizer(wxVERTICAL);
	
	wxBoxSizer* scrollSizer = new wxBoxSizer(wxVERTICAL);
	scrollSizer->AddSpacer(25);

	wxFont questionFont(wxFontInfo(wxSize(0, 18)).Bold());
	wxFont answerFont(wxFontInfo(wxSize(0, 14)));

	for (const auto& entry : questionsAndAnswers)
	{

		wxStaticText* question = entry.first;
		wxStaticText* answer = entry.second;

		question->SetFont(questionFont);
		answer->SetFont(answerFont);

		question->Wrap(1000);
		answer->Wrap(1000);

		scrollSizer->Add(question);
		scrollSizer->AddSpacer(5);
		scrollSizer->Add(answer);
		scrollSizer->AddSpacer(25);
	}

	scrollWindow->SetSizer(scrollSizer);
	scrollWindow->SetScrollRate(5, 5);

	mainSizer->Add(scrollWindow, 1, wxEXPAND | wxLEFT, 20);

	panel->SetSizer(mainSizer);
	mainSizer->SetSizeHints(this);
}

void HelpSectionFrame::BindEventHandlers()
{
}