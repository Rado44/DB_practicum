#include "Row.h"

Row::Row(const Vector<MyString>& columns, size_t colsCount) :columns(columns), colsCount(colsCount){}

Vector<MyString> Row::getColumns() const
{
    return columns;
}

size_t Row::getColsCount() const
{
    return colsCount;
}

void Row::setColumns(const Vector<MyString>& columns)
{
    this->columns = columns;
}

void Row::setColsCount(size_t colsCount)
{
    this->colsCount = colsCount;
}

const MyString& Row::getValueByColumnIndex(size_t columnIndex) const
{
    return columns[columnIndex];
}

void Row::setValue(size_t columnIndex, const MyString& value)
{
    columns[columnIndex] = value;
}

void Row::addColumn(const MyString& column)
{
    columns.pushBack(column);
    colsCount++;
}

void Row::addColumnAt(const MyString& column, size_t index)
{
    columns.pushAt(column, index);
    colsCount++;
}

void Row::deleteColumn()
{
    columns[colsCount - 1] = Constants::NULLID;
}

void Row::deleteColumnAt(size_t index)
{
    columns[index] = Constants::NULLID;
}

void Row::removeColumn()
{
    columns.popBack();
    colsCount--;
}

void Row::removeColumnAt(size_t index)
{
    columns.popAt(index);
    colsCount--;
}

void Row::serialize(std::ostream& os)
{
    for (int i = 0; i < colsCount; i++)
    {
       // std::cout << columns[i];
        os << columns[i];
        if (i != colsCount - 1)
        {
            os << Constants::SEP;
        }
    }
    
}

void Row::deserialize(const char* rowFromFile, size_t colsCount)
{
    std::stringstream ss(rowFromFile);

    size_t currentColumnCount = 0;
    for (size_t i = 0; i < colsCount; i++)
    {
        char currColumnValue[Constants::BUFFER_SIZE];
        ss.getline(currColumnValue, Constants::BUFFER_SIZE, Constants::SEP);
        columns.pushBack(currColumnValue);
    }
}

void Row::print() const
{
    for (int i = 0; i < colsCount; i++)
    {
        std::cout << columns[i] << ' ';
        if (i != colsCount - 1)
        {
            std::cout << Constants::SEP;
        }
        else
        {
            std::cout << std::endl;
        }
    }
}
