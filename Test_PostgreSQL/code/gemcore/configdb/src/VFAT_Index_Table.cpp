/// Include the Header File
#include "../interface/VFAT_Index_Table.h"

void VFAT_Index_Table:: create_table(connection *dbClient)
{
    work WW(*dbClient);

    /// Structure the PostgreSQL Statement to create a table
    string query = "CREATE TABLE IF NOT EXISTS " + to_string(VFAT_INDEX_TABLE) + "( CONFIG_ID bigint, ID bigint,";
    string s1 = "PRIMARY KEY(CONFIG_ID,ID),";
    string s2 = "FOREIGN KEY (CONFIG_ID) REFERENCES "+to_string(VFAT_CONFIG_TABLE)+"(CONFIG_ID),";
    string s3 = "FOREIGN KEY (ID) REFERENCES "+to_string(VFAT_DATA_TABLE)+"(ID));";
    query = query + s1 + s2 + s3;
    //cout << "Executed Query : " << endl << query << endl;
    /// Execute the PostgreSQL Statement and create the table
    WW.exec(query);
    cout << "Table Created -> " << to_string(VFAT_CONFIG_TABLE) << endl;
    /// Commit Work to the database
    WW.commit();
}

void VFAT_Index_Table::initialize(long config_id,long id)
{
    /// Initialize the class variables
    this->config_id = config_id;
    this->id = id;
}

long VFAT_Index_Table:: get_id()
{
    /// Function to access the id field.
    return this->id;
}

void VFAT_Index_Table:: insert_row(connection *dbClient)
{       
    work WW(*dbClient);
    /// Structure the PostgreSQL Statement to insert data
    string field_values = "",arrays = "'{";
    string sql = "INSERT INTO " + to_string(VFAT_INDEX_TABLE) +" VALUES(" + to_string(this->config_id)+", "+to_string(this->id)+");";
    
    /// Execute the PostgreSQL Statement and insert data into the table
    WW.exec(sql);
    /// Commit Work to the database
    WW.commit();
}

void VFAT_Index_Table:: insert_data(connection *dbClient, vector<VFAT_Index_Table> data)
{
    int i;
    /// Insert extracted data, Iterate the Object vector
    for (i=0;i<data.size();i++)
    {
        /// Insert data of a particular object
        data[i].insert_row(&(*dbClient));
    }
    cout << "Values inserted into table : "<< VFAT_INDEX_TABLE << endl;
}

vector<VFAT_Index_Table> VFAT_Index_Table:: row_to_object(result R)
{
    vector<VFAT_Index_Table> query_results;

    for (auto const &row: R)
    {
        VFAT_Index_Table obj;

        //Actual VFAT Columns
        obj.config_id = row["CONFIG_ID"].as<long>();
        obj.id = row["ID"].as<long>();
        //obj.display_row();
        query_results.push_back(obj);
    }
    //display_results(query_results);
    return query_results;
}