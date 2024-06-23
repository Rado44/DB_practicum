#include "Database.h"
#include <iostream>

int main()
{
    /*MyString a = "blqks";
    MyString b = "asdasd";
    MyString c = "pruc";

    Vector<MyString> columns;
    columns.pushBack(a);
    columns.pushBack(b);
    columns.pushBack(c);

    Row one(columns, 3);
    one.addColumnAt(a, 2);
    one.removeColumnAt(2);
    one.print();*/

    MyString tableName = "test";

    Table t(tableName);
    t.deserialize();

    

    t.print();

    std::cout << std::endl;

    /*Database base("BasePath");
    base.addTable(t);
    base.addTable(t);*/

    MyString colName1 = "field1";
    MyString colName2 = "field2";
    MyString colName3 = "field3";
    MyString colName4 = "field4";
    Vector<MyString> colsNames;
    colsNames.pushBack(colName1);
    colsNames.pushBack(colName2);

    Vector<MyString> columns;
    columns.pushBack(colName3);
    columns.pushBack(colName4);

    

    MyString colType1 = "int";
    MyString colType2 = "real";
    MyString colType3 = "text";
    MyString colType4 = "text";
    Vector<MyString> colsTypes1;
    colsTypes1.pushBack(colType1);
    colsTypes1.pushBack(colType2);

    Vector<MyString> colsTypes2;
    colsTypes2.pushBack(colType1);
    //colsTypes.pushBack(colType2);

    Vector<Vector<MyString>> values;
    values.pushBack(colsTypes1);
    values.pushBack(colsTypes2);

    t.updateColumns(columns, values);

    t.print();

   // 
   // Table table(tableName, 2, colsNames, colsTypes);
   // table.serialize();
   // 

   // MyString cell00 = "1";
   // MyString cell01 = "1.0";
   // Vector<MyString> cells;
   // cells.pushBack(cell00);
   // cells.pushBack(cell01);

   // table.addRow(colsNames, cells);
   // table.addRow(colsNames, cells);
   // table.addColumnAt(colName3, colType3, 2);
   // table.addColumnAt(colName4, colType4, 3);

   // table.serialize();

   ////table.deleteColumnAt(0);
   // table.updateRowField(0, 2, cell00);
   // 
   // table.serialize();

   // 
   //// std::cout<<table.getColumnIndex("field2");

}

