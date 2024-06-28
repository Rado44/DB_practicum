#include "Database.h"
#include <iostream>
int main()
{
	///*char com[] = "create table test_table (field1 int, field2 real)";
	//char com1[] = "insert into test_table (field1, field2) values (1, 1.0), (2, 2.0)";
	//char com2[] = "select * from test_table";*/
	//char command[Constants::BUFFER_SIZE];
	//std::cin.getline(command, Constants::BUFFER_SIZE, '\n');
	//std::stringstream ss(command);
	//
	//Database db("DB");
	///*db.executeQuery(com);
	//db.executeQuery(com1);
	//db.executeQuery(com2);*/
	//db.getTables()[0].print();

	//std::cout << std::endl;

	//db.executeQuery(command);

	//db.getTables()[0].print();

	///*Table deserialised("test_table");
	//deserialised.deserialize();
	//db.addTable(deserialised);

	//std::cout << std::endl;
	//db.getTables()[1].print();*/

	Database db("DB");
	while (true)
	{
		char command[Constants::BUFFER_SIZE];
		std::cin.getline(command, Constants::BUFFER_SIZE, '\n');
		std::stringstream ss(command);

		if (!std::strcmp(command, "exit"))
		{
			std::cout << db.getPath() << " closed" << std::endl;
			break;
		}

		db.executeQuery(command);
	}

}

