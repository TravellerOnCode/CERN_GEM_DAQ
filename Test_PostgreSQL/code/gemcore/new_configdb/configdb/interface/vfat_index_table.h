#ifndef VFAT_INDEX_TABLE_H
#define VFAT_INDEX_TABLE_H

#include "info.h"
#include <iostream>
#include <pqxx/pqxx>
#include <string>

/// Class to store the Index for a particular component
/// This table is used to store the configuration IDs scanned from the JSON and
/// ID received.
/// Table Schema: <index table name> (bigint config_id, bigint id)
/// The class variables indicate the columns of the table.

class vfat_index_table {
public:
    /// Access the id
    long get_id();

    /// Create the configuration table
    void create_table(pqxx::connection* db_client);

    /// Initialize the class objects
    void initialize(long config_id, long id);

    /// Insert a row into the Table
    void insert_row(pqxx::connection* db_client);

    /// Insert data from the class objects into the Table
    void insert_data(pqxx::connection* db_client, const std::vector<vfat_index_table> data);
    // void display_results(std::vector<VFAT_Data_Table> &data);

    /// Converts a Query Response into std::vector of class objects
    std::vector<vfat_index_table> row_to_object(pqxx::result R);

private:
    /// Field Values of the Table
    long config_id;
    long id;
};

#endif