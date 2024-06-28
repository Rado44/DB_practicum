#pragma once
#include "Table.h"
#include "SQLResponse.h"
class Database
{
private:
	Vector<Table> tables;
	MyString dbPath;
	Database() = default;

public:
	Database(const MyString& dbPath);

	Database(const Database&) = delete;
	Database& operator=(const Database&) = delete;

	static Database& getInstance();

	size_t getTablesCount() const;

	const Vector<Table> getTables() const;

	const MyString getPath() const;

	void addTable(Table& ref);

private:
	//Utilities
	MyString inputConvert(MyString& str);
	void inputVectorInsertion(Vector<MyString>& vector, std::stringstream& ss);
	//

	bool isContainingTable(Table& ref) const;

	bool isContainingTable(const MyString& name) const;

	int getTableIndex(const MyString& name) const;

	SQLResponse& createTable(std::stringstream& ss, MyString& command);

	SQLResponse& showTables() const;

	SQLResponse& selectTable(std::stringstream& ss) const;

	SQLResponse& insertIntoTable(std::stringstream& ss);

	SQLResponse& alterTableAdd(std::stringstream& ss, const MyString& tableName);

	SQLResponse& alterTableDrop(std::stringstream& ss, const MyString& tableName);

	SQLResponse& alterTableRename(std::stringstream& ss, const MyString& tableName);

	//SQLResponse& updateTable(std::stringstream& ss);

public:
	SQLResponse& executeQuery(char* query);


};

