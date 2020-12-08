#include "VFAT_Config_Table.h"
#include "VFAT_Data_Table.h"
#include "VFAT_Index_Table.h"
#include "Postgres_Database.h"

string DBNAME = "gemdatabase";
string USER = "postgres";
string PASSWORD = "linuxos16";


int main(int argc, char** argv)
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
                
              Postgres_Database ob;
              Postgres_Database ob2;
              result r;
              //ob.insert_datanew(&C,"COMPANY");
              //r = ob.query_response(&C,"COMPANY");

              VFAT_Config_Table obj1;
              VFAT_Data_Table obj2;
              VFAT_Index_Table obj3;

              
              vector<VFAT_Config_Table> configurations;
              vector<VFAT_Data_Table> vfat_data;
              vector<VFAT_Index_Table> indexes;

              vector<VFAT_Config_Table> configurations2;
              vector<VFAT_Data_Table> vfat_data2;
              vector<VFAT_Index_Table> indexes2;

              /*
              //creating tables
              obj1.create_table(&C,"VFAT_CONFIG_TABLE");
              obj2.create_table(&C,"VFAT_DATA_TABLE");
              obj3.create_table(&C,"VFAT_INDEX_TABLE");

              string filename1 = argv[1];
              string filename2 = argv[2];
              vector<VFAT_Data_Table> file_obs;

		      vfat_data = ob.VFAT_json_to_vec(filename1);
              configurations = ob.Config_json_to_vec();
              indexes = ob.Index_json_to_vec();

              vfat_data2 = ob2.VFAT_json_to_vec(filename2);
              configurations2 = ob2.Config_json_to_vec();
              indexes2 = ob2.Index_json_to_vec();

            
              cout << "All JSON converted to object Vectors" << endl;
		      
            
              //Data Insertion (in this particular order data -> config -> index)
              obj1.insert_data(&C,configurations);
              obj2.insert_data(&C,vfat_data);
              obj3.insert_data(&C,indexes);

              cout << "JSON 1 DATA INSERTED ! " << endl;

              obj1.insert_data(&C,configurations2);
              obj2.insert_data(&C,vfat_data2);
              obj3.insert_data(&C,indexes2);

              cout << "JSON 2 DATA INSERTED ! " << endl;
              */


              //obj.create_table(&C,"VFAT_COMPONENT");
              r = ob.query_response(&C,"VFAT_DATA_TABLE");
              //RETURNS A VECTOR OF OBJECTS
              vfat_data = obj2.row_to_object(r);
              obj2.display_results(vfat_data);
            
              C.disconnect ();
        }
        catch(const std::exception& e)
        {
            cerr << e.what() << std::endl;
        }

    return 0;
}
