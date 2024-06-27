#include "SQLResponse.h"

SQLResponse::SQLResponse(size_t rowsAff, bool isOK) : rowsAffected(rowsAff), isOK(isOK)
{
	print();
}

void SQLResponse::print() const
{
	if (isOK)
	{
		std::cout << "Query OK, " << rowsAffected << " rows Affected" << std::endl;
		return;
	}
	
	std::cout << "Query Not OK, " << rowsAffected << " rows Affected" << std::endl;
}
