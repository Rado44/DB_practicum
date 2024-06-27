#include "Table.h"
#pragma warning(disable:4996)

Table::Table(const MyString& name, size_t colsCount, const Vector<MyString>& columnNames,
	const Vector<MyString>& columnTypes): name(name), colsCount(colsCount), columnNames(columnNames), columnTypes(columnTypes){}

Table::Table(const MyString& name) :name(name) {}
const Vector<Row>& Table::getRows() const
{
	return rows;
}
const Vector<MyString>& Table::getColumnNames() const
{
	return columnNames;
}
const Vector<MyString>& Table::getColumnTypes() const
{
	return columnTypes;
}
const MyString& Table::getName() const
{
	return name;
}
size_t Table::getColsCount() const
{
	return colsCount;
}
size_t Table::getRowsCount() const
{
	return rowsCount;
}

void Table::addRow(const Vector<MyString>& colsNamesUser, const Vector<MyString>& cellsValuesUser)
{
	size_t colsCountUser = colsNamesUser.getSize();
	Vector<MyString> row;

	for (size_t i = 0; i < colsCount; i++)
	{
		row.pushBack(Constants::NULLID);
	}

	for (size_t i = 0; i < colsCountUser; i++)
	{
		int index = getColumnIndex(colsNamesUser[i]);
		row.pushAt(cellsValuesUser[index], index);
		
	}

	Row newRow(row, colsCount);
	rows.pushBack(newRow);
	rowsCount++;
}

void Table::deleteRow(size_t rowIndex)
{
	rows.popAt(rowIndex);
	rowsCount--;
}

void Table::updateRowField(size_t rowIndex, size_t colIndex, const MyString& newData)
{
	rows[rowIndex].setValue(colIndex, newData);
}

void Table::addColumnAt(const MyString& columnName,const MyString& columnType, size_t index)
{
	if (colsCount == index)
	{
		columnNames.pushBack(columnName);
		columnTypes.pushBack(columnType);
	}
	else
	{
		columnNames.pushAt(columnName, index);
		columnTypes.pushAt(columnType, index);
	}

	for (size_t i = 0; i < rowsCount; i++)
	{
		rows[i].addColumnAt(Constants::NULLID, index);
		size_t ColsCount = rows[i].getColsCount();

		rows[i].setColsCount(ColsCount++);
	}

	colsCount++;
}

void Table::deleteColumnAt(size_t index)
{
	columnNames.popAt(index);
	columnTypes.popAt(index);

	for (size_t i = 0; i < rowsCount; i++)
	{
		rows[i].removeColumnAt(index);
		size_t ColsCount = rows[i].getColsCount();

		rows[i].setColsCount(ColsCount--);
	}

	colsCount--;
}

void Table::serialize()
{
	std::ofstream ofs((name + Constants::EXTENSION).c_str());
	if (!ofs.is_open()) {
		throw std::logic_error("Could not open file!");
	}

	initTableFile(ofs);

	for (int i = 0; i < rowsCount; i++)
	{
		rows[i].serialize(ofs);
		if (i != rowsCount - 1)
		{
			ofs << std::endl;
		}
	}

	ofs.close();
}

void Table::deserialize()
{
	std::ifstream ifs((name+Constants::EXTENSION).c_str());
	if (!ifs.is_open()) {
		throw std::logic_error("Could not open file!");
	}

	char rowStr[Constants::BUFFER_SIZE];

	//columnTypes

	ifs.getline(rowStr, Constants::BUFFER_SIZE, '\n');	
	std::stringstream ss1(rowStr);

	while (!ss1.eof())
	{
		char currColumnValue[Constants::BUFFER_SIZE];
		ss1.getline(currColumnValue, Constants::BUFFER_SIZE, Constants::SEP);
		columnTypes.pushBack(currColumnValue);
		colsCount++;
	}

	//columnNames

	ifs.getline(rowStr, Constants::BUFFER_SIZE, '\n');
	std::stringstream ss2(rowStr);

	for (size_t i = 0; i < colsCount; i++)
	{
		char currColumnValue[Constants::BUFFER_SIZE];
		ss2.getline(currColumnValue, Constants::BUFFER_SIZE, Constants::SEP);
		columnNames.pushBack(currColumnValue);
	}

	//rows

	while (!ifs.eof())
	{
		ifs.getline(rowStr, Constants::BUFFER_SIZE, '\n');

		Row empty;
		empty.setColsCount(colsCount);
		rows.pushBack(empty);
		
		rows[rowsCount++].deserialize(rowStr, colsCount);
	}
}

void Table::print() const
{
	if (rowsCount == 0)
	{
		std::cout << "Empty set" << std::endl;
		return;
	}
	for (size_t i = 0; i < colsCount; i++)
	{
		std::cout << columnTypes[i] << ' ';

		if (i != colsCount - 1)
		{
			std::cout << Constants::SEP;
		}
		else
		{
			std::cout << std::endl;
		}
	}

	for (size_t i = 0; i < colsCount; i++)
	{
		std::cout << columnNames[i] << ' ';

		if (i != colsCount - 1)
		{
			std::cout << Constants::SEP;
		}
		else
		{
			std::cout << std::endl;
		}
	}

	for (size_t i = 0; i < rowsCount; i++)
	{
		rows[i].print();
	}
}

void Table::initTableFile(std::ostream& os)
{
	for (size_t i = 0; i < colsCount; i++)
	{
		os << columnTypes[i];
		if (i != colsCount - 1)
		{
			os << Constants::SEP;
		}
	}

	os << std::endl;

	for (size_t i = 0; i < colsCount; i++)
	{
		os << columnNames[i];
		if (i != colsCount - 1)
		{
			os << Constants::SEP;
		}
	}

	os << std::endl;
}

bool Table::isCondtionMet(const MyString& cellValue, 
	const MyString& conditionValue, const MyString& comparisonOperator) const
{
	if (comparisonOperator == "==") {
		return cellValue == conditionValue;
	}
	else if (comparisonOperator == "!=") {
		return cellValue != conditionValue;
	}
	else if (comparisonOperator == ">") {
		return cellValue > conditionValue;
	}
	else if (comparisonOperator == "<") {
		return cellValue < conditionValue;
	}
	else if (comparisonOperator == ">=") {
		return cellValue >= conditionValue;
	}
	else if (comparisonOperator == "<=") {
		return cellValue <= conditionValue;
	}
}

const Vector<Pair<int, int>>& Table::searchForValueByColumnAndPredicate(const MyString& columnName, 
	const MyString& conditionValue, const MyString& comparisonOperator) const
{
	Vector<Pair<int, int>> indicesPairs;

	int columnIndex = getColumnIndex(columnName);
	for (size_t i = 0; i < rowsCount; i++)
	{
		if (isCondtionMet(rows[i].getValueByColumnIndex(columnIndex), conditionValue, comparisonOperator)) {
			Pair<int, int> indicesPair(i, columnIndex);
			indicesPairs.pushBack(indicesPair);
		}
	}

	return indicesPairs;
}

void Table::updateColumns(const Vector<MyString> columns, Vector<Vector<MyString>> values)
{
	for (size_t i = 0; i < columns.getSize(); i++)
	{
		if (isContainingColumn(columns[i]))
		{
			for (size_t j = 0; j < values[i].getSize(); j++)
			{
				rows[j].setValue(i, values[i][j]);
			}
		}
	}
}

void Table::renameColumn(const MyString oldName, const MyString newName)
{
	if (isContainingColumn(oldName))
	{
		columnNames[getColumnIndex(oldName)] = newName;
	}
}

void Table::setAllColumnsTo(const MyString column, const MyString value)
{
	if (isContainingColumn(column))
	{
		size_t columnIndex = getColumnIndex(column);
		for (size_t i = 0; i < rowsCount; i++)
		{
			rows[i].setValue(columnIndex, value);
		}
	}
}

void Table::printAtColumn(const MyString column) const
{
	if (isContainingColumn(column))
	{
		size_t columnIndex = getColumnIndex(column);
		for (size_t i = 0; i < rowsCount; i++)
		{
			std::cout<<rows[i].getColumns()[columnIndex]<<std::endl;
		}
	}
}

int Table::getColumnIndex(const MyString& colName) const
{
	if (colsCount < 1) {
		throw std::logic_error("No such column");
	}

	for (int i = 0; i < colsCount; i++)
	{
		if (!strcmp(columnNames[i].c_str(), colName.c_str()))
		{
			return i;
		}
	}
}

bool Table::isContainingColumn(const MyString& colName) const
{
	if (colsCount < 1) {
		throw std::logic_error("No such column");
	}
	for (int i = 0; i < colsCount; i++)
	{
		if (strcmp(columnNames[i].c_str(), colName.c_str()) == 0)
			return true;
	}
	return false;
}
