#include "VFAT_Index_Table.h"

void VFAT_Index_Table:: create_table(connection *C,string table_name)
{
        work WW(*C);
        string query = "CREATE TABLE " + table_name + "( CONFIG_ID bigint, VFAT_ID bigint);";
        cout << "Executed Query : " << endl << query << endl;
        WW.exec(query);
        cout << "Table Created !" << endl;
        WW.commit();
}

void VFAT_Index_Table::initialize()
{
    this->config_id = 0;
    this->vfat_id = 0;
}

void VFAT_Index_Table:: insert_row(connection *C, string table_name)
{       
        work WW(*C);
        string field_values = "",arrays = "'{";
        string sql = "INSERT INTO "+table_name+"(" + to_string(this->config_id)+", "+to_string(this->vfat_id)+");";
        WW.exec(sql);
        WW.commit();
        cout << "Values inserted !" << endl;
}

void VFAT_Index_Table:: insert_data(connection *C, vector<VFAT_Index_Table> data)
{
    int i;
    for (i=0;i<data.size();i++)
    {
        data[i].insert_row(&(*C),"COMPANY");
    }
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