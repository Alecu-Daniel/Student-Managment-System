#pragma once
#include <string>
#include <vector>
#include <wx/grid.h>


struct Data {
	std::string cellValue;
	wxGridCellCoords cellCoords;
};

struct TableSize {
	int rowSize;
	int columnSize;
};


struct TableData {
	TableSize tableSize;
	std::vector<std::string> columnLabels;
	std::vector<Data> data;
};



void SaveDataToFile(const TableData& tableData, const std::string& fileName);
TableData LoadDataFromFile(const std::string& fileName);
