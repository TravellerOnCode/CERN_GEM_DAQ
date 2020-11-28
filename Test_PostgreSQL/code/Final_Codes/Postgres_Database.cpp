#include "Postgres_Database.h"

//Returns the query response of a query 
result Postgres_Database ::query_response(connection *C,string table_name)
{
        work WW(*C);
        string query = "SELECT * FROM " + table_name +";";

        result r = WW.exec(query);
        for (auto const &row: r)
        {
           //cout << row["ID"].c_str() << "   " << row["NAME"].c_str();
           for (auto const &field: row) 
               cout << field.c_str() << '\t';
           cout << endl;
        }
        cout << "Table displayed successfully" << endl;
        return r;
}
