#pragma once
#include "MyString.h"
#include "Pair.hpp"
#include "Vector.hpp"
#include "Constants.h"
#include <fstream>
#include <sstream>

class Row
{
private:
	Vector<MyString> columns;
	size_t colsCount = 0;

public:
    Row() = default;
    Row(const Vector<MyString>& row, size_t columnsCount);

    Vector<MyString> getColumns() const;
    size_t getColsCount() const;

    void setColumns(const Vector<MyString>& columns);
    void setColsCount(size_t colsCount);

    const MyString& getValueByColumnIndex(size_t columnIndex) const;
    void setValue(size_t columnIndex, const MyString& value);

    void addColumn(const MyString& column);
    void addColumnAt(const MyString& column, size_t index);

    void deleteColumn();
    void deleteColumnAt(size_t index);

    void removeColumn();
    void removeColumnAt(size_t index);

    void serialize(std::ostream& os);
    void deserialize(const char* rowFromFile, size_t colsCount);

    void print() const;

    void print(size_t colLenght) const;
};

