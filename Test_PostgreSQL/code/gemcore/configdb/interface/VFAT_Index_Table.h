#pragma once

#include "info.h"
#include <iostream>
#include <pqxx/pqxx> 
#include <string>

//------------

using namespace std;
using namespace pqxx;

/// Class to store the Index for a particular component
/// This table is used to store the configuration IDs scanned from the JSON and ID received. 
/// Table Schema: <index table name> (bigint config_id, bigint id)
/// The class variables indicate the columns of the table.

class VFAT_Index_Table
{
    public:
        /// Access the id
        long get_id();

        /// Create the configuration table
        void create_table(connection *dbClient);

        /// Initialize the class objects
        void initialize(long config_id,long id);

        /// Insert a row into the Table
        void insert_row(connection *dbClient);

        /// Insert data from the class objects into the Table
        void insert_data(connection *dbClient, vector<VFAT_Index_Table> data);
        //void display_results(vector<VFAT_Data_Table> &data);

        /// Converts a Query Response into vector of class objects
        vector<VFAT_Index_Table> row_to_object(result R);

    private:
        /// Field Values of the Table
        long config_id;
        long id;
    

};