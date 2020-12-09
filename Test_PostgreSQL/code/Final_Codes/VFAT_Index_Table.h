#ifndef VFAT_INDEX_TABLE_H
#define VFAT_INDEX_TABLE_H

#include <iostream>
#include <pqxx/pqxx> 
#include <string>
//#include "json.hpp"

//------------

using namespace std;
using namespace pqxx;

class VFAT_Index_Table
{
    private:
        long config_id;
        long id;
    public:
        long get_id();
        void create_table(connection *C,string table_name);
        void initialize(long config_id,long id);
        void insert_row(connection *C, string table_name);
        void insert_data(connection *C, vector<VFAT_Index_Table> data);
        //void display_results(vector<VFAT_Data_Table> &data);
        vector<VFAT_Index_Table> row_to_object(result R);

};

#endif