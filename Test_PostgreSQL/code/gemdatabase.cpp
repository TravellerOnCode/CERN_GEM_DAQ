//-----------
#include <iostream>
#include <pqxx/pqxx> 


//------------

using namespace std;
using namespace pqxx;


string DBNAME = "sample";
string USER = "postgres";
string PASSWORD = "linuxos16";

//--------------

class component_name
{
    public:

        //to be used with original database
        //long cernid;
        //int settings[128];

        int ID,SALARY,AGE;
        string NAME,ADDRESS;
    
    component_name(int id,int salary,int age,string name,string address)
    {
        ID = id;
        SALARY = salary;
        AGE = age;
        NAME = name;
        ADDRESS = address;
    }


    void display_row()
    {
        cout << "ID: " << ID << endl;
        cout << "NAME: " << NAME << endl;
        cout << "AGE: " << AGE << endl;
        cout << "SALARY: " << SALARY << endl;
        cout << "ADDRESS: " << ADDRESS << endl;
    }

    component_name row_to_object()
    {





    }
};

class postgre_database  // : public component_name //-- hiding the imheritange for the moment
{
    public:

    void insert_datanew(connection *C, string table_name)
    {
        work WW(*C);
        string sql1 = "INSERT INTO COMPANY(ID,NAME,AGE,ADDRESS,SALARY) VALUES (4, 'Avijit 1',21,'kolkata',33000) RETURNING *;";
        string sql2 = "INSERT INTO COMPANY(ID,NAME,AGE,ADDRESS,SALARY) VALUES (5, 'Avijit 2',21,'kolkata',35000) RETURNING *;";
        string sql3 = "INSERT INTO COMPANY(ID,NAME,AGE,ADDRESS,SALARY) VALUES (6, 'Avijit 3',21,'delhi',40000) RETURNING *;";
                        
        WW.exec(sql1);
        WW.exec(sql2);
        WW.exec(sql3);
             
        WW.commit();
        cout << "Values inserted !" << endl;
    }

    void display_datanew(connection *C,string table_name)
    {
            work WW(*C);
            string query = "SELECT * FROM " + table_name +";";

             result r = WW.exec(query);
             for (auto const &row: r)
                {
                      for (auto const &field: row) std::cout << field.c_str() << '\t';
                       std::cout << std::endl;
                }

                // convert each row to an object of component_name class 

              cout << "Table displayed successfully" << endl;
    }
};

int main()
{
    try
        {
            connection C("dbname = " + DBNAME + " user = "+ USER +" password = "+ PASSWORD +" \
                hostaddr = 127.0.0.1 port = 5432");
            if (C.is_open()) {
                   cout << "Opened database successfully: " << C.dbname() << endl;
             } 
             else {
                     cout << "Can't open database" << endl;
                     return 1;
              }

              postgre_database ob;
              //ob.insert_datanew(&C,"COMPANY");
              ob.display_datanew(&C,"COMPANY");


              C.disconnect ();
        }
        catch(const std::exception& e)
        {
            cerr << e.what() << std::endl;
        }

    
    return 0;
}