#ifndef VFAT_CONFIG_TABLE_H
#define VFAT_CONFIG_TABLE_H

#include "info.h"
#include <iostream>
#include <pqxx/pqxx>
#include <string>

//------------

//using namespace std;
//using namespace pqxx;

/// Class to store the Configuration Table for a particular component
/// This table is used to store the configuration IDs scanned in the JSON.
/// Table Schema: <config table name> (bigint config_id)
/// The class variables indicate the columns of the table.

class vfat_config_table {
public:
    /// Create the configuration table
    void create_table(pqxx::connection* db_client);

    /// Initialize the class objects
    void initialize(long config_id);

    /// Insert a row into the Table
    void insert_row(pqxx::connection* db_client);

    /// Insert data from the class objects into the Table
    void insert_data(pqxx::connection* db_client, std::vector<vfat_config_table> data);

    // void display_results(std::vector<VFAT_Data_Table> &data);

    /// Converts a Query Response into std::vector of class objects
    std::vector<vfat_config_table> row_to_object(pqxx::result R);

private:
    /// Field value of the table
    long config_id;
};

#endif