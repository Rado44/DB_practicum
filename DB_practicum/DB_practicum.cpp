#include "Database.h"
#include <iostream>
int main()
{
	char com[] = "create table test_table (field1 int, field2 real)";
	char com1[] = "insert into test_table (field1, field2) values (1, 1.0), (2, 2.0)";
	char command[Constants::BUFFER_SIZE];
	std::cin.getline(command, Constants::BUFFER_SIZE, '\n');
	std::stringstream ss(command);
	
	Database db("DB");
	db.executeQuery(com);
	db.executeQuery(com1);
	db.getTables()[0].print();

	std::cout << std::endl;

	db.executeQuery(command);

	db.getTables()[0].print();

	/*std::cout<<db.getTablesCount();
	db.getTables()[0].print();*/

	//MyString rowValue1 = "a";
	//MyString rowValue2 = "b";
	//MyString rowValue3 = "c";

	//Vector<MyString> row1;
	//row1.pushBack(rowValue1);
	//row1.pushBack(rowValue2);
	//row1.pushBack(rowValue3);

	//MyString rowValue11 = "d";
	//MyString rowValue22 = "e";
	//MyString rowValue33 = "f";

	//Vector<MyString> row2;
	//row2.pushBack(rowValue11);
	//row2.pushBack(rowValue22);
	//row2.pushBack(rowValue33);

	//Row rone(row1, 3);
	//Row rtwo(row2, 3);

	/////cols

	//MyString tableName = "test_Table";///
	//size_t colsCount = 3;///


	//MyString colName1 = "one";
	//MyString colName2 = "two";
	//MyString colName3 = "three";
	//Vector<MyString> colNames;////
	//colNames.pushBack(colName1);
	//colNames.pushBack(colName2);
	//colNames.pushBack(colName3);
	//
	//MyString colType1 = "int";
	//MyString colType2 = "real";
	//MyString colType3 = "text";
	//Vector<MyString> colTypes;////
	//colTypes.pushBack(colType1);
	//colTypes.pushBack(colType2);
	//colTypes.pushBack(colType3);

	//Table table(tableName, colsCount, colNames, colTypes);
	//table.addRow(colNames, row1);
	//table.addRow(colNames, row2);


	//Vector<MyString> colNames1;////
	//colNames1.pushBack(colName1);
	////colNames1.pushBack(colName2);
	//colNames1.pushBack(colName3);
	//table.addRow(colNames1, row2);

	//table.print();
}

