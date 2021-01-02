#pragma once

#include "VFAT_Index_Table.h"
#include "info.h"
#include <bits/stdc++.h>
#include <iomanip>
#include <iostream>
#include <pqxx/pqxx>
#include <sstream>
#include <string>

using namespace std;
using namespace pqxx;

/// Class to store the Data for a particular component. This stores the settings
/// of a particular VFAT.
/// This table is used to store the settings scanned in the JSON.
/// Table Schema: <data table name> (bigint id, bigint config_id, ............ )
/// The class variables indicate the columns of the table.

class VFAT_Data_Table {

public:
  /// Create the data table
  void create_table(connection *dbClient);

  /// Access the id
  long get_id();

  /// Initialize the class objects
  void initialize(long VFAT_ID, unordered_map<string, long> field_val,
                  vector<long> array_val);

  /// Insert a row into the Table
  long insert_row(connection *dbClient);

  /// Insert data from the class objects into the Table
  void insert_data(connection *dbClient, vector<VFAT_Data_Table> data,
                   long config_id);

  /// Converts a Query Response into vector of class objects
  vector<VFAT_Data_Table> row_to_object(result R);

  /// Get the Reference Configuration ID
  /// Check into the database and store new settings into a vector as objects.
  /// Insert a reference of the already present settings into the Index Table.
  vector<VFAT_Data_Table> getNewSettings(connection *dbClient,
                                         vector<VFAT_Data_Table> vfat_ob,
                                         vector<VFAT_Data_Table> ref_ob,
                                         long config_id);

  /// Compare two VFAT settings.
  int compareSettings(const VFAT_Data_Table &ob1, const VFAT_Data_Table &ob2);

  /// To display the results
  void display_row();
  void display_results(vector<VFAT_Data_Table> &data);

private:
  /// ID
  long id;

  /// Component ID
  long VFAT_ID;

  // Actual VFAT Columns
  long CFG_IREF;
  long CFG_HYST;

  long CFG_BIAS_CFD_DAC_2;
  long CFG_BIAS_CFD_DAC_1;
  long CFG_BIAS_PRE_I_BSF;

  long CFG_BIAS_PRE_I_BIT;
  long CFG_BIAS_PRE_I_BLCC;
  long CFG_BIAS_PRE_VREF;
  long CFG_BIAS_SH_I_BFCAS;
  long CFG_BIAS_SH_I_BDIFF;
  long CFG_BIAS_SH_I_BFAMP;
  long CFG_BIAS_SD_I_BDIFF;
  long CFG_BIAS_SD_I_BSF;
  long CFG_BIAS_SD_I_BFCAS;

  //## DAC monitor
  long CFG_VREF_ADC;
  long CFG_MON_GAIN;
  long CFG_MONITOR_SELECT;

  //## Input
  //# Preamp gain - high
  long CFG_RES_PRE;
  long CFG_CAP_PRE;
  //# Preamp gain - medium
  // long CFG_RES_PRE;
  // long CFG_CAP_PRE;
  //# Preamp gain - low
  // long CFG_RES_PRE;
  // long CFG_CAP_PRE;

  //# Timing constants - long
  long CFG_FP_FE;
  long CFG_PT;

  //# Use negative polarity (errata VFAT3 manual)
  long CFG_SEL_POL;

  //# Provide a slight offset to the ZCC comparator baseline voltage
  long CFG_THR_ZCC_DAC;

  //# "Main" threshold
  long CFG_THR_ARM_DAC;

  //# Comparator mode - CFD
  long CFG_SEL_COMP_MODE;
  long CFG_FORCE_EN_ZCC;
  //# Comparator mode - arming
  // long CFG_SEL_COMP_MODE;
  // long CFG_FORCE_EN_ZCC;
  //# Comparator mode - ZCC
  // long CFG_SEL_COMP_MODE;
  // long CFG_FORCE_EN_ZCC;

  //# Enable arming comparator hysteresis
  long CFG_EN_HYST;

  //# Disable debug ZCC comparator
  long CFG_FORCE_TH;

  //# Synchronize input on edge
  long CFG_SYNC_LEVEL_MODE;

  //# Pulse length of 4
  long CFG_PULSE_STRETCH;

  //## Trigger
  //# Disable self-triggering
  long CFG_SELF_TRIGGER_MODE;
  //# Output Sbits at 320MHz
  long CFG_DDR_TRIGGER_MODE;

  //## Data format
  //# Disable zero suppression
  long CFG_SPZS_SUMMARY_ONLY;
  long CFG_SPZS_MAX_PARTITIONS;
  long CFG_SPZS_ENABLE;
  long CFG_SZP_ENABLE;
  long CFG_SZD_ENABLE;
  //# Default time tags
  long CFG_TIME_TAG;
  long CFG_EC_BYTES;
  long CFG_BC_BYTES;

  //## Latency
  //# Default latency for Scurves
  long CFG_LATENCY; // 57

  //## Calibration pulses
  //# Ensure the calibration module is off
  long CFG_CAL_MODE;

  //# Negative polarity
  long CFG_CAL_SEL_POL;

  //# Pulse amplitude
  long CFG_CAL_DAC;

  long CFG_CAL_EXT;
  long CFG_CAL_PHI;
  long CFG_CAL_FS;
  long CFG_CAL_DUR; // 511

  //# Zeroing out all 127 channels
  std::vector<int> VFAT_CHANNELS_CHANNEL_0_to_128;

  string vfat_columns[48] = {"CFG_IREF",
                             "CFG_HYST",
                             "CFG_BIAS_CFD_DAC_2",
                             "CFG_BIAS_CFD_DAC_1",
                             "CFG_BIAS_PRE_I_BSF",

                             "CFG_BIAS_PRE_I_BIT",
                             "CFG_BIAS_PRE_I_BLCC",
                             "CFG_BIAS_PRE_VREF",
                             "CFG_BIAS_SH_I_BFCAS",
                             "CFG_BIAS_SH_I_BDIFF",
                             "CFG_BIAS_SH_I_BFAMP",
                             "CFG_BIAS_SD_I_BDIFF",
                             "CFG_BIAS_SD_I_BSF",
                             "CFG_BIAS_SD_I_BFCAS",
                             "CFG_VREF_ADC",
                             "CFG_MON_GAIN",
                             "CFG_MONITOR_SELECT",
                             "CFG_RES_PRE",
                             "CFG_CAP_PRE",
                             "CFG_FP_FE",
                             "CFG_PT",
                             "CFG_SEL_POL",
                             "CFG_THR_ZCC_DAC",
                             "CFG_THR_ARM_DAC",
                             "CFG_SEL_COMP_MODE",
                             "CFG_FORCE_EN_ZCC",
                             "CFG_EN_HYST",
                             "CFG_FORCE_TH",
                             "CFG_SYNC_LEVEL_MODE",
                             "CFG_PULSE_STRETCH",
                             "CFG_SELF_TRIGGER_MODE",
                             "CFG_DDR_TRIGGER_MODE",
                             "CFG_SPZS_SUMMARY_ONLY",
                             "CFG_SPZS_MAX_PARTITIONS",
                             "CFG_SPZS_ENABLE",
                             "CFG_SZP_ENABLE",
                             "CFG_SZD_ENABLE",
                             "CFG_TIME_TAG",
                             "CFG_EC_BYTES",
                             "CFG_BC_BYTES",
                             "CFG_LATENCY",
                             "CFG_CAL_MODE",
                             "CFG_CAL_SEL_POL",
                             "CFG_CAL_DAC",
                             "CFG_CAL_EXT",
                             "CFG_CAL_PHI",
                             "CFG_CAL_FS",
                             "CFG_CAL_DUR"};
};