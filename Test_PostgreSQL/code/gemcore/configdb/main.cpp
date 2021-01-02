#include "./interface/Postgres_Database.h"
#include "./interface/VFAT_Config_Table.h"
#include "./interface/VFAT_Data_Table.h"
#include "./interface/VFAT_Index_Table.h"
#include "./interface/info.h"

int main(int argc, char **argv) {
  try {

    // connect to the database
    connection dbClient("dbname = " + to_string(DBNAME) + "\
                            user = " +
                        USER + "\
                            password = " +
                        PASSWORD + " \
                            hostaddr = " +
                        IP + "\
                            port = " +
                        PORT);

    if (dbClient.is_open())
      cout << "Opened database successfully: " << dbClient.dbname() << endl;
    else {
      cout << "Can't open database" << endl;
      return 1;
    }

    //---------------------------------------------------------------------------

    // DECLARING NECESSARY OBJECTS AND VECTORS
    Postgres_Database ob;
    result r;

    VFAT_Config_Table obj1;
    VFAT_Data_Table obj2;
    VFAT_Index_Table obj3;

    vector<VFAT_Config_Table> configurations;
    vector<VFAT_Data_Table> vfat_data;     // Store data from current JSON
    vector<VFAT_Data_Table> vfat_data_ref; // Store data from reference JSON
    vector<VFAT_Index_Table> indexes;

    //---------------------------------------------------------------------------

    // creating tables
    obj1.create_table(&dbClient);
    obj2.create_table(&dbClient);
    obj3.create_table(&dbClient);

    //---------------------------------------------------------------------------

    string filepath = argv[1]; // Read Input JSON File
    // string config_id = filename1.substr(3,filename1.length()-4);
    string config_id = ob.extract_configid(filepath);

    //---------------------------------------------------------------------------

    vfat_data = ob.getVFATSettings(filepath);
    configurations = ob.getConfigIDs();
    // indexes = ob.Index_json_to_vec();

    cout << "All JSON converted to object Vectors" << endl;

    //---------------------------------------------------------------------------

    if (argc > 2) {
      long reference_config = stoi(argv[2]); // Read Reference JSON Name
      vfat_data_ref = ob.getReferenceVFATSettings(
          &dbClient, reference_config); // Getting Data stored in Reference JSON
      // obj2.display_results(vfat_data_ref); //Displaying the results
      obj1.insert_data(&dbClient, configurations);
      vfat_data = obj2.getNewSettings(&dbClient, vfat_data, vfat_data_ref,
                                      stoi(config_id));
      obj2.insert_data(&dbClient, vfat_data, stoi(config_id));
    } else {
      // Data Insertion (in this particular order data -> config -> index)
      obj1.insert_data(&dbClient, configurations);
      obj2.insert_data(&dbClient, vfat_data, stoi(config_id));
      //*****obj3.insert_data(&C,indexes);
    }

    //---------------------------------------------------------------------------

    // cout << "JSON 1 DATA INSERTED ! " << endl;

    //---------------------------------------------------------------------------

    // PLACED HERE FOR TESTING PURPOSE
    // vfat_data_ref = ob.GET_DATA_FROM_REFCONFIG(&C,reference_config);
    // //Getting Data stored in Reference JSON
    // obj2.display_results(vfat_data_ref); //Displaying the results

    //---------------------------------------------------------------------------

    string query = "select * from " + to_string(VFAT_DATA_TABLE) +
                   ";"; // + " where vfat_id = 1000";
    r = ob.query_response(&dbClient, query);
    // RETURNS A VECTOR OF OBJECTS
    vfat_data = obj2.row_to_object(r);
    obj2.display_results(vfat_data);

    dbClient.disconnect();
  } catch (const std::exception &e) {
    cerr << e.what() << std::endl;
  }

  return 0;
}
