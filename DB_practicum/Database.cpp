#include "Database.h"

Database::Database(const MyString& dbPath) :dbPath(dbPath) {}

Database& Database::getInstance(const MyString& dbPath)
{
	static Database instance;
	return instance;
}

void Database::addTable(Table& ref)
{
	if (!isContainingTable(ref))
	{
		tables.pushBack(&ref);
	}
}

bool Database::isContainingTable(Table& ref) const
{
	for (size_t i = 0; i < tables.getSize(); i++)
	{
		if (tables[i] == &ref) 
		{
			return true;
		}
	}
	return false;
}

