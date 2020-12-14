#pragma once

#include "info.h"
#include <iostream>
#include <pqxx/pqxx> 
#include <string>

//------------

using namespace std;
using namespace pqxx;

class VFAT_Index_Table
{
    public:
        long get_id();
        void create_table(connection *C,string table_name);
        void initialize(long config_id,long id);
        void insert_row(connection *C, string table_name);
        void insert_data(connection *C, vector<VFAT_Index_Table> data);
        //void display_results(vector<VFAT_Data_Table> &data);
        vector<VFAT_Index_Table> row_to_object(result R);

    private:
        long config_id;
        long id;
    

};