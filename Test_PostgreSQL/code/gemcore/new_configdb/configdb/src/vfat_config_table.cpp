/// Include the Header File
#include "../interface/vfat_config_table.h"

void vfat_config_table::create_table(pqxx::connection* db_client)
{
    pqxx::work WW(*db_client);

    /// Structure the PostgreSQL Statement to create a table
    std::string query = std::string("CREATE TABLE IF NOT EXISTS ") + VFAT_CONFIG_TABLE + "( CONFIG_ID bigint PRIMARY KEY);";
    // std::cout << "Executed Query : " << std::endl << query << std::endl;
    /// Execute the PostgreSQL Statement and create the table
    WW.exec(query);
    std::cout << "Table Created -> " << VFAT_CONFIG_TABLE << std::endl;
    /// Commit pqxx::Work to the database
    WW.commit();
}

void vfat_config_table::initialize(long config_id)
{
    /// Initialize the class variables
    this->config_id = config_id;
}

void vfat_config_table::insert_row(pqxx::connection* db_client)
{
    pqxx::work WW(*db_client);
    /// Structure the PostgreSQL Statement to insert data
    std::string field_values = "", arrays = "'{";
    std::string sql = std::string("INSERT INTO ") + VFAT_CONFIG_TABLE + " VALUES(" + std::to_string(this->config_id) + ");";

    /// Execute the PostgreSQL Statement and insert data into the table
    WW.exec(sql);
    /// Commit pqxx::Work to the database
    WW.commit();
}

void vfat_config_table::insert_data(pqxx::connection* db_client,
    std::vector<vfat_config_table> data)
{
    /// Insert extracted data, Iterate the Object std::vector
    for (auto rowObject = data.begin(); rowObject != data.end(); ++rowObject) {
        /// Insert data of a particular object
        (*rowObject).insert_row(&(*db_client));
    }
    std::cout << "Values inserted into table : " << VFAT_CONFIG_TABLE << std::endl;
}

std::vector<vfat_config_table> vfat_config_table::row_to_object(pqxx::result R)
{
    std::vector<vfat_config_table> query_results;

    for (auto const& row : R) {
        vfat_config_table obj;

        // Actual VFAT Columns
        obj.config_id = row["CONFIG_ID"].as<long>();
        // obj.display_row();
        query_results.push_back(obj);
    }
    // display_results(query_results);
    return query_results;
}