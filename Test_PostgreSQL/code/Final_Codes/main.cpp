#include "VFAT_Config_Table.h"
#include "VFAT_Data_Table.h"
#include "VFAT_Index_Table.h"
#include "Postgres_Database.h"

string DBNAME = "gemdaq";
string USER = "postgres";
string PASSWORD = "linuxos16";

int main()
{
    try
        {
            //connect to the database
            connection C("dbname = " + DBNAME + " user = "+ USER +" password = "+ PASSWORD +" \
                hostaddr = 127.0.0.1 port = 5432");
            if (C.is_open()) {
                   cout << "Opened database successfully: " << C.dbname() << endl;
             } 
             else {
                     cout << "Can't open database" << endl;
                     return 1;
              }

              //Postgres_Database ob;
              result r;
              //ob.insert_datanew(&C,"COMPANY");
              //r = ob.query_response(&C,"COMPANY");

              VFAT_Config_Table obj1;
              VFAT_Data_Table obj2;
              VFAT_Index_Table obj3;

              vector<VFAT_Config_Table> results1;
              vector<VFAT_Data_Table> results2;
              vector<VFAT_Index_Table> results3;



              //obj.create_table(&C,"VFAT_COMPONENT");
              //r = ob.query_response(&C,"gemlong");
              //RETURNS A VECTOR OF OBJECTS
              results2 = obj2.row_to_object(r);
              //obj.display_results(results);

              C.disconnect ();
        }
        catch(const std::exception& e)
        {
            cerr << e.what() << std::endl;
        }

    return 0;
}