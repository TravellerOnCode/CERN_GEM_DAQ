//-----------
#include <iostream>
#include <pqxx/pqxx> 


//------------

using namespace std;
using namespace pqxx;

#define DBNAME sameple user
#define USER postgres
#define PASSWORD linuxos16

//--------------

class component_name
{
    public:
        long cernid;
        int settings[128];

    void display_row()
    {

    }

    component_name row_to_object()
    {



    }

};

class postgre_database // : public component_name -- hiding the imheritange for the moment
{
    public:

    void insert_data(string table_name)
    {
        try
        {
            connection C("dbname = sample user = postgres password = linuxos16 \
                hostaddr = 127.0.0.1 port = 5432");
            if (C.is_open()) {
                   cout << "Opened database successfully: " << C.dbname() << endl;
             } else {
                     cout << "Can't open database" << endl;
              }
            work W(C);

             string sql1 = "INSERT INTO COMPANY(ID,NAME,AGE,ADDRESS,SALARY) VALUES (1, 'Avijit 1',21,'kolkata',33000) RETURNING *;";
             string sql2 = "INSERT INTO COMPANY(ID,NAME,AGE,ADDRESS,SALARY) VALUES (2, 'Avijit 2',21,'kolkata',35000) RETURNING *;";
             string sql3 = "INSERT INTO COMPANY(ID,NAME,AGE,ADDRESS,SALARY) VALUES (3, 'Avijit 3',21,'delhi',40000) RETURNING *;";
                        

             W.exec(sql1);
             W.exec(sql2);
             W.exec(sql3);
             
              W.commit();
              cout << "Values inserted !" << endl;
              C.disconnect ();
        }
        catch(const std::exception& e)
        {
            cerr << e.what() << std::endl;
        }
        
    }


    void display_table(string table_name)
    {
        try{

            connection C("dbname = sample user = postgres password = linuxos16 \
                hostaddr = 127.0.0.1 port = 5432");
            if (C.is_open()) {
                   cout << "Opened database successfully: " << C.dbname() << endl;
             } else {
                     cout << "Can't open database" << endl;
              }
            work W(C);

             string query = "SELECT * FROM " + table_name +";";

             result r = W.exec(query);
             for (auto const &row: r)
                {
                      for (auto const &field: row) std::cout << field.c_str() << '\t';
                       std::cout << std::endl;
                }
             //W.commit();
              cout << "Table displayed successfully" << endl;
              C.disconnect ();

        } 
        catch (const std::exception &e) {
             cerr << e.what() << std::endl;
             }

    }

};

int main()
{

    postgre_database ob;
    ob.insert_data("COMPANY");
    ob.display_table("COMPANY");
    return 0;
}