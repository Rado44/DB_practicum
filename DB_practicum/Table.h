#pragma once
#include "Row.h"

class Table
{
private:
	Vector<Row> rows;

	Vector<MyString> columnTypes;

	Vector<MyString> columnNames;

	MyString name;
	size_t colsCount = 0;
	size_t rowsCount = 0;

public:
	Table() = default;
	Table(const MyString& name, size_t colsCount, const Vector<MyString>& namesOfColumns, const Vector<MyString>& typesOfColumns);
	Table(const MyString& name);

	/*Vector<Row> getRows() const;
	Vector<MyString> getColumnNames() const;
	Vector<MyString> getColumnTypes() const;
	MyString getName() const;
	size_t getColsCount() const;
	size_t getRowsCount() const;

	void setName(const MyString& name);
	void setColsCount(size_t count);
	void setRowsCount(size_t count);*/

	void addRow(const Vector<MyString>& colsNames, const Vector<MyString>& cellsValues);
	void deleteRow(size_t rowIndex);
	void updateRowField(size_t rowIndex, size_t colIndex, const MyString& newData);

	void addColumnAt(const MyString& columnName, const MyString& columnType, size_t index);
	void deleteColumnAt(size_t index);

	void serialize();
	void deserialize();

	void print() const;
	

private:
	int getColumnIndex(const MyString& colName) const;
	void initTableFile(std::ostream& os);
	
};

