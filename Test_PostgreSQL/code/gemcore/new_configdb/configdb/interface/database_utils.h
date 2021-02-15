#ifndef DATABASE_UTILS_H
#define DATABASE_UTILS_H

/// Header File inclusion
#include "info.h"
#include "vfat_configurations.h"
#include "vfat_settings.h"
//#include "vfat_index_table.h"
//#include <bits/stdc++.h>
//#include <iostream>
#include "json.hpp"
#include <pqxx/pqxx>
//#include <string>
//#include <vector>

class database_utils {
public:
    /// Accepts a Query as std::String and returns the response
    pqxx::result query_response(pqxx::connection* db_client, const std::string& query);

    /// Extracts the configuration ID from a filepath
    std::string extract_configid(const std::string& filepath);

    /// TODO : to be checked later
    /// std::vector<vfat_index_table> Index_json_to_vec();

    /// Returns the Configuration IDs from the JSON
    std::vector<vfat_configurations> get_config_ids();

    /// Returns the VFAT Settings found in JSON
    std::vector<vfat_settings> get_VFAT_settings(const std::string& filename);

    /// Returns the VFAT Settings found at Reference Configuration ID
    std::vector<vfat_settings> get_reference_VFAT_settings(pqxx::connection* db_client,
        long reference_config_id);

private:
    /// std::vector<vfat_index_table> vfat_indexes;
    /// std::Vector to store Configuration ID
    std::vector<vfat_configurations> vfat_configs;
};

#endif