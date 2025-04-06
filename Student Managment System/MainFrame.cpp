#include "MainFrame.h"
#include "SaveSystem.h"

#include "HelpSectionFrame.h"

MainFrame::MainFrame(const wxString& title) : wxFrame(nullptr, wxID_ANY, title)
{
	CreateControls();
	SetupSizers();
	BindEventHandlers();
}

void MainFrame::CreateControls()
{
	panel = new wxPanel(this);

	saveButton = new wxButton(panel, wxID_ANY, "Save");
	loadButton = new wxButton(panel, wxID_ANY, "Load");

	helpButton = new wxButton(panel, wxID_ANY, "Help");

	grid = new wxGrid(panel, wxID_ANY);

	grid->CreateGrid(10,5);
	grid->EnableDragCell();

	int defaultColSize = 120;
	int defaultRowSize = 30;


	grid->SetDefaultColSize(defaultColSize, true);
	grid->SetDefaultRowSize(defaultRowSize, true);

	
	addRowButton = new wxButton(panel, wxID_ANY, "Add Row");
	rowInputFieldLabel = new wxStaticText(panel, wxID_ANY, "Enter number of rows to add:");
	rowInputField = new wxTextCtrl(panel, wxID_ANY, "", wxDefaultPosition, wxDefaultSize, wxTE_PROCESS_ENTER);

	addColumnButton = new wxButton(panel, wxID_ANY, "Add Column");
	columnInputFieldLabel = new wxStaticText(panel, wxID_ANY, "Enter a name for the new column:");
	columnInputField = new wxTextCtrl(panel, wxID_ANY);
	

	deleteButton = new wxButton(panel, wxID_ANY, "Delete");
	deleteLabel = new wxStaticText(panel, wxID_ANY, "- Select a row/column and press Delete");

}

void MainFrame::SetupSizers()
{
	wxBoxSizer* mainSizer = new wxBoxSizer(wxVERTICAL);
	mainSizer->AddSpacer(10);

	wxBoxSizer* ribbonSizer = new wxBoxSizer(wxHORIZONTAL);

	wxBoxSizer* saveSizer = new wxBoxSizer(wxHORIZONTAL);
	saveSizer->Add(saveButton);
	saveSizer->AddSpacer(25);
	saveSizer->Add(loadButton);

	ribbonSizer->Add(saveSizer);
	ribbonSizer->AddStretchSpacer();
	ribbonSizer->Add(helpButton);
	ribbonSizer->AddSpacer(20);


	mainSizer->Add(ribbonSizer, wxSizerFlags().Expand());
	mainSizer->AddSpacer(25);

	wxBoxSizer* tabelSizer = new wxBoxSizer(wxHORIZONTAL);
	tabelSizer->Add(grid, wxSizerFlags().Proportion(1));

	mainSizer->Add(tabelSizer, wxSizerFlags().Expand().Proportion(1));
	mainSizer->AddSpacer(25);

	wxBoxSizer* buttonsSizer = new wxBoxSizer(wxVERTICAL);

	wxBoxSizer* deleteSizer = new wxBoxSizer(wxHORIZONTAL);
	deleteSizer->Add(deleteButton);
	deleteSizer->AddSpacer(10);
	deleteSizer->Add(deleteLabel, wxSizerFlags().Align(wxALIGN_CENTER_VERTICAL));
	buttonsSizer->Add(deleteSizer);
	buttonsSizer->AddSpacer(10);

	wxBoxSizer* rowSizer = new wxBoxSizer(wxHORIZONTAL);

	rowSizer->Add(addRowButton);
	rowSizer->AddSpacer(10);
	rowSizer->Add(rowInputFieldLabel, wxSizerFlags().Align(wxALIGN_CENTER_VERTICAL));
	rowSizer->AddSpacer(10);
	rowSizer->Add(rowInputField);
	buttonsSizer->Add(rowSizer);
	buttonsSizer->AddSpacer(10);

	wxBoxSizer* columnSizer = new wxBoxSizer(wxHORIZONTAL);

	columnSizer->Add(addColumnButton);
	columnSizer->AddSpacer(10);
	columnSizer->Add(columnInputFieldLabel, wxSizerFlags().Align(wxALIGN_CENTER_VERTICAL));
	columnSizer->AddSpacer(10);
	columnSizer->Add(columnInputField);
	buttonsSizer->Add(columnSizer);

	mainSizer->Add(buttonsSizer);

	wxGridSizer* outerSizer = new wxGridSizer(1);

	outerSizer->Add(mainSizer, wxSizerFlags().Border(wxALL, 20).Expand());


	panel->SetSizer(outerSizer);
	outerSizer->SetSizeHints(this);
}

void MainFrame::BindEventHandlers()
{
	saveButton->Bind(wxEVT_BUTTON, &MainFrame::OnSaveButtonClicked, this);
	loadButton->Bind(wxEVT_BUTTON, &MainFrame::OnLoadButtonClicked, this);
	
	helpButton->Bind(wxEVT_BUTTON, &MainFrame::OnHelpButtonClicked, this);

	addRowButton->Bind(wxEVT_BUTTON, &MainFrame::OnAddRowButtonClicked, this);
	rowInputField->Bind(wxEVT_TEXT_ENTER, &MainFrame::OnRowInputEnterPress, this);
	addColumnButton->Bind(wxEVT_BUTTON, &MainFrame::OnAddColumnButtonClicked, this);


	deleteButton->Bind(wxEVT_BUTTON, &MainFrame::OnDeleteButtonClicked, this);

	grid->Bind(wxEVT_GRID_CELL_CHANGED, &MainFrame::OnCellValueChanged, this);
	grid->Bind(wxEVT_GRID_LABEL_LEFT_DCLICK, &MainFrame::OnLabelDoubleClick, this);
	
}


void MainFrame::OnSaveButtonClicked(wxCommandEvent& event)
{
	TableData tableData;

	tableData.tableSize.rowSize = grid->GetNumberRows();
	tableData.tableSize.columnSize = grid->GetNumberCols();

	for (int i = 0; i < tableData.tableSize.columnSize; i++)
	{
		tableData.columnLabels.push_back(grid->GetColLabelValue(i).ToStdString());
	}

	for (int i = 0; i < grid->GetNumberRows(); i++)
		for(int j = 0; j < grid->GetNumberCols(); j++)
		{
			wxString cellValue = grid->GetCellValue(wxGridCellCoords(i, j));

			if (!cellValue.IsEmpty())
			{
				Data cell;
				cell.cellCoords = wxGridCellCoords(i, j);
				cell.cellValue = cellValue;
				tableData.data.push_back(cell);
			}
		}

	wxFileDialog saveFileDialog(this, "Save File", "", "",
		"Text files (*.txt)|*.txt|All files (*.*)|*.*",
		wxFD_SAVE | wxFD_OVERWRITE_PROMPT);

	if (saveFileDialog.ShowModal() == wxID_CANCEL)
		return;  // User canceled

	std::string filePath = saveFileDialog.GetPath().ToStdString();

	SaveDataToFile(tableData, filePath);
	event.Skip();
}

void MainFrame::OnLoadButtonClicked(wxCommandEvent& event)
{
	wxFileDialog openFileDialog(this, "Open File", "", "",
		"Text files (*.txt)|*.txt|All files (*.*)|*.*",
		wxFD_OPEN | wxFD_FILE_MUST_EXIST);

	if (openFileDialog.ShowModal() == wxID_CANCEL)
		return;  // User canceled

	std::string filePath = openFileDialog.GetPath().ToStdString();

	TableData tableData = LoadDataFromFile(filePath);

	if(grid->GetNumberRows() && grid->GetNumberCols())
	{ 
		grid->DeleteRows(0, grid->GetNumberRows());
		grid->DeleteCols(0, grid->GetNumberCols());
	}
	
	for (int i = 0; i < tableData.tableSize.rowSize; i++)
	{
		grid->AppendRows();
	}

	for (int i = 0; i < tableData.tableSize.columnSize; i++)
	{
		grid->AppendCols();
	}

	for (int i = 0; i < tableData.columnLabels.size(); i++)
	{
		grid->SetColLabelValue(i, tableData.columnLabels[i]);
	}


	for (const Data& it : tableData.data)
	{
		grid->SetCellValue(it.cellCoords, it.cellValue);
	}

	int colMinWidth = 120;
	int colMaxWidth = 220;

	for (int i = 0; i < grid->GetNumberCols();i++)
	{
		grid->AutoSizeColumn(i,false);

		if (grid->GetColSize(i) < colMinWidth)
			grid->SetColSize(i, colMinWidth);
		else if (grid->GetColSize(i) > colMaxWidth)
			grid->SetColSize(i, colMaxWidth);
	}


	panel->Layout();
}

