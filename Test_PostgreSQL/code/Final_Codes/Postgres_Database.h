#ifndef POSTGRES_DATABASE_H
#define POSTGRES_DATABASE_H

#include <bits/stdc++.h>
#include <iostream>
#include <pqxx/pqxx> 
#include <string>
#include "json.hpp"
#include "VFAT_Data_Table.h"
#include "VFAT_Index_Table.h"
#include "VFAT_Config_Table.h"

using namespace std;
using namespace pqxx;
using json = nlohmann::json;

class Postgres_Database
{
    private:
       
    public:
        vector<VFAT_Index_Table> vfat_indexes;
        vector<VFAT_Config_Table> vfat_configs;

        result query_response(connection *C,string table_name,string query);
        vector<VFAT_Index_Table> Index_json_to_vec();
        vector<VFAT_Config_Table> Config_json_to_vec();
        vector<VFAT_Data_Table> VFAT_json_to_vec(string filename);
        vector<VFAT_Data_Table> GET_DATA_FROM_REFCONFIG(connection *C,long reference_config_id);

};

#endif