#pragma once

/// Header File inclusion
#include "VFAT_Config_Table.h"
#include "VFAT_Data_Table.h"
#include "VFAT_Index_Table.h"
#include "info.h"
#include "json.hpp"
#include <bits/stdc++.h>
#include <iostream>
#include <pqxx/pqxx>
#include <string>

using namespace std;
using namespace pqxx;
using json = nlohmann::json;

class Postgres_Database {
public:
  /// Accepts a Query as String and returns the response
  result query_response(connection *dbClient, string query);

  /// Extracts the configuration ID from a filepath
  string extract_configid(string filepath);

  /// TODO : to be checked later
  /// vector<VFAT_Index_Table> Index_json_to_vec();

  /// Returns the Configuration IDs from the JSON
  vector<VFAT_Config_Table> getConfigIDs();

  /// Returns the VFAT Settings found in JSON
  vector<VFAT_Data_Table> getVFATSettings(string filename);

  /// Returns the VFAT Settings found at Reference Configuration ID
  vector<VFAT_Data_Table> getReferenceVFATSettings(connection *dbClient,
                                                   long reference_config_id);

private:
  /// vector<VFAT_Index_Table> vfat_indexes;
  /// Vector to store Configuration ID
  vector<VFAT_Config_Table> vfat_configs;
};