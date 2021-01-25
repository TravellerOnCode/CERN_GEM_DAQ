/// Include the Header File
#include "../interface/vfat_indexes.h"

void vfat_indexes::create_table(pqxx::connection* db_client)
{
    pqxx::work WW(*db_client);

    /// Structure the PostgreSQL Statement to create a table
    std::string query = std::string("CREATE TABLE IF NOT EXISTS ") + "INDEX_TABLE" + "( CONFIG_ID bigint, ID bigint,";
    std::string s1 = "PRIMARY KEY(CONFIG_ID,ID),";
    std::string s2 = std::string("FOREIGN KEY (CONFIG_ID) REFERENCES ") + "CONFIGURATION_TABLE" + "(CONFIG_ID),";
    std::string s3 = std::string("FOREIGN KEY (ID) REFERENCES ") + "SETTINGS_TABLE" + "(ID));";
    query = query + s1 + s2 + s3;
    // std::cout << "Executed Query : " << endl << query << endl;
    /// Execute the PostgreSQL Statement and create the table
    WW.exec(query);
    std::cout << std::string("Table Created -> ") << "CONFIGURATION_TABLE" << std::endl;
    /// Commit Work to the database
    WW.commit();
}

void vfat_indexes::initialize(long config_id, long id)
{
    /// Initialize the class variables
    this->config_id = config_id;
    this->ref_id = id;
}


void vfat_indexes::insert_row(pqxx::connection* db_client)
{
    pqxx::work WW(*db_client);
    /// Structure the PostgreSQL Statement to insert data
    std::string field_values = "", arrays = "'{";
    std::string sql = std::string("INSERT INTO ") + "INDEX_TABLE" + " VALUES(" + std::to_string(this->config_id) + ", " + std::to_string(this->ref_id) + ");";

    /// Execute the PostgreSQL Statement and insert data into the table
    WW.exec(sql);
    /// Commit Work to the database
    WW.commit();
}

void vfat_indexes::insert_data(pqxx::connection* db_client,
    std::vector<vfat_indexes> data)
{
    /// Insert extracted data, Iterate the Object std::vector
    for (auto row_object = data.begin(); row_object != data.end(); ++row_object) {
        /// Insert data of a particular object
        (*row_object).insert_row(&(*db_client));
    }
    std::cout << "Values inserted into table : " << "INDEX_TABLE" << std::endl;
}

std::vector<vfat_indexes> vfat_indexes::row_to_object(pqxx::result R)
{
    ///converts each query result row to a vfat_indexes object
    /// returns a vfat_indexes object vector
    std::vector<vfat_indexes> query_results;

    for (auto const& row : R) {
        vfat_indexes obj;

        // Actual VFAT Columns
        obj.config_id = row["CONFIG_ID"].as<long>();
        obj.ref_id = row["ID"].as<long>();
        // obj.display_row();
        query_results.push_back(obj);
    }
    // display_results(query_results);
    return query_results;
}