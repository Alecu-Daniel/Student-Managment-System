#include "SaveSystem.h"
#include <string>
#include <vector>
#include <fstream>
#include <algorithm>


void SaveDataToFile(const TableData& tableData, const std::string& fileName)
{
	std::ofstream ostream(fileName);

	ostream << tableData.tableSize.rowSize << " " << tableData.tableSize.columnSize << "\n";

	for (const std::string& label : tableData.columnLabels)
	{
		std::string colLabel = label;
		std::replace(colLabel.begin(), colLabel.end(), ' ', '_');
		ostream << colLabel << "\n";
	}

	ostream << tableData.data.size() << "\n";

	for (const Data& it : tableData.data)
	{
		std::string cellValue = it.cellValue;
		wxGridCellCoords cellCoords = it.cellCoords;
		
		std::replace(cellValue.begin(), cellValue.end(), ' ', '_');

		ostream << cellValue << ' ' << cellCoords.GetRow()  << ' ' << cellCoords.GetCol() << "\n";
	}
}

TableData LoadDataFromFile(const std::string& fileName)
{
	std::ifstream istream(fileName);

	TableData tableData;

	istream >> tableData.tableSize.rowSize >> tableData.tableSize.columnSize;
	
	for (int i = 0; i < tableData.tableSize.columnSize; i++)
	{
		std::string label;
		istream >> label;
		std::replace(label.begin(), label.end(), '_', ' ');
		tableData.columnLabels.push_back(label);
	}

	int n;
	istream >> n;
	for (int i = 0; i < n; i++)
	{
		std::string cellValue;
		wxGridCellCoords cellCoords;
		int rowIndex;
		int colIndex;
		
		istream >> cellValue >> rowIndex >> colIndex;

		std::replace(cellValue.begin(), cellValue.end(), '_', ' ');
		
		cellCoords.Set(rowIndex, colIndex);

		tableData.data.push_back(Data{ cellValue,cellCoords });

	}

	return tableData;
}
