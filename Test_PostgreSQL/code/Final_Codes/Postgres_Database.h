#include <iostream>
#include <pqxx/pqxx> 
#include <string>

using namespace std;
using namespace pqxx;

class Postgres_Database
{
    private:
       
    public:
        result query_response(connection *C,string table_name);

};