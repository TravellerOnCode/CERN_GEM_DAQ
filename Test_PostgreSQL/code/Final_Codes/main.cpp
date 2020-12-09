#include "VFAT_Config_Table.h"
#include "VFAT_Data_Table.h"
#include "VFAT_Index_Table.h"
#include "Postgres_Database.h"

string DBNAME = "gemdatabase2";
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

              //---------------------------------------------------------------------------
                
              // DECLARING NECESSARY OBJECTS AND VECTORS 
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

              //---------------------------------------------------------------------------

              //creating tables
              //obj1.create_table(&C,"VFAT_CONFIG_TABLE");
              //obj2.create_table(&C,"VFAT_DATA_TABLE");
              ///obj3.create_table(&C,"VFAT_INDEX_TABLE");

              //---------------------------------------------------------------------------

              string filename1 = argv[1]; //Read Input JSON File
              //string filename2 = argv[2];
              long reference_config = stoi(argv[2]); //Read Reference JSON Name
              string config_id = filename1.substr(0,filename1.length()-4);

              //---------------------------------------------------------------------------

		      vfat_data = ob.VFAT_json_to_vec(filename1);
              configurations = ob.Config_json_to_vec();
              indexes = ob.Index_json_to_vec();


              vfat_data = ob.GET_DATA_FROM_REFCONFIG(&C,reference_config); //Getting Data stored in Reference JSON
              obj2.display_results(vfat_data); //Displaying the results
            
              cout << "All JSON converted to object Vectors" << endl;
		      
              //---------------------------------------------------------------------------

              //Data Insertion (in this particular order data -> config -> index)
              //obj1.insert_data(&C,configurations);
              //obj2.insert_data(&C,vfat_data,stoi(config_id));
              //*****obj3.insert_data(&C,indexes);

              //cout << "JSON 1 DATA INSERTED ! " << endl;

              //---------------------------------------------------------------------------

              //---------------------------------------------------------------------------

              string query = "select * from vfat_data_table where vfat_id = 9000";
              //obj.create_table(&C,"VFAT_COMPONENT");
              r = ob.query_response(&C,"VFAT_DATA_TABLE",query);
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
