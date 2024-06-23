#pragma once
#include "Table.h"

class Database
{
private:
	Vector<Table*> tables;
	MyString dbPath;
	Database() = default;

public:
	Database(const MyString& dbPath);

	Database(const Database&) = delete;
	Database& operator=(const Database&) = delete;

	static Database& getInstance(const MyString& dbPath = nullptr);

	void addTable(Table& ref);

private:
	bool isContainingTable(Table& ref) const;

};

