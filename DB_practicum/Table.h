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

	const Vector<Row>& getRows() const;
	const Vector<MyString>& getColumnNames() const;
	const Vector<MyString>& getColumnTypes() const;
	const MyString& getName() const;
	size_t getColsCount() const;
	size_t getRowsCount() const;

	/*void setName(const MyString& name);
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

	int getColumnIndex(const MyString& colName) const;
private:

	
	bool isContainingColumn(const MyString& colName) const;
	void initTableFile(std::ostream& os);

	bool isCondtionMet(const MyString& cellValue, const MyString& conditionValue,
		const MyString& comparisonOperator) const;

	const Vector<Pair<int, int>>& searchForValueByColumnAndPredicate(const MyString& columnName,
		const MyString& conditionValue, const MyString& comparisonOperator) const;

public:

	void updateColumns(const Vector<MyString> columns, Vector<Vector<MyString>> values);

	void renameColumn(const MyString oldName, const MyString newName);
	
	void setAllColumnsTo(const MyString column, const MyString value);

	void printAtColumn(const MyString column) const;
};

