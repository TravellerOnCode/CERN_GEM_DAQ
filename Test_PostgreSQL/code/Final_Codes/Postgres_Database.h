#include <iostream>
#include <pqxx/pqxx> 
#include <string>

using namespace std;
using namespace pqxx;

class postgre_database
{
    public:
        result query_response(connection *C,string table_name);

};