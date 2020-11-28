#include "VFAT_Data_Table.h"

void VFAT_Data_Table ::create_table(connection *C,string table_name)
{
        work WW(*C);
        string query = "CREATE TABLE " + table_name + "(";
        for (int i=0;i<48;i++)
        {
            query = query + vfat_columns[i] + " bigint" +", ";
        }
        query = query + "VFAT_CHANNELS_CHANNEL_0_to_128" + " integer[]);";
        cout << "Executed Query : " << endl << query << endl;
        WW.exec(query);
        cout << "Table Created !" << endl;
        WW.commit();

}

void VFAT_Data_Table ::initialize()
{
            this->CFG_IREF=0;
            this->CFG_HYST=0;

            this->CFG_BIAS_CFD_DAC_2=0;
            this->CFG_BIAS_CFD_DAC_1=0;
            this->CFG_BIAS_PRE_I_BSF=0;

            this->CFG_BIAS_PRE_I_BIT=0;
            this->CFG_BIAS_PRE_I_BLCC=0;
            this->CFG_BIAS_PRE_VREF=0;
            this->CFG_BIAS_SH_I_BFCAS=0;
            this->CFG_BIAS_SH_I_BDIFF=0;
            this->CFG_BIAS_SH_I_BFAMP=0;
            this->CFG_BIAS_SD_I_BDIFF=0;
            this->CFG_BIAS_SD_I_BSF=0;
            this->CFG_BIAS_SD_I_BFCAS=0;

            this->CFG_VREF_ADC=0;
            this->CFG_MON_GAIN=0;
            this->CFG_MONITOR_SELECT=0;

            this->CFG_RES_PRE=0;
            this->CFG_CAP_PRE=0;

            this->CFG_FP_FE=0;
            this->CFG_PT=0;

            this->CFG_SEL_POL=0;

            this->CFG_THR_ZCC_DAC=0;

            this->CFG_THR_ARM_DAC=0;

            this->CFG_SEL_COMP_MODE=0;
            this->CFG_FORCE_EN_ZCC=0;
            this->CFG_EN_HYST=0;
            this->CFG_FORCE_TH=0;

            this->CFG_SYNC_LEVEL_MODE=0;

            this->CFG_PULSE_STRETCH=0;

            this->CFG_SELF_TRIGGER_MODE=0;
            this->CFG_DDR_TRIGGER_MODE=0;

            this->CFG_SPZS_SUMMARY_ONLY=0;
            this->CFG_SPZS_MAX_PARTITIONS=0;
            this->CFG_SPZS_ENABLE=0;
            this->CFG_SZP_ENABLE=0;
            this->CFG_SZD_ENABLE=0;

            this->CFG_TIME_TAG=0;
            this->CFG_EC_BYTES=0;
            this->CFG_BC_BYTES=0;

            this->CFG_LATENCY=0;

            this->CFG_CAL_MODE=0;

            this->CFG_CAL_SEL_POL=0;

            this->CFG_CAL_DAC=0;

            this->CFG_CAL_EXT=0;
            this->CFG_CAL_PHI=0;
            this->CFG_CAL_FS=0;
            this->CFG_CAL_DUR=0;
}

