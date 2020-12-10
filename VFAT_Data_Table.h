#ifndef VFAT_DATA_TABLE_H
#define VFAT_DATA_TABLE_H

#include <bits/stdc++.h>
#include <iostream>
#include <pqxx/pqxx> 
#include <string>
#include <sstream>
#include <iomanip>
#include "VFAT_Index_Table.h"
#include "info.h"

using namespace std;
using namespace pqxx;

class VFAT_Data_Table
{
    private:

        long id;

        long VFAT_ID;
        //Actual VFAT Columns
        long CFG_IREF; // 32
        long CFG_HYST; // 5

        long CFG_BIAS_CFD_DAC_2;// 40
        long CFG_BIAS_CFD_DAC_1;// 40
        long CFG_BIAS_PRE_I_BSF;// 13
        
        long CFG_BIAS_PRE_I_BIT;// 150
        long CFG_BIAS_PRE_I_BLCC;// 25
        long CFG_BIAS_PRE_VREF;// 86
        long CFG_BIAS_SH_I_BFCAS;// 130
        long CFG_BIAS_SH_I_BDIFF;// 80
        long CFG_BIAS_SH_I_BFAMP;// 1
        long CFG_BIAS_SD_I_BDIFF;// 140
        long CFG_BIAS_SD_I_BSF;// 15
        long CFG_BIAS_SD_I_BFCAS;// 135

        //## DAC monitor
        long CFG_VREF_ADC;// 3
        long CFG_MON_GAIN;// 0
        long CFG_MONITOR_SELECT;// 0

        //## Input
        //# Preamp gain - high
        long CFG_RES_PRE;// 1
        long CFG_CAP_PRE;// 0
        //# Preamp gain - medium
        //long CFG_RES_PRE;// 2
        //long CFG_CAP_PRE;// 1
        //# Preamp gain - low
        //long CFG_RES_PRE;// 4
        //long CFG_CAP_PRE;// 3

        //# Timing constants - long
        long CFG_FP_FE;// 7
        long CFG_PT;// 15

        //# Use negative polarity (errata VFAT3 manual)
        long CFG_SEL_POL;// 0

        //# Provide a slight offset to the ZCC comparator baseline voltage
        long CFG_THR_ZCC_DAC;// 10

        //# "Main" threshold
        long CFG_THR_ARM_DAC;// 100

        //# Comparator mode - CFD
        long CFG_SEL_COMP_MODE;// 0
        long CFG_FORCE_EN_ZCC;// 0
        //# Comparator mode - arming
        //long CFG_SEL_COMP_MODE;// 1
        //long CFG_FORCE_EN_ZCC;// 0
        //# Comparator mode - ZCC
        //long CFG_SEL_COMP_MODE;// 2
        //long CFG_FORCE_EN_ZCC;// 1

        //# Enable arming comparator hysteresis
        long CFG_EN_HYST;// 1

        //# Disable debug ZCC comparator
        long CFG_FORCE_TH;// 0

        //# Synchronize input on edge
        long CFG_SYNC_LEVEL_MODE;// 0

        //# Pulse length of 4
        long CFG_PULSE_STRETCH;// 3

        //## Trigger
        //# Disable self-triggering
        long CFG_SELF_TRIGGER_MODE;// 0
        //# Output Sbits at 320MHz
        long CFG_DDR_TRIGGER_MODE;// 0

        //## Data format
        //# Disable zero suppression
        long CFG_SPZS_SUMMARY_ONLY;// 0
        long CFG_SPZS_MAX_PARTITIONS;// 0
        long CFG_SPZS_ENABLE;// 0
        long CFG_SZP_ENABLE;// 0
        long CFG_SZD_ENABLE;// 0
        //# Default time tags
        long CFG_TIME_TAG;// 0
        long CFG_EC_BYTES;// 0
        long CFG_BC_BYTES;// 0

        //## Latency
        //# Default latency for Scurves
        long CFG_LATENCY;// 57

        //## Calibration pulses
        //# Ensure the calibration module is off
        long CFG_CAL_MODE;// 0

        //# Negative polarity
        long CFG_CAL_SEL_POL;// 0

        //# Pulse amplitude
        long CFG_CAL_DAC;// 0

        long CFG_CAL_EXT;// 0
        long CFG_CAL_PHI;// 0
        long CFG_CAL_FS;// 0
        long CFG_CAL_DUR;// 511

        //# Zeroing out all 127 channels
        std::vector<int> VFAT_CHANNELS_CHANNEL_0_to_128;// 0


        string vfat_columns[48] =
                                    {"CFG_IREF",
                                    "CFG_HYST",
                                    "CFG_BIAS_CFD_DAC_2",
                                    "CFG_BIAS_CFD_DAC_1",
                                    "CFG_BIAS_PRE_I_BSF",
                                            
                                    "CFG_BIAS_PRE_I_BIT",
                                    "CFG_BIAS_PRE_I_BLCC",
                                    "CFG_BIAS_PRE_VREF",
                                    "CFG_BIAS_SH_I_BFCAS",
                                    "CFG_BIAS_SH_I_BDIFF",
                                    "CFG_BIAS_SH_I_BFAMP","CFG_BIAS_SD_I_BDIFF",
                                    "CFG_BIAS_SD_I_BSF",
                                    "CFG_BIAS_SD_I_BFCAS",
                                    "CFG_VREF_ADC","CFG_MON_GAIN","CFG_MONITOR_SELECT",
                                    "CFG_RES_PRE","CFG_CAP_PRE",
                                    "CFG_FP_FE","CFG_PT",
                                    "CFG_SEL_POL",
                                    "CFG_THR_ZCC_DAC",
                                    "CFG_THR_ARM_DAC",
                                    "CFG_SEL_COMP_MODE","CFG_FORCE_EN_ZCC",
                                    "CFG_EN_HYST",
                                    "CFG_FORCE_TH",
                                    "CFG_SYNC_LEVEL_MODE",
                                    "CFG_PULSE_STRETCH",
                                    "CFG_SELF_TRIGGER_MODE",
                                    "CFG_DDR_TRIGGER_MODE",
                                    "CFG_SPZS_SUMMARY_ONLY","CFG_SPZS_MAX_PARTITIONS","CFG_SPZS_ENABLE","CFG_SZP_ENABLE","CFG_SZD_ENABLE",
                                    "CFG_TIME_TAG","CFG_EC_BYTES","CFG_BC_BYTES",
                                    "CFG_LATENCY",
                                    "CFG_CAL_MODE",
                                    "CFG_CAL_SEL_POL",
                                    "CFG_CAL_DAC",
                                    "CFG_CAL_EXT","CFG_CAL_PHI","CFG_CAL_FS","CFG_CAL_DUR" };

    public:

        void create_table(connection *C,string table_name);
        //void initialize(long VFAT_ID, vector<long> field_val, vector<long> array_val);
        void initialize(long VFAT_ID, unordered_map<string, long> field_val, vector<long> array_val);
        long insert_row(connection *C, string table_name);
        void insert_data(connection *C, vector<VFAT_Data_Table> data,long config_id);
        vector<VFAT_Data_Table> row_to_object(result R);
	vector<VFAT_Data_Table> ref_compare(vector<VFAT_Data_Table> vfat_ob, vector<VFAT_Data_Table> ref_ob);
	int compare(const VFAT_Data_Table& ob1, const VFAT_Data_Table& ob2);
        void display_row();
        void display_results(vector<VFAT_Data_Table> &data);

};

#endif
