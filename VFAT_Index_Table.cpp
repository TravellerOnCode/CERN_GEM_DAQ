#include "VFAT_Index_Table.h"

void VFAT_Index_Table:: create_table(connection *C,string table_name)
{
        work WW(*C);
        string query = "CREATE TABLE " + table_name + "( CONFIG_ID bigint, ID bigint,";
         string s1 = "PRIMARY KEY(CONFIG_ID,ID),";
         string s2 = "FOREIGN KEY (CONFIG_ID) REFERENCES "+to_string(VFAT_CONFIG_TABLE)+"(CONFIG_ID),";
         string s3 = "FOREIGN KEY (ID) REFERENCES "+to_string(VFAT_DATA_TABLE)+"(ID));";
        query = query + s1 + s2 + s3;
        //cout << "Executed Query : " << endl << query << endl;
        WW.exec(query);
        cout << "Table Created -> " << table_name << endl;
        WW.commit();
}

void VFAT_Index_Table::initialize(long config_id,long id)
{
    this->config_id = config_id;
    this->id = id;
}

long VFAT_Index_Table:: get_id()
{
    return this->id;
}

void VFAT_Index_Table:: insert_row(connection *C, string table_name)
{       
        work WW(*C);
        string field_values = "",arrays = "'{";
        string sql = "INSERT INTO "+table_name+" VALUES(" + to_string(this->config_id)+", "+to_string(this->id)+");";
        WW.exec(sql);
        WW.commit();
}

void VFAT_Index_Table:: insert_data(connection *C, vector<VFAT_Index_Table> data)
{
    int i;
    for (i=0;i<data.size();i++)
    {
        data[i].insert_row(&(*C),VFAT_INDEX_TABLE);
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