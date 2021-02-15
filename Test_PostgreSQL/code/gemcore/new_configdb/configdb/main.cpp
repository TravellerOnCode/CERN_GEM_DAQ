#include "./interface/database_utils.h"
#include "./interface/vfat_configurations.h"
#include "./interface/vfat_settings.h"
#include "./interface/vfat_indexes.h"

int main(int argc, char** argv)
{
    try {
	
	    ///database info

	    string DBNAME = "gemdatabase";
	    string USER = "postgres";
	    string PASSWORD = "linuxos16";
	    string IP = "127.0.0.1";
	    string PORT = "5432";

        /// connect to the database
        pqxx::connection db_client(std::string("dbname = ") + DBNAME + "\
                            user = "
            + USER + "\
                            password = "
            + PASSWORD + " \
                            hostaddr = "
            + IP + "\
                            port = "
            + PORT);

        if (db_client.is_open())
            std::cout << "Opened database successfully: " << db_client.dbname() << std::endl;
        else {
            std::cout << "Can't open database" << std::endl;
            return 1;
        }

        //---------------------------------------------------------------------------

        // DECLARING NECESSARY OBJECTS AND std::VECTORS
        database_utils ob;
        pqxx::result r;

        vfat_configurations obj1;
        vfat_settings obj2;
        vfat_indexes obj3;

        std::vector<vfat_configurations> configurations;
        std::vector<vfat_settings> vfat_data; // Store data from current JSON
        std::vector<vfat_settings> vfat_data_ref; // Store data from reference JSON
        std::vector<vfat_indexes> indexes;

        //---------------------------------------------------------------------------

        // creating tables
        obj1.create_table(&db_client);
        obj2.create_table(&db_client);
        obj3.create_table(&db_client);

        //---------------------------------------------------------------------------

        std::string filepath = argv[1]; // Read Input JSON File
        // std::string config_id = filename1.substr(3,filename1.length()-4);
        std::string config_id = ob.extract_configid(filepath);

        //---------------------------------------------------------------------------

        vfat_data = ob.get_VFAT_settings(filepath);
        configurations = ob.get_config_ids();
        // indexes = ob.Index_json_to_vec();

        std::cout << "All JSON converted to object std::Vectors" << std::endl;

        //---------------------------------------------------------------------------

        if (argc > 2) {
            long reference_config = std::stoi(argv[2]); // Read Reference JSON Name
            vfat_data_ref = ob.get_reference_VFAT_settings(
                &db_client, reference_config); // Getting Data stored in Reference JSON
            // obj2.display_results(vfat_data_ref); //Displaying the results
            obj1.insert_data(&db_client, configurations);
            vfat_data = obj2.get_new_settings(&db_client, vfat_data, vfat_data_ref,
                stoi(config_id));
            obj2.insert_data(&db_client, vfat_data, stoi(config_id));
        } else {
            // Data Insertion (in this particular order data -> config -> index)
            obj1.insert_data(&db_client, configurations);
            obj2.insert_data(&db_client, vfat_data, stoi(config_id));
            //*****obj3.insert_data(&C,indexes);
        }

        //---------------------------------------------------------------------------

        // std::cout << "JSON 1 DATA INSERTED ! " << std::endl;

        //---------------------------------------------------------------------------

        // PLACED HERE FOR TESTING PURPOSE
        // vfat_data_ref = ob.GET_DATA_FROM_REFCONFIG(&C,reference_config);
        // //Getting Data stored in Reference JSON
        // obj2.display_results(vfat_data_ref); //Displaying the results

        //---------------------------------------------------------------------------

        std::string query = std::string("select * from ") + "SETTINGS_TABLE" + ";"; // + " where vfat_id = 1000";
        r = ob.query_response(&db_client, query);
        // RETURNS A std::VECTOR OF OBJECTS
        vfat_data = obj2.row_to_object(r);
        obj2.display_results(vfat_data);

        // db_client.disconnect();
    } catch (const std::exception& e) {
        std::cerr << e.what() << std::endl;
    }

    return 0;
}