void MainFrame::OnHelpButtonClicked(wxCommandEvent& event)
{
	helpSectionFrame = new HelpSectionFrame("Help");
	
	wxSize screenSize;

	screenSize = wxGetDisplaySize();

	helpSectionFrame->SetClientSize(screenSize.GetWidth() / 1.2,screenSize.GetHeight() / 1.2);
	helpSectionFrame->Center();
	helpSectionFrame->Show();
}

void MainFrame::OnAddRowButtonClicked(wxCommandEvent& event) {

	int rowCount = grid->GetNumberRows();

	wxString input = rowInputField->GetValue();
	int rowsToAdd = 1;

	if (!input.empty())
	{
		int temp;
		if (input.ToInt(&temp) && temp > 0)
		{
			rowsToAdd = temp;
		}
		else
		{
			rowInputField->Clear();
			wxMessageBox("Enter a positive number", "Invalid Input");
			return;
		}
	}

	grid->AppendRows(rowsToAdd);
	
	panel->Layout();

}

void MainFrame::OnRowInputEnterPress(wxCommandEvent& event)
{
	
		wxCommandEvent evt(wxEVT_BUTTON, addRowButton->GetId());
		wxPostEvent(this, evt);

	event.Skip();
}

void MainFrame::OnAddColumnButtonClicked(wxCommandEvent& event)
{
	int colCount = grid->GetNumberCols();
	grid->AppendCols(1);

	int lastColIndex = grid->GetColAt(colCount);

	wxString lastColLabel = columnInputField->GetValue();

	if(!lastColLabel.empty())
		grid->SetColLabelValue(lastColIndex, lastColLabel);
	
	panel->Layout();
}

void MainFrame::OnColumnInputEnterPress(wxKeyEvent& event)
{
}

void MainFrame::OnDeleteButtonClicked(wxCommandEvent& event)
{
	wxArrayInt selectedRows = grid->GetSelectedRows(); 
	wxArrayInt selectedCols = grid->GetSelectedCols();

	if (!selectedRows.IsEmpty())
	{
		for (int i = selectedRows.GetCount() - 1; i >= 0; i--)
		{
			grid->DeleteRows(selectedRows[i]);
		}
	}
	else if (!selectedCols.IsEmpty())
	{
		for (int i = selectedCols.GetCount() - 1; i >= 0; i--)
		{
			grid->DeleteCols(selectedCols[i]);
		}
	}

	panel->Layout();
}

void MainFrame::OnCellValueChanged(wxGridEvent& event)
{
	int col = event.GetCol();
	int colMaxWidth = 220;
	int colMinWidth = 120;

	int currentWidth = grid->GetColSize(col);

	if (currentWidth > colMaxWidth) {
        grid->SetColSize(col, colMaxWidth);
    } 
    else if (currentWidth < colMinWidth) {
        grid->SetColSize(col, colMinWidth);
    }

	event.Skip();

}

void MainFrame::OnLabelDoubleClick(wxGridEvent& event)
{

	if (event.GetRow() == -1)
	{
		int col = event.GetCol();

		wxTextEntryDialog dialogBox(this, "Enter new name", "Rename Label");

		if (dialogBox.ShowModal() == wxID_OK)
		{ 
			wxString newLabel = dialogBox.GetValue();
			if (!newLabel.empty())
				grid->SetColLabelValue(col, newLabel);
		}
	}
}
