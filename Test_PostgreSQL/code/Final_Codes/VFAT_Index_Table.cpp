#include "VFAT_Index_Table.h"

void VFAT_Index_Table:: create_table(connection *C,string table_name)
{
        work WW(*C);
        string query = "CREATE TABLE " + table_name + "( CONFIG_ID bigint, VFAT_ID bigint,";
         string s1 = "PRIMARY KEY(CONFIG_ID,VFAT_ID),";
         string s2 = "FOREIGN KEY (CONFIG_ID) REFERENCES VFAT_CONFIG_TABLE(CONFIG_ID),";
         string s3 = "FOREIGN KEY (VFAT_ID) REFERENCES VFAT_DATA_TABLE(VFAT_ID));";
        query = query + s1 + s2 + s3;
        //cout << "Executed Query : " << endl << query << endl;
        WW.exec(query);
        cout << "Table Created -> " << table_name << endl;
        WW.commit();
}

void VFAT_Index_Table::initialize(long config_id,long vfat_id)
{
    this->config_id = config_id;
    this->vfat_id = vfat_id;
}

void VFAT_Index_Table:: insert_row(connection *C, string table_name)
{       
        work WW(*C);
        string field_values = "",arrays = "'{";
        string sql = "INSERT INTO "+table_name+" VALUES(" + to_string(this->config_id)+", "+to_string(this->vfat_id)+");";
        WW.exec(sql);
        WW.commit();
}

void VFAT_Index_Table:: insert_data(connection *C, vector<VFAT_Index_Table> data)
{
    int i;
    for (i=0;i<data.size();i++)
    {
        data[i].insert_row(&(*C),"VFAT_INDEX_TABLE");
    }
    cout << "Values inserted into table : VFAT_INDEX_TABLE" << endl;
}

vector<VFAT_Index_Table> VFAT_Index_Table:: row_to_object(result R)
{
    vector<VFAT_Index_Table> query_results;

        for (auto const &row: R)
        {
            VFAT_Index_Table obj;

            //Actual VFAT Columns
            obj.config_id = row["CONFIG_ID"].as<long>();
            obj.vfat_id = row["VFAT_ID"].as<long>();
            //obj.display_row();
            query_results.push_back(obj);
        }
        //display_results(query_results);
        return query_results;
}