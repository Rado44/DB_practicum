#include "Database.h"

Database::Database(const MyString& dbPath) :dbPath(dbPath) {}

Database& Database::getInstance()
{
	static Database instance;
	return instance;
}

size_t Database::getTablesCount() const
{
	return tables.getSize();
}

const Vector<Table> Database::getTables() const
{
	return tables;
}

const MyString Database::getPath() const
{
	return dbPath;
}

void Database::addTable(Table& ref)
{
	if (!isContainingTable(ref))
	{
		tables.pushBack(ref);	
	}
}

MyString Database::inputConvert(MyString& data)
{
	size_t a = data.getLength();
	char* colType = new char[a];
	colType[a - 1] = '\0';

	for (size_t i = 0; i < a - 1; i++)
	{
		colType[i] = data[i];
	}

	data = colType;
	delete[] colType;

	return data;
}

void Database::inputVectorInsertion(Vector<MyString>& vector, std::stringstream& ss)
{
	MyString data;
	char text[Constants::BUFFER_SIZE];
	size_t size = 0;
	size_t count = 0;

	while (true)
	{
		text[size] = ss.get();

		if (text[size] == ',')
		{
			text[size] = '\0';
			data = text;
			size = 0;

			if (vector.getSize() == count)
			{
				vector.pushBack(data);
			}
			else
			{
				vector.pushAt(data, count);
			}
			count++;

			ss.get();
		}

		else if (text[size] == ')')
		{			
			text[size] = '\0';
			data = text;
			size = 0;

			if (vector.getSize() == count)
			{
				vector.pushBack(data);
			}
			else
			{
				vector.pushAt(data, count);
			}
			count++;

			break;
		}

		else
		{
			size++;
		}
	}
}

bool Database::isContainingTable(Table& ref) const
{
	for (size_t i = 0; i < tables.getSize(); i++)
	{
		if (&tables[i] == &ref) 
		{
			return true;
		}
	}
	return false;
}

bool Database::isContainingTable(const MyString& name) const
{
	for (size_t i = 0; i < tables.getSize(); i++)
	{
		if (tables[i].getName() == name)
		{
			return true;
		}
	}
	return false;
}

int Database::getTableIndex(const MyString& name) const
{
	for (size_t i = 0; i < tables.getSize(); i++)
	{
		if (tables[i].getName() == name)
		{
			return i;
		}
	}
	return -1;
}

SQLResponse& Database::createTable(std::stringstream& ss, MyString& command)
{
	ss >> command;

	if (command == "table")
	{
		ss >> command;

		if (ss.eof())
		{
			Table t1(command);

			addTable(t1);

			SQLResponse a(0, 1);
			return a;
		}

		char ignore;
		ss >> ignore;

		Vector<MyString> colNames;
		Vector<MyString> colTypes;
		MyString tableName = command;
		size_t colsCount = 0;

		MyString data;
		while (!ss.eof())
		{
			ss >> data;
			colNames.pushBack(data);

			ss >> data;

			data = inputConvert(data);

			colTypes.pushBack(data);

			colsCount++;
		}

		bool isOk = 1;
		try
		{
			Table t2(tableName, colsCount, colNames, colTypes);
			addTable(t2);
			tables[getTableIndex(tableName)].serialize();
		}
		catch (std::exception& e)
		{
			std::cout << e.what() << std::endl;
			isOk = 0;
		}

		SQLResponse a(0, isOk);
		return a;
	}
}

SQLResponse& Database::showTables() const
{
	size_t numberOfTables = getTablesCount();
	size_t maxLenghtName = 0;
	for (size_t i = 0; i < numberOfTables; i++)
	{
		if (tables[i].getName().getLength() > maxLenghtName) 
		{
			maxLenghtName = tables[i].getName().getLength();
		}
	}

	std::cout << '+';
	for (size_t i = 0; i < maxLenghtName + 2; i++)
	{
		std::cout << '-';
	}
	std::cout << '+' << std::endl;

	for (size_t i = 0; i < numberOfTables; i++)
	{
		std::cout << "| ";
		std::cout << tables[i].getName();
		std::cout << " |" << std::endl;

		std::cout << '+';
		for (size_t i = 0; i < maxLenghtName + 2; i++)
		{
			std::cout << '-';
		}
		std::cout << '+' << std::endl;
	}

	SQLResponse a;
	return a;
}

SQLResponse& Database::selectTable(std::stringstream& ss) const
{
	MyString data;
	char ignore;

	ss >> ignore;//*

	ss >> data;//from

	if (data == "from")
	{
		ss >> data;

		if (isContainingTable(data))
		{
			tables[getTableIndex(data)].print();
		}
	}
	SQLResponse a;
	return a;
}

SQLResponse& Database::insertIntoTable(std::stringstream& ss)
{
	try {
		if (tables.getSize() == 0)
		{
			throw std::exception("There are no tables");
		}
	}
	catch (std::exception& e)
	{
		std::cout << e.what() << std::endl;
		SQLResponse a;
		return a;
	}

	MyString data;

	char ignore;

	ss >> data;
	if (data != "into")
	{
		SQLResponse a(0,0);
		return a;
	}

	ss >> data;

	ss >> ignore;
	//
	MyString tableName = data;
	size_t numberOfColumns = 0;
	Vector<MyString> columnNames;
	Vector<MyString> values;
	//

	inputVectorInsertion(columnNames, ss);

	ss >> data;

	if (data != "values")
	{
		SQLResponse a(0, 0);
		return a;
	}

	ss >> ignore;
	
	int countOfRows = 0;
	//Column Values
	while (!ss.eof())
	{
		inputVectorInsertion(values, ss);
		size_t a = getTableIndex(tableName);

		try {
			tables[getTableIndex(tableName)].addRow(columnNames, values);
		}
		catch (std::exception& e)
		{
			std::cout << e.what() << std::endl;
			SQLResponse a;
			return a;
		}
		
		countOfRows++;

		ss >> ignore;
		if (ignore == ',')
		{
			ss >> ignore;
			values.empty();
		}
	}

	tables[getTableIndex(tableName)].serialize();
	SQLResponse a(countOfRows, 1);
	return a;
}

SQLResponse& Database::alterTableAdd(std::stringstream& ss, const MyString& tableName)
{
	MyString data;
	ss >> data;

	MyString columnName = data;

	ss >> data;

	MyString columnType = data;

	size_t tableIndex = getTableIndex(tableName);
	tables[tableIndex].addColumnAt(columnName, columnType, tables[tableIndex].getColsCount());

	tables[getTableIndex(tableName)].serialize();

	SQLResponse a(tables[tableIndex].getRowsCount(), 1);
	return a;

	//alter table test_table add field3 int
}

SQLResponse& Database::alterTableDrop(std::stringstream& ss, const MyString& tableName)
{
	MyString data;
	ss >> data;

	if (data != "column")
	{
		SQLResponse a(0, 0);
		return a;
	}

	ss >> data;
	MyString columnName = data;

	size_t tableIndex = getTableIndex(tableName);
	tables[tableIndex].deleteColumnAt(tables[tableIndex].getColumnIndex(columnName));

	tables[getTableIndex(tableName)].serialize();

	SQLResponse a(tables[tableIndex].getRowsCount(), 1);
	return a;

	//alter table test_table drop column field1
}

SQLResponse& Database::alterTableRename(std::stringstream& ss, const MyString& tableName)
{
	MyString data;
	ss >> data;

	if (data != "column")
	{
		SQLResponse a(0, 0);
		return a;
	}

	ss >> data;
	MyString columnNameOld = data;

	ss >> data;
	if (data != "to")
	{
		SQLResponse a(0, 0);
		return a;
	}

	ss >> data;
	MyString columnNameNew = data;

	size_t tableIndex = getTableIndex(tableName);
	tables[tableIndex].renameColumn(columnNameOld, columnNameNew);

	tables[getTableIndex(tableName)].serialize();

	SQLResponse a(0, 1);
	return a;
	//alter table test_table rename column field1 to field4
}

SQLResponse& Database::executeQuery(char * query)
{
	if (query == nullptr)
	{
		std::cout << std::endl;

		SQLResponse a(0, 0);
		return a;
	}

	MyString command;
	std::stringstream ss(query);
	ss >> command;

	if (command == "create")
	{
		std::cout << std::endl;
		return createTable(ss, command);
	}
	else if (command == "show")
	{
		std::cout << std::endl;
		return showTables();
	}
	else if (command == "select")
	{
		std::cout << std::endl;
		return selectTable(ss);
	}
	else if(command == "insert")
	{
		std::cout << std::endl;
		return insertIntoTable(ss);
	}
	else if (command == "alter")
	{
		MyString data;
		ss >> data;

		if (data != "table")
		{
			std::cout << std::endl;
			SQLResponse a(0, 0);
			return a;
		}

		ss >> data;
		MyString tableName = data;

		ss >> data;

		if (data == "add")
		{
			std::cout << std::endl;

			return alterTableAdd(ss, tableName);
		}
		else if (data == "drop")
		{
			std::cout << std::endl;

			return alterTableDrop(ss, tableName);
		}
		else if (data == "rename")
		{
			std::cout << std::endl;

			return alterTableRename(ss, tableName);
		}
		else
		{
			std::cout << std::endl;

			SQLResponse a(0, 0);
			return a;
		}
	}
	else
	{
		std::cout << std::endl;

		SQLResponse a(0, 0);
		return a;
	}
}

