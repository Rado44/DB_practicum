#pragma once
#include "MyString.h"
class SQLResponse
{
private:
	MyString message = "";
	size_t rowsAffected = 0;
	bool isOK = 1;

public:
	SQLResponse() = default;
	SQLResponse(size_t rowsAff, bool isOK);
	void print() const;
};

