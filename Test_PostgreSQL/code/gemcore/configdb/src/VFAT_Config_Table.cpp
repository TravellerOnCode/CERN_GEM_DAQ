/// Include the Header File
#include "../interface/VFAT_Config_Table.h"

void VFAT_Config_Table:: create_table(connection *dbClient)
{
    work WW(*dbClient);

    /// Structure the PostgreSQL Statement to create a table
    string query = "CREATE TABLE IF NOT EXISTS " + to_string(VFAT_CONFIG_TABLE) + "( CONFIG_ID bigint PRIMARY KEY);";
    //cout << "Executed Query : " << endl << query << endl;
    /// Execute the PostgreSQL Statement and create the table
    WW.exec(query);
    cout << "Table Created -> " << to_string(VFAT_CONFIG_TABLE) << endl;
    /// Commit Work to the database
    WW.commit();
}

void VFAT_Config_Table::initialize(long config_id)
{
    /// Initialize the class variables
    this->config_id = config_id;
}

void VFAT_Config_Table:: insert_row(connection *dbClient)
{       
    work WW(*dbClient);
    /// Structure the PostgreSQL Statement to insert data
    string field_values = "",arrays = "'{";
    string sql = "INSERT INTO "+to_string(VFAT_CONFIG_TABLE)+" VALUES(" + to_string(this->config_id)+");";
    
    /// Execute the PostgreSQL Statement and insert data into the table
    WW.exec(sql);
    /// Commit Work to the database
    WW.commit();
}

void VFAT_Config_Table:: insert_data(connection *dbClient, vector<VFAT_Config_Table> data)
{
    int i;
    /// Insert extracted data, Iterate the Object vector
    for (i=0;i<data.size();i++)
    {
        /// Insert data of a particular object
        data[i].insert_row(&(*dbClient));
    }
    cout << "Values inserted into table : " << VFAT_CONFIG_TABLE << endl;
}

vector<VFAT_Config_Table> VFAT_Config_Table:: row_to_object(result R)
{
    vector<VFAT_Config_Table> query_results;

    for (auto const &row: R)
    {
        VFAT_Config_Table obj;

        //Actual VFAT Columns
        obj.config_id = row["CONFIG_ID"].as<long>();
        //obj.display_row();
        query_results.push_back(obj);
    }
    //display_results(query_results);
    return query_results;
}