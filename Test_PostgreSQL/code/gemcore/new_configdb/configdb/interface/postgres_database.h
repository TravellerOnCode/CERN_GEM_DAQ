#ifndef POSTGRES_DATABASE_H
#define POSTGRES_DATABASE_H

/// Header File inclusion
#include "info.h"
#include "vfat_config_table.h"
#include "vfat_data_table.h"
//#include "vfat_index_table.h"
//#include <bits/stdc++.h>
//#include <iostream>
#include "json.hpp"
#include <pqxx/pqxx>
//#include <string>
//#include <vector>

class postgres_database {
public:
    /// Accepts a Query as std::String and returns the response
    pqxx::result query_response(pqxx::connection* db_client, const std::string& query);

    /// Extracts the configuration ID from a filepath
    std::string extract_configid(const std::string& filepath);

    /// TODO : to be checked later
    /// std::vector<vfat_index_table> Index_json_to_vec();

    /// Returns the Configuration IDs from the JSON
    std::vector<vfat_config_table> getConfigIDs();

    /// Returns the VFAT Settings found in JSON
    std::vector<vfat_data_table> getVFATSettings(const std::string& filename);

    /// Returns the VFAT Settings found at Reference Configuration ID
    std::vector<vfat_data_table> getReferenceVFATSettings(pqxx::connection* db_client,
        long reference_config_id);

private:
    /// std::vector<vfat_index_table> vfat_indexes;
    /// std::Vector to store Configuration ID
    std::vector<vfat_config_table> vfat_configs;
};

#endif