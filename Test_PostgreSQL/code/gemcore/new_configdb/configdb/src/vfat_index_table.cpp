/// Include the Header File
#include "../interface/vfat_index_table.h"

void vfat_index_table::create_table(pqxx::connection* db_client)
{
    pqxx::work WW(*db_client);

    /// Structure the PostgreSQL Statement to create a table
    std::string query = std::string("CREATE TABLE IF NOT EXISTS ") + VFAT_INDEX_TABLE + "( CONFIG_ID bigint, ID bigint,";
    std::string s1 = "PRIMARY KEY(CONFIG_ID,ID),";
    std::string s2 = std::string("FOREIGN KEY (CONFIG_ID) REFERENCES ") + VFAT_CONFIG_TABLE + "(CONFIG_ID),";
    std::string s3 = std::string("FOREIGN KEY (ID) REFERENCES ") + VFAT_DATA_TABLE + "(ID));";
    query = query + s1 + s2 + s3;
    // std::cout << "Executed Query : " << endl << query << endl;
    /// Execute the PostgreSQL Statement and create the table
    WW.exec(query);
    std::cout << std::string("Table Created -> ") << VFAT_CONFIG_TABLE << std::endl;
    /// Commit Work to the database
    WW.commit();
}

void vfat_index_table::initialize(long config_id, long id)
{
    /// Initialize the class variables
    this->config_id = config_id;
    this->id = id;
}

long vfat_index_table::get_id()
{
    /// Function to access the id field.
    return this->id;
}

void vfat_index_table::insert_row(pqxx::connection* db_client)
{
    pqxx::work WW(*db_client);
    /// Structure the PostgreSQL Statement to insert data
    std::string field_values = "", arrays = "'{";
    std::string sql = std::string("INSERT INTO ") + VFAT_INDEX_TABLE + " VALUES(" + std::to_string(this->config_id) + ", " + std::to_string(this->id) + ");";

    /// Execute the PostgreSQL Statement and insert data into the table
    WW.exec(sql);
    /// Commit Work to the database
    WW.commit();
}

void vfat_index_table::insert_data(pqxx::connection* db_client,
    std::vector<vfat_index_table> data)
{
    /// Insert extracted data, Iterate the Object std::vector
    for (auto rowObject = data.begin(); rowObject != data.end(); ++rowObject) {
        /// Insert data of a particular object
        (*rowObject).insert_row(&(*db_client));
    }
    std::cout << "Values inserted into table : " << VFAT_INDEX_TABLE << std::endl;
}

std::vector<vfat_index_table> vfat_index_table::row_to_object(pqxx::result R)
{
    std::vector<vfat_index_table> query_results;

    for (auto const& row : R) {
        vfat_index_table obj;

        // Actual VFAT Columns
        obj.config_id = row["CONFIG_ID"].as<long>();
        obj.id = row["ID"].as<long>();
        // obj.display_row();
        query_results.push_back(obj);
    }
    // display_results(query_results);
    return query_results;
}