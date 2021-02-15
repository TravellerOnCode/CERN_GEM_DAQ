#ifndef VFAT_SETTINGS_H
#define VFAT_SETTINGS_H

/// #include "info.h"
#include "vfat_indexes.h"
#include <bits/stdc++.h>

/// Class to store the Data for a particular component. This stores the settings
/// of a particular VFAT.
/// This table is used to store the settings scanned in the JSON.
/// Table Schema: <data table name> (bigint id, bigint config_id, ............ )
/// The class variables indicate the columns of the table.

class vfat_settings {

public:
    /// Create the data table
    void create_table(pqxx::connection* db_client);

    /// Access the id
    long id() const { return this->m_id; }

    /// Initialize the class objects
    void initialize(long VFAT_ID, std::unordered_map<std::string, long> field_val,
    const std::array<int, 128> &array_val);
     //  const std::vector<long> &array_val);

    /// Insert a row into the Table
    long insert_row(pqxx::connection* db_client);

    /// Insert data from the class objects into the Table
    void insert_data(pqxx::connection* db_client, std::vector<vfat_settings> data,
        long config_id);

    /// Converts a Query Response into std::vector of class objects
    std::vector<vfat_settings> row_to_object(pqxx::result R);

    /// Get the Reference Configuration ID
    /// Check into the database and store new settings into a std::vector as objects.
    /// Insert a reference of the already present settings into the Index Table.
    std::vector<vfat_settings> get_new_settings(pqxx::connection* db_client,
        std::vector<vfat_settings> vfat_ob,
        std::vector<vfat_settings> ref_ob,
        long config_id);

    /// Compare two VFAT settings.
    int compare_settings(const vfat_settings& ob1, const vfat_settings& ob2);

    /// To display the results
    void display_row();
    void display_results(std::vector<vfat_settings>& data);

private:
    /// ID
    long m_id;

    /// Component ID
    long VFAT_ID;

    // Actual VFAT Columns
    long IREF;
    long HYST;

    long BIAS_CFD_DAC_2;
    long BIAS_CFD_DAC_1;
    long BIAS_PRE_I_BSF;

    long BIAS_PRE_I_BIT;
    long BIAS_PRE_I_BLCC;
    long BIAS_PRE_VREF;
    long BIAS_SH_I_BFCAS;
    long BIAS_SH_I_BDIFF;
    long BIAS_SH_I_BFAMP;
    long BIAS_SD_I_BDIFF;
    long BIAS_SD_I_BSF;
    long BIAS_SD_I_BFCAS;

    //## DAC monitor
    long VREF_ADC;
    long MON_GAIN;
    long MONITOR_SELECT;

    //## Input
    //# Preamp gain - high
    long RES_PRE;
    long CAP_PRE;
    //# Preamp gain - medium
    // long RES_PRE;
    // long CAP_PRE;
    //# Preamp gain - low
    // long RES_PRE;
    // long CAP_PRE;

    //# Timing constants - long
    long FP_FE;
    long PT;

    //# Use negative polarity (errata VFAT3 manual)
    long SEL_POL;

    //# Provide a slight offset to the ZCC comparator baseline voltage
    long THR_ZCC_DAC;

    //# "Main" threshold
    long THR_ARM_DAC;

    //# Comparator mode - CFD
    long SEL_COMP_MODE;
    long FORCE_EN_ZCC;
    //# Comparator mode - arming
    // long SEL_COMP_MODE;
    // long FORCE_EN_ZCC;
    //# Comparator mode - ZCC
    // long SEL_COMP_MODE;
    // long FORCE_EN_ZCC;

    //# Enable arming comparator hysteresis
    long EN_HYST;

    //# Disable debug ZCC comparator
    long FORCE_TH;

    //# Synchronize input on edge
    long SYNC_LEVEL_MODE;

    //# Pulse length of 4
    long PULSE_STRETCH;

    //## Trigger
    //# Disable self-triggering
    long SELF_TRIGGER_MODE;
    //# Output Sbits at 320MHz
    long DDR_TRIGGER_MODE;

    //## Data format
    //# Disable zero suppression
    long SPZS_SUMMARY_ONLY;
    long SPZS_MAX_PARTITIONS;
    long SPZS_ENABLE;
    long SZP_ENABLE;
    long SZD_ENABLE;
    //# Default time tags
    long TIME_TAG;
    long EC_BYTES;
    long BC_BYTES;

    //## Latency
    //# Default latency for Scurves
    long LATENCY; // 57

    //## Calibration pulses
    //# Ensure the calibration module is off
    long CAL_MODE;

    //# Negative polarity
    long CAL_SEL_POL;

    //# Pulse amplitude
    long CAL_DAC;

    long CAL_EXT;
    long CAL_PHI;
    long CAL_FS;
    long CAL_DUR; // 511

    //# Zeroing out all 127 channels
    //std::vector<int> VFAT_CHANNELS_CHANNEL_0_to_128;
    std::array<int, 128> VFAT_CHANNELS_CHANNEL_0_to_128;

    
};

#endif