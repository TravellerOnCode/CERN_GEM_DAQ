#include "VFAT_Config_Table.h"

void VFAT_Config_Table:: create_table(connection *C,string table_name)
{
        work WW(*C);
        string query = "CREATE TABLE " + table_name + "( CONFIG_ID bigint PRIMARY KEY);";
        //cout << "Executed Query : " << endl << query << endl;
        WW.exec(query);
        cout << "Table Created -> " << table_name << endl;
        WW.commit();
}

void VFAT_Config_Table::initialize(long config_id)
{
    this->config_id = config_id;
}

void VFAT_Config_Table:: insert_row(connection *C, string table_name)
{       
        work WW(*C);
        string field_values = "",arrays = "'{";
        string sql = "INSERT INTO "+table_name+" VALUES(" + to_string(this->config_id)+");";
        WW.exec(sql);
        WW.commit();
}

void VFAT_Config_Table:: insert_data(connection *C, vector<VFAT_Config_Table> data)
{
    int i;
    for (i=0;i<data.size();i++)
    {
        data[i].insert_row(&(*C),"VFAT_CONFIG_TABLE");
    }
    cout << "Values inserted into table : VFAT_CONFIG_TABLE" << endl;
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