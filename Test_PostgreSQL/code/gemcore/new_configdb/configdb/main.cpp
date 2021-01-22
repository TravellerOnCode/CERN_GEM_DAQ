#include "./interface/info.h"
#include "./interface/postgres_database.h"
#include "./interface/vfat_config_table.h"
#include "./interface/vfat_data_table.h"
#include "./interface/vfat_index_table.h"

int main(int argc, char** argv)
{
    try {

        const std::string dbname = DBNAME;


        // connect to the database
        pqxx::connection dbClient(std::string("dbname = ") + DBNAME + "\
                            user = "
            + USER + "\
                            password = "
            + PASSWORD + " \
                            hostaddr = "
            + IP + "\
                            port = "
            + PORT);

        if (dbClient.is_open())
            std::cout << "Opened database successfully: " << dbClient.dbname() << std::endl;
        else {
            std::cout << "Can't open database" << std::endl;
            return 1;
        }

        //---------------------------------------------------------------------------

        // DECLARING NECESSARY OBJECTS AND std::VECTORS
        postgres_database ob;
        pqxx::result r;

        vfat_config_table obj1;
        vfat_data_table obj2;
        vfat_index_table obj3;

        std::vector<vfat_config_table> configurations;
        std::vector<vfat_data_table> vfat_data; // Store data from current JSON
        std::vector<vfat_data_table> vfat_data_ref; // Store data from reference JSON
        std::vector<vfat_index_table> indexes;

        //---------------------------------------------------------------------------

        // creating tables
        obj1.create_table(&dbClient);
        obj2.create_table(&dbClient);
        obj3.create_table(&dbClient);

        //---------------------------------------------------------------------------

        std::string filepath = argv[1]; // Read Input JSON File
        // std::string config_id = filename1.substr(3,filename1.length()-4);
        std::string config_id = ob.extract_configid(filepath);

        //---------------------------------------------------------------------------

        vfat_data = ob.getVFATSettings(filepath);
        configurations = ob.getConfigIDs();
        // indexes = ob.Index_json_to_vec();

        std::cout << "All JSON converted to object std::Vectors" << std::endl;

        //---------------------------------------------------------------------------

        if (argc > 2) {
            long reference_config = std::stoi(argv[2]); // Read Reference JSON Name
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

        // std::cout << "JSON 1 DATA INSERTED ! " << std::endl;

        //---------------------------------------------------------------------------

        // PLACED HERE FOR TESTING PURPOSE
        // vfat_data_ref = ob.GET_DATA_FROM_REFCONFIG(&C,reference_config);
        // //Getting Data stored in Reference JSON
        // obj2.display_results(vfat_data_ref); //Displaying the results

        //---------------------------------------------------------------------------

        std::string query = std::string("select * from ") + VFAT_DATA_TABLE + ";"; // + " where vfat_id = 1000";
        r = ob.query_response(&dbClient, query);
        // RETURNS A std::VECTOR OF OBJECTS
        vfat_data = obj2.row_to_object(r);
        obj2.display_results(vfat_data);

        // dbClient.disconnect();
    } catch (const std::exception& e) {
        std::cerr << e.what() << std::endl;
    }

    return 0;
}
