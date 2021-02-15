/// Include the Header File
#include "../interface/vfat_configurations.h"

vfat_configurations::vfat_configurations(const long config_id)
{
    this->config_id = config_id;
}

void vfat_configurations::create_table(pqxx::connection* db_client)
{
    pqxx::work WW(*db_client);

    /// Structure the PostgreSQL Statement to create a table
    std::string query = std::string("CREATE TABLE IF NOT EXISTS ") + "CONFIGURATION_TABLE" + "( CONFIG_ID bigint PRIMARY KEY);";
    // std::cout << "Executed Query : " << std::endl << query << std::endl;
    /// Execute the PostgreSQL Statement and create the table
    WW.exec(query);
    std::cout << "Table Created -> " << "CONFIGURATION_TABLE" << std::endl;
    /// Commit pqxx::Work to the database
    WW.commit();
}

/*void vfat_configurations::initialize(long config_id)
{
    /// Initialize the class variables
    this->config_id = config_id;
}*/

void vfat_configurations::insert_row(pqxx::connection* db_client)
{
    pqxx::work WW(*db_client);
    /// Structure the PostgreSQL Statement to insert data
    std::string field_values = "", arrays = "'{";
    std::string sql = std::string("INSERT INTO ") + "CONFIGURATION_TABLE" + " VALUES(" + std::to_string(this->config_id) + ");";

    /// Execute the PostgreSQL Statement and insert data into the table
    WW.exec(sql);
    /// Commit pqxx::Work to the database
    WW.commit();
}

void vfat_configurations::insert_data(pqxx::connection* db_client,
    std::vector<vfat_configurations> data)
{
    /// Insert extracted data, Iterate the Object std::vector
    for (auto row_object = data.begin(); row_object != data.end(); ++row_object) {
        /// Insert data of a particular object
        (*row_object).insert_row(&(*db_client));
    }
    std::cout << "Values inserted into table : " << "CONFIGURATION_TABLE" << std::endl;
}

std::vector<vfat_configurations> vfat_configurations::row_to_object(pqxx::result R)
{
    std::vector<vfat_configurations> query_results;

    for (auto const& row : R) {
        vfat_configurations obj;

        // Actual VFAT Columns
        obj.config_id = row["CONFIG_ID"].as<long>();
        // obj.display_row();
        query_results.push_back(obj);
    }
    // display_results(query_results);
    return query_results;
}