void VFAT_Data_Table:: insert_row(connection *C, string table_name)
{
        work WW(*C);
        string field_values = "",arrays = "'{";
        string sql = "INSERT INTO COMPANY(";
        for (int i=0;i<48;i++)
        {
            sql = sql + vfat_columns[i] + ", ";
        }
        sql = sql + ") VALUES (";
        
        field_values = field_values + 
                        to_string(this->CFG_IREF) + ", '" +to_string(this->CFG_HYST)+ ", '" \
                        +to_string(this->CFG_BIAS_CFD_DAC_2)+ ", '" +to_string(this->CFG_BIAS_CFD_DAC_1)+ ", '" +to_string(this->CFG_BIAS_PRE_I_BSF)+ ", '" \
                        +to_string(this->CFG_BIAS_PRE_I_BIT)+ ", '" +to_string(this->CFG_BIAS_PRE_I_BLCC)+ ", '" +to_string(this->CFG_BIAS_PRE_VREF)+ ", '" \
                        +to_string(this->CFG_BIAS_SH_I_BFCAS)+ ", '" +to_string(this->CFG_BIAS_SH_I_BDIFF)+ ", '" +to_string(this->CFG_BIAS_SH_I_BFAMP)+ ", '" \
                        +to_string(this->CFG_BIAS_SD_I_BDIFF)+ ", '" +to_string(this->CFG_BIAS_SD_I_BSF)+ ", '" +to_string(this->CFG_BIAS_SD_I_BFCAS)+ ", '" \
                        +to_string(this->CFG_VREF_ADC)+ ", '" +to_string(this->CFG_MON_GAIN)+ ", '" +to_string(this->CFG_MONITOR_SELECT)+ ", '" \
                        +to_string(this->CFG_RES_PRE)+ ", '" +to_string(this->CFG_CAP_PRE)+ ", '" \
                        +to_string(this->CFG_FP_FE)+ ", '" +to_string(this->CFG_PT)+ ", '" +to_string(this->CFG_SEL_POL)+ ", '" \
                        +to_string(this->CFG_THR_ZCC_DAC)+ ", '" +to_string(this->CFG_THR_ARM_DAC)+ ", '" \
                        +to_string(this->CFG_SEL_COMP_MODE)+ ", '" +to_string(this->CFG_FORCE_EN_ZCC)+ ", '" +to_string(this->CFG_EN_HYST)+ ", '" +to_string(this->CFG_FORCE_TH)+ ", '" \
                        +to_string(this->CFG_SYNC_LEVEL_MODE)+ ", '" +to_string(this->CFG_PULSE_STRETCH)+ ", '" \
                        +to_string(this->CFG_SELF_TRIGGER_MODE)+ ", '" +to_string(this->CFG_DDR_TRIGGER_MODE)+ ", '" \
                        +to_string(this->CFG_SPZS_SUMMARY_ONLY)+ ", '" +to_string(this->CFG_SPZS_MAX_PARTITIONS)+ ", '" \
                        +to_string(this->CFG_SPZS_ENABLE)+ ", '" +to_string(this->CFG_SZP_ENABLE)+ ", '" +to_string(this->CFG_SZD_ENABLE)+ ", '" \
                        +to_string(this->CFG_TIME_TAG)+ ", '" +to_string(this->CFG_EC_BYTES)+ ", '" +to_string(this->CFG_BC_BYTES)+ ", '" \
                        +to_string(this->CFG_LATENCY)+ ", '" +to_string(this->CFG_CAL_MODE)+ ", '" \
                        +to_string(this->CFG_CAL_SEL_POL)+ ", '" +to_string(this->CFG_CAL_DAC)+ ", '" \
                        +to_string(this->CFG_CAL_EXT)+ ", '" +to_string(this->CFG_CAL_PHI)+ ", '" +to_string(this->CFG_CAL_FS)+ ", '" +to_string(this->CFG_CAL_DUR)+ ", '";
        
        for (int i=0;i<128;i++)
        {
            arrays = arrays + to_string(this->VFAT_CHANNELS_CHANNEL_0_to_128[i]);
        }
        sql = sql + field_values + arrays + "}');";
        WW.exec(sql);
        WW.commit();
        cout << "Values inserted !" << endl;
}

void VFAT_Data_Table::insert_data(connection *C, vector<VFAT_Data_Table> data)
{
    int i;
    for (i=0;i<data.size();i++)
    {
        data[i].insert_row(&(*C),"COMPANY");
    }
}

vector<VFAT_Data_Table> VFAT_Data_Table::row_to_object(result R)
{
        vector<VFAT_Data_Table> query_results;

        for (auto const &row: R)
        {
            VFAT_Data_Table obj;
            //Actual VFAT Columns
            obj.CFG_IREF = row["CFG_IREF"].as<long>();
            obj.CFG_HYST = row["CFG_HYST"].as<long>(); 

            obj.CFG_BIAS_CFD_DAC_2 = row["CFG_BIAS_CFD_DAC_2"].as<long>();
            obj.CFG_BIAS_CFD_DAC_1 = row["CFG_BIAS_CFD_DAC_1"].as<long>(); 
            obj.CFG_BIAS_PRE_I_BSF = row["CFG_BIAS_PRE_I_BSF"].as<long>(); 
            
            obj.CFG_BIAS_PRE_I_BIT = row["CFG_BIAS_PRE_I_BIT"].as<long>();
            obj.CFG_BIAS_PRE_I_BLCC = row["CFG_BIAS_PRE_I_BLCC"].as<long>();
            obj.CFG_BIAS_PRE_VREF = row["CFG_BIAS_PRE_VREF"].as<long>();
            obj.CFG_BIAS_SH_I_BFCAS = row["CFG_BIAS_SH_I_BFCAS"].as<long>();
            obj.CFG_BIAS_SH_I_BDIFF = row["CFG_BIAS_SH_I_BDIFF"].as<long>();
            obj.CFG_BIAS_SH_I_BFAMP = row["CFG_BIAS_SH_I_BFAMP"].as<long>();
            obj.CFG_BIAS_SD_I_BDIFF = row["CFG_BIAS_SD_I_BDIFF"].as<long>();
            obj.CFG_BIAS_SD_I_BSF = row["CFG_BIAS_SD_I_BSF"].as<long>();
            obj.CFG_BIAS_SD_I_BFCAS = row["CFG_BIAS_SD_I_BFCAS"].as<long>();

            //## DAC monitor
            obj.CFG_VREF_ADC = row["CFG_VREF_ADC"].as<long>();
            obj.CFG_MON_GAIN = row["CFG_MON_GAIN"].as<long>();
            obj.CFG_MONITOR_SELECT = row["CFG_MONITOR_SELECT"].as<long>();

            //## Input
            //# Preamp gain - high
            obj.CFG_RES_PRE = row["CFG_RES_PRE"].as<long>();
            obj.CFG_CAP_PRE = row["CFG_CAP_PRE"].as<long>();
            //# Preamp gain - medium
            //long CFG_RES_PRE;// 2
            //long CFG_CAP_PRE;// 1
            //# Preamp gain - low
            //long CFG_RES_PRE;// 4
            //long CFG_CAP_PRE;// 3

            //# Timing constants - long
            obj.CFG_FP_FE = row["CFG_FP_FE"].as<long>();
            obj.CFG_PT = row["CFG_PT"].as<long>();
            obj.CFG_PT = row["CFG_PT"].as<long>();


            //# Use negative polarity (errata VFAT3 manual)
            obj.CFG_SEL_POL = row["CFG_SEL_POL"].as<long>();

            //# Provide a slight offset to the ZCC comparator baseline voltage
            obj.CFG_THR_ZCC_DAC = row["CFG_THR_ZCC_DAC"].as<long>();

            //# "Main" threshold
            obj.CFG_THR_ARM_DAC = row["CFG_THR_ARM_DAC"].as<long>();

            //# Comparator mode - CFD
            obj.CFG_SEL_COMP_MODE = row["CFG_SEL_COMP_MODE"].as<long>();
            obj.CFG_FORCE_EN_ZCC = row["CFG_FORCE_EN_ZCC"].as<long>();
            //# Comparator mode - arming
            obj.CFG_SEL_COMP_MODE = row["CFG_SEL_COMP_MODE"].as<long>();
            obj.CFG_FORCE_EN_ZCC = row["CFG_FORCE_EN_ZCC"].as<long>();
            //# Comparator mode - ZCC
            obj.CFG_SEL_COMP_MODE = row["CFG_SEL_COMP_MODE"].as<long>();
            obj.CFG_FORCE_EN_ZCC = row["CFG_FORCE_EN_ZCC"].as<long>();

            //# Enable arming comparator hysteresis
            obj.CFG_EN_HYST = row["CFG_EN_HYST"].as<long>();

            //# Disable debug ZCC comparator
            obj.CFG_FORCE_TH = row["CFG_FORCE_TH"].as<long>();

            //# Synchronize input on edge
            obj.CFG_SYNC_LEVEL_MODE = row["CFG_SYNC_LEVEL_MODE"].as<long>();

            //# Pulse length of 4
            obj.CFG_PULSE_STRETCH = row["CFG_PULSE_STRETCH"].as<long>();

            //## Trigger
            //# Disable self-triggering
            obj.CFG_SELF_TRIGGER_MODE = row["CFG_SELF_TRIGGER_MODE"].as<long>();
            //# Output Sbits at 320MHz
            obj.CFG_DDR_TRIGGER_MODE = row["CFG_DDR_TRIGGER_MODE"].as<long>();

            //## Data format
            //# Disable zero suppression
            obj.CFG_SPZS_SUMMARY_ONLY = row["CFG_SPZS_SUMMARY_ONLY"].as<long>();
            obj.CFG_SPZS_MAX_PARTITIONS = row["CFG_SPZS_MAX_PARTITIONS"].as<long>();
            obj.CFG_SPZS_ENABLE = row["CFG_SPZS_ENABLE"].as<long>();
            obj.CFG_SZP_ENABLE = row["CFG_SZP_ENABLE"].as<long>();
            obj.CFG_SZD_ENABLE = row["CFG_SZD_ENABLE"].as<long>();
            //# Default time tags
            obj.CFG_TIME_TAG = row["CFG_TIME_TAG"].as<long>();
            obj.CFG_EC_BYTES = row["CFG_EC_BYTES"].as<long>();
            obj.CFG_BC_BYTES = row["CFG_BC_BYTES"].as<long>();

            //## Latency
            //# Default latency for Scurves
            obj.CFG_LATENCY = row["CFG_LATENCY"].as<long>();

            //## Calibration pulses
            //# Ensure the calibration module is off
            obj.CFG_CAL_MODE = row["CFG_CAL_MODE"].as<long>();

            //# Negative polarity
            obj.CFG_CAL_SEL_POL = row["CFG_CAL_SEL_POL"].as<long>();

            //# Pulse amplitude
            obj.CFG_CAL_DAC = row["CFG_CAL_DAC"].as<long>();

            obj.CFG_CAL_EXT = row["CFG_CAL_EXT"].as<long>();
            obj.CFG_CAL_PHI = row["CFG_CAL_PHI"].as<long>();
            obj.CFG_CAL_FS = row["CFG_CAL_FS"].as<long>();
            obj.CFG_CAL_DUR = row["CFG_CAL_DUR"].as<long>();


            //# Zeroing out all 127 channels
            //vector<int> VFAT_CHANNELS_CHANNEL_0_to_128;// 0
            string str = row["VFAT_CHANNELS_CHANNEL_0_to_128"].c_str();
            str = str.substr(1,str.length());
                        
            stringstream ss(str);
            while (ss.good()) {
                string sub;
                getline(ss, sub, ',');
                int d = stoi(sub);
                obj.VFAT_CHANNELS_CHANNEL_0_to_128.push_back(d);
            }

            //obj.display_row();
            query_results.push_back(obj);
        }
        //display_results(query_results);
        return query_results;
}

