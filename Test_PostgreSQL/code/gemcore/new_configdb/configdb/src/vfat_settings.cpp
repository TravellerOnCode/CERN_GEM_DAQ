/// Include the Header File
#include "../interface/vfat_settings.h"

const std::string vfat_columns[] = { "IREF",
        "HYST",
        "BIAS_CFD_DAC_2",
        "BIAS_CFD_DAC_1",
        "BIAS_PRE_I_BSF",
        "BIAS_PRE_I_BIT",
        "BIAS_PRE_I_BLCC",
        "BIAS_PRE_VREF",
        "BIAS_SH_I_BFCAS",
        "BIAS_SH_I_BDIFF",
        "BIAS_SH_I_BFAMP",
        "BIAS_SD_I_BDIFF",
        "BIAS_SD_I_BSF",
        "BIAS_SD_I_BFCAS",
        "VREF_ADC",
        "MON_GAIN",
        "MONITOR_SELECT",
        "RES_PRE",
        "CAP_PRE",
        "FP_FE",
        "PT",
        "SEL_POL",
        "THR_ZCC_DAC",
        "THR_ARM_DAC",
        "SEL_COMP_MODE",
        "FORCE_EN_ZCC",
        "EN_HYST",
        "FORCE_TH",
        "SYNC_LEVEL_MODE",
        "PULSE_STRETCH",
        "SELF_TRIGGER_MODE",
        "DDR_TRIGGER_MODE",
        "SPZS_SUMMARY_ONLY",
        "SPZS_MAX_PARTITIONS",
        "SPZS_ENABLE",
        "SZP_ENABLE",
        "SZD_ENABLE",
        "TIME_TAG",
        "EC_BYTES",
        "BC_BYTES",
        "LATENCY",
        "CAL_MODE",
        "CAL_SEL_POL",
        "CAL_DAC",
        "CAL_EXT",
        "CAL_PHI",
        "CAL_FS",
        "CAL_DUR" };

void vfat_settings::create_table(pqxx::connection* db_client)
{
    pqxx::work WW(*db_client);
    /// Structure the PostgreSQL Statement to create a table
    std::string query = std::string("CREATE TABLE IF NOT EXISTS ") + "SETTINGS_TABLE" + "(ID SERIAL PRIMARY KEY, VFAT_ID bigint,";
    /// Append the VFAT Column Names
    for (int i = 0; i < 48; i++)
        query = query + vfat_columns[i] + " bigint" + ", ";
    query = query + "VFAT_CHANNELS_CHANNEL_0_to_128" + " integer[]);";

    // std::cout << "Executed Query : " << std::endl << query << std::endl;
    /// Execute the PostgreSQL Statement and create the table
    WW.exec(query);
    std::cout << std::string("Table Created -> ") << "SETTINGS_TABLE" << std::endl;
    /// Commit pqxx::Work to the database
    WW.commit();
}


void vfat_settings::initialize(long VFAT_ID,
    std::unordered_map<std::string, long> field_val,
    //const std::vector<long> &array_val)
const std::array<int,128> &array_val)
{
    /// Initialize the Field Vales
    this->VFAT_ID = VFAT_ID;

    this->IREF = field_val["IREF"];
    this->HYST = field_val["HYST"];

    this->BIAS_CFD_DAC_2 = field_val["BIAS_CFD_DAC_2"];
    this->BIAS_CFD_DAC_1 = field_val["BIAS_CFD_DAC_1"];
    this->BIAS_PRE_I_BSF = field_val["BIAS_PRE_I_BSF"];

    this->BIAS_PRE_I_BIT = field_val["BIAS_PRE_I_BIT"];
    this->BIAS_PRE_I_BLCC = field_val["BIAS_PRE_I_BLCC"];
    this->BIAS_PRE_VREF = field_val["BIAS_PRE_VREF"];
    this->BIAS_SH_I_BFCAS = field_val["BIAS_SH_I_BFCAS"];
    this->BIAS_SH_I_BDIFF = field_val["BIAS_SH_I_BDIFF"];
    this->BIAS_SH_I_BFAMP = field_val["BIAS_SH_I_BFAMP"];
    this->BIAS_SD_I_BDIFF = field_val["BIAS_SD_I_BDIFF"];
    this->BIAS_SD_I_BSF = field_val["BIAS_SD_I_BSF"];
    this->BIAS_SD_I_BFCAS = field_val["BIAS_SD_I_BFCAS"];

    this->VREF_ADC = field_val["VREF_ADC"];
    this->MON_GAIN = field_val["MON_GAIN"];
    this->MONITOR_SELECT = field_val["MONITOR_SELECT"];

    this->RES_PRE = field_val["RES_PRE"];
    this->CAP_PRE = field_val["CAP_PRE"];

    this->FP_FE = field_val["FP_FE"];
    this->PT = field_val["PT"];

    this->SEL_POL = field_val["SEL_POL"];

    this->THR_ZCC_DAC = field_val["THR_ZCC_DAC"];

    this->THR_ARM_DAC = field_val["THR_ARM_DAC"];

    this->SEL_COMP_MODE = field_val["SEL_COMP_MODE"];
    this->FORCE_EN_ZCC = field_val["FORCE_EN_ZCC"];
    this->EN_HYST = field_val["EN_HYST"];
    this->FORCE_TH = field_val["FORCE_TH"];

    this->SYNC_LEVEL_MODE = field_val["SYNC_LEVEL_MODE"];

    this->PULSE_STRETCH = field_val["PULSE_STRETCH"];

    this->SELF_TRIGGER_MODE = field_val["SELF_TRIGGER_MODE"];
    this->DDR_TRIGGER_MODE = field_val["DDR_TRIGGER_MODE"];

    this->SPZS_SUMMARY_ONLY = field_val["SPZS_SUMMARY_ONLY"];
    this->SPZS_MAX_PARTITIONS = field_val["SPZS_MAX_PARTITIONS"];
    this->SPZS_ENABLE = field_val["SPZS_ENABLE"];
    this->SZP_ENABLE = field_val["SZP_ENABLE"];
    this->SZD_ENABLE = field_val["SZD_ENABLE"];

    this->TIME_TAG = field_val["TIME_TAG"];
    this->EC_BYTES = field_val["EC_BYTES"];
    this->BC_BYTES = field_val["BC_BYTES"];

    this->LATENCY = field_val["LATENCY"];

    this->CAL_MODE = field_val["CAL_MODE"];

    this->CAL_SEL_POL = field_val["CAL_SEL_POL"];

    this->CAL_DAC = field_val["CAL_DAC"];

    this->CAL_EXT = field_val["CAL_EXT"];
    this->CAL_PHI = field_val["CAL_PHI"];
    this->CAL_FS = field_val["CAL_FS"];
    this->CAL_DUR = field_val["CAL_DUR"];

    //for (auto value = array_val.begin(); value != array_val.end(); ++value) {
    //    VFAT_CHANNELS_CHANNEL_0_to_128.push_back(*value);
    //}
    for (int i = 0; i< 128;i++){
        VFAT_CHANNELS_CHANNEL_0_to_128[i] = array_val[i];
    }

    // std::cout << "******" << array_val[0] << std::endl;
}

long vfat_settings::insert_row(pqxx::connection* db_client)
{
    pqxx::work WW(*db_client);
    long id;

    /// Structure the PostgreSQL Statement to insert data
    std::string field_values = "", arrays = "'{";
    std::string sql = std::string("INSERT INTO ") + "SETTINGS_TABLE" + "(VFAT_ID,";
    for (int i = 0; i < 48; i++) {
        sql = sql + vfat_columns[i] + ", ";
    }
    sql = sql + "VFAT_CHANNELS_CHANNEL_0_to_128) VALUES (";

    /// Append the field values to the SQL Statement.
    field_values = std::to_string(this->VFAT_ID) + ", ";
    field_values = field_values + std::to_string(this->IREF) + ", " + std::to_string(this->HYST) + ", " + std::to_string(this->BIAS_CFD_DAC_2) + ", " + std::to_string(this->BIAS_CFD_DAC_1) + ", " + std::to_string(this->BIAS_PRE_I_BSF) + ", " + std::to_string(this->BIAS_PRE_I_BIT) + ", " + std::to_string(this->BIAS_PRE_I_BLCC) + ", " + std::to_string(this->BIAS_PRE_VREF) + ", " + std::to_string(this->BIAS_SH_I_BFCAS) + ", " + std::to_string(this->BIAS_SH_I_BDIFF) + ", " + std::to_string(this->BIAS_SH_I_BFAMP) + ", " + std::to_string(this->BIAS_SD_I_BDIFF) + ", " + std::to_string(this->BIAS_SD_I_BSF) + ", " + std::to_string(this->BIAS_SD_I_BFCAS) + ", " + std::to_string(this->VREF_ADC) + ", " + std::to_string(this->MON_GAIN) + ", " + std::to_string(this->MONITOR_SELECT) + ", " + std::to_string(this->RES_PRE) + ", " + std::to_string(this->CAP_PRE) + ", " + std::to_string(this->FP_FE) + ", " + std::to_string(this->PT) + ", " + std::to_string(this->SEL_POL) + ", " + std::to_string(this->THR_ZCC_DAC) + ", " + std::to_string(this->THR_ARM_DAC) + ", " + std::to_string(this->SEL_COMP_MODE) + ", " + std::to_string(this->FORCE_EN_ZCC) + ", " + std::to_string(this->EN_HYST) + ", " + std::to_string(this->FORCE_TH) + ", " + std::to_string(this->SYNC_LEVEL_MODE) + ", " + std::to_string(this->PULSE_STRETCH) + ", " + std::to_string(this->SELF_TRIGGER_MODE) + ", " + std::to_string(this->DDR_TRIGGER_MODE) + ", " + std::to_string(this->SPZS_SUMMARY_ONLY) + ", " + std::to_string(this->SPZS_MAX_PARTITIONS) + ", " + std::to_string(this->SPZS_ENABLE) + ", " + std::to_string(this->SZP_ENABLE) + ", " + std::to_string(this->SZD_ENABLE) + ", " + std::to_string(this->TIME_TAG) + ", " + std::to_string(this->EC_BYTES) + ", " + std::to_string(this->BC_BYTES) + ", " + std::to_string(this->LATENCY) + ", " + std::to_string(this->CAL_MODE) + ", " + std::to_string(this->CAL_SEL_POL) + ", " + std::to_string(this->CAL_DAC) + ", " + std::to_string(this->CAL_EXT) + ", " + std::to_string(this->CAL_PHI) + ", " + std::to_string(this->CAL_FS) + ", " + std::to_string(this->CAL_DUR) + ", ";

    for (int i = 0; i < 127; i++) {
        arrays = arrays + std::to_string(this->VFAT_CHANNELS_CHANNEL_0_to_128[i]) + ", ";
    }

    /// PostgreSQL Insert Statement
    sql = sql + field_values + arrays + std::to_string(this->VFAT_CHANNELS_CHANNEL_0_to_128[127]) + "}') RETURNING ID;";

    /// Execute the PostgreSQL Statement and insert data into the table.
    /// Insertion returns a system generated ID into R
    pqxx::result R = WW.exec(sql);
    /// Extracts the ID from the response and store in id.
    for (auto const& row : R)
        id = row["ID"].as<long>();

    /// Commit pqxx::Work to the database
    WW.commit();

    /// Return the id
    return id;
}

// This should accept only those Objects that are unique
void vfat_settings::insert_data(pqxx::connection* db_client,
    std::vector<vfat_settings> data,
    long config_id)
{
    long id;
    /// Insert extracted data, Iterate the Object std::vector
    for (auto rowObject = data.begin(); rowObject != data.end(); ++rowObject) {
        /// Insert data of a particular object
        id = (*rowObject).insert_row(&(*db_client));

        // Insert into Index Table along with Config
        vfat_indexes obj;
        obj.initialize(config_id, id);
        obj.insert_row(&(*db_client));
    }
    std::cout << "Values inserted into table : " << "SETTINGS_TABLE" << std::endl;
}

std::vector<vfat_settings> vfat_settings::row_to_object(pqxx::result R)
{
    std::vector<vfat_settings> query_results;

    for (auto const& row : R) {
        vfat_settings obj;
        obj.m_id = row["ID"].as<long>(); // System Generated ID

        obj.VFAT_ID = row["VFAT_ID"].as<long>();

        // Actual VFAT Columns
        obj.IREF = row["IREF"].as<long>();
        obj.HYST = row["HYST"].as<long>();

        obj.BIAS_CFD_DAC_2 = row["BIAS_CFD_DAC_2"].as<long>();
        obj.BIAS_CFD_DAC_1 = row["BIAS_CFD_DAC_1"].as<long>();
        obj.BIAS_PRE_I_BSF = row["BIAS_PRE_I_BSF"].as<long>();

        obj.BIAS_PRE_I_BIT = row["BIAS_PRE_I_BIT"].as<long>();
        obj.BIAS_PRE_I_BLCC = row["BIAS_PRE_I_BLCC"].as<long>();
        obj.BIAS_PRE_VREF = row["BIAS_PRE_VREF"].as<long>();
        obj.BIAS_SH_I_BFCAS = row["BIAS_SH_I_BFCAS"].as<long>();
        obj.BIAS_SH_I_BDIFF = row["BIAS_SH_I_BDIFF"].as<long>();
        obj.BIAS_SH_I_BFAMP = row["BIAS_SH_I_BFAMP"].as<long>();
        obj.BIAS_SD_I_BDIFF = row["BIAS_SD_I_BDIFF"].as<long>();
        obj.BIAS_SD_I_BSF = row["BIAS_SD_I_BSF"].as<long>();
        obj.BIAS_SD_I_BFCAS = row["BIAS_SD_I_BFCAS"].as<long>();

        //## DAC monitor
        obj.VREF_ADC = row["VREF_ADC"].as<long>();
        obj.MON_GAIN = row["MON_GAIN"].as<long>();
        obj.MONITOR_SELECT = row["MONITOR_SELECT"].as<long>();

        //## Input
        //# Preamp gain - high
        obj.RES_PRE = row["RES_PRE"].as<long>();
        obj.CAP_PRE = row["CAP_PRE"].as<long>();
        //# Preamp gain - medium
        // long RES_PRE;// 2
        // long CAP_PRE;// 1
        //# Preamp gain - low
        // long RES_PRE;// 4
        // long CAP_PRE;// 3

        //# Timing constants - long
        obj.FP_FE = row["FP_FE"].as<long>();
        obj.PT = row["PT"].as<long>();
        obj.PT = row["PT"].as<long>();

        //# Use negative polarity (errata VFAT3 manual)
        obj.SEL_POL = row["SEL_POL"].as<long>();

        //# Provide a slight offset to the ZCC comparator baseline voltage
        obj.THR_ZCC_DAC = row["THR_ZCC_DAC"].as<long>();

        //# "Main" threshold
        obj.THR_ARM_DAC = row["THR_ARM_DAC"].as<long>();

        //# Comparator mode - CFD
        obj.SEL_COMP_MODE = row["SEL_COMP_MODE"].as<long>();
        obj.FORCE_EN_ZCC = row["FORCE_EN_ZCC"].as<long>();
        //# Comparator mode - arming
        obj.SEL_COMP_MODE = row["SEL_COMP_MODE"].as<long>();
        obj.FORCE_EN_ZCC = row["FORCE_EN_ZCC"].as<long>();
        //# Comparator mode - ZCC
        obj.SEL_COMP_MODE = row["SEL_COMP_MODE"].as<long>();
        obj.FORCE_EN_ZCC = row["FORCE_EN_ZCC"].as<long>();

        //# Enable arming comparator hysteresis
        obj.EN_HYST = row["EN_HYST"].as<long>();

        //# Disable debug ZCC comparator
        obj.FORCE_TH = row["FORCE_TH"].as<long>();

        //# Synchronize input on edge
        obj.SYNC_LEVEL_MODE = row["SYNC_LEVEL_MODE"].as<long>();

        //# Pulse length of 4
        obj.PULSE_STRETCH = row["PULSE_STRETCH"].as<long>();

        //## Trigger
        //# Disable self-triggering
        obj.SELF_TRIGGER_MODE = row["SELF_TRIGGER_MODE"].as<long>();
        //# Output Sbits at 320MHz
        obj.DDR_TRIGGER_MODE = row["DDR_TRIGGER_MODE"].as<long>();

        //## Data format
        //# Disable zero suppression
        obj.SPZS_SUMMARY_ONLY = row["SPZS_SUMMARY_ONLY"].as<long>();
        obj.SPZS_MAX_PARTITIONS = row["SPZS_MAX_PARTITIONS"].as<long>();
        obj.SPZS_ENABLE = row["SPZS_ENABLE"].as<long>();
        obj.SZP_ENABLE = row["SZP_ENABLE"].as<long>();
        obj.SZD_ENABLE = row["SZD_ENABLE"].as<long>();
        //# Default time tags
        obj.TIME_TAG = row["TIME_TAG"].as<long>();
        obj.EC_BYTES = row["EC_BYTES"].as<long>();
        obj.BC_BYTES = row["BC_BYTES"].as<long>();

        //## Latency
        //# Default latency for Scurves
        obj.LATENCY = row["LATENCY"].as<long>();

        //## Calibration pulses
        //# Ensure the calibration module is off
        obj.CAL_MODE = row["CAL_MODE"].as<long>();

        //# Negative polarity
        obj.CAL_SEL_POL = row["CAL_SEL_POL"].as<long>();

        //# Pulse amplitude
        obj.CAL_DAC = row["CAL_DAC"].as<long>();

        obj.CAL_EXT = row["CAL_EXT"].as<long>();
        obj.CAL_PHI = row["CAL_PHI"].as<long>();
        obj.CAL_FS = row["CAL_FS"].as<long>();
        obj.CAL_DUR = row["CAL_DUR"].as<long>();

        //# Zeroing out all 127 channels
        // std::vector<int> VFAT_CHANNELS_CHANNEL_0_to_128;// 0
        std::string str = row["VFAT_CHANNELS_CHANNEL_0_to_128"].c_str();
        str = str.substr(1, str.length());
        int i = 0;
        std::stringstream ss(str);
        while (ss.good()) {
            std::string sub;
            getline(ss, sub, ',');
            int d = stoi(sub);
            //obj.VFAT_CHANNELS_CHANNEL_0_to_128.push_back(d);
            obj.VFAT_CHANNELS_CHANNEL_0_to_128[i++] = d; 
        }

        // obj.display_row();
        query_results.push_back(obj);
    }
    // display_results(query_results);
    return query_results;
}

// Display a particular row of the table
void vfat_settings::display_row()
{
    std::cout << std::left << std::setw(30) << "ID " << std::setw(2) << ":" << this->m_id
              << std::endl;
    std::cout << std::left << std::setw(30) << "VFAT_ID " << std::setw(2) << ":"
              << this->VFAT_ID << std::endl;
    std::cout << std::left << std::setw(30) << "IREF " << std::setw(2) << ":"
              << this->IREF << std::endl;
    std::cout << std::left << std::setw(30) << "HYST " << std::setw(2) << ":"
              << this->HYST << std::endl;

    std::cout << std::left << std::setw(30) << "BIAS_CFD_DAC_2 " << std::setw(2)
              << ":" << this->BIAS_CFD_DAC_2 << std::endl;
    std::cout << std::left << std::setw(30) << "BIAS_CFD_DAC_1 " << std::setw(2)
              << ":" << this->BIAS_CFD_DAC_1 << std::endl;
    std::cout << std::left << std::setw(30) << "BIAS_PRE_I_BSF " << std::setw(2)
              << ":" << this->BIAS_PRE_I_BSF << std::endl;

    std::cout << std::left << std::setw(30) << "BIAS_PRE_I_BIT " << std::setw(2)
              << ":" << this->BIAS_PRE_I_BIT << std::endl;
    std::cout << std::left << std::setw(30) << "BIAS_PRE_I_BLCC " << std::setw(2)
              << ":" << this->BIAS_PRE_I_BLCC << std::endl;
    std::cout << std::left << std::setw(30) << "BIAS_PRE_VREF " << std::setw(2)
              << ":" << this->BIAS_PRE_VREF << std::endl;
    std::cout << std::left << std::setw(30) << "BIAS_SH_I_BFCAS " << std::setw(2)
              << ":" << this->BIAS_SH_I_BFCAS << std::endl;
    std::cout << std::left << std::setw(30) << "BIAS_SH_I_BDIFF " << std::setw(2)
              << ":" << this->BIAS_SH_I_BDIFF << std::endl;
    std::cout << std::left << std::setw(30) << "BIAS_SH_I_BFAMP " << std::setw(2)
              << ":" << this->BIAS_SH_I_BFAMP << std::endl;
    std::cout << std::left << std::setw(30) << "BIAS_SD_I_BDIFF " << std::setw(2)
              << ":" << this->BIAS_SD_I_BDIFF << std::endl;
    std::cout << std::left << std::setw(30) << "BIAS_SD_I_BSF " << std::setw(2)
              << ":" << this->BIAS_SD_I_BSF << std::endl;
    std::cout << std::left << std::setw(30) << "BIAS_SD_I_BFCAS " << std::setw(2)
              << ":" << this->BIAS_SD_I_BFCAS << std::endl;

    std::cout << std::left << std::setw(30) << "VREF_ADC " << std::setw(2) << ":"
              << this->VREF_ADC << std::endl;
    std::cout << std::left << std::setw(30) << "MON_GAIN " << std::setw(2) << ":"
              << this->MON_GAIN << std::endl;
    std::cout << std::left << std::setw(30) << "MONITOR_SELECT " << std::setw(2)
              << ":" << this->MONITOR_SELECT << std::endl;

    std::cout << std::left << std::setw(30) << "RES_PRE " << std::setw(2) << ":"
              << this->RES_PRE << std::endl;
    std::cout << std::left << std::setw(30) << "CAP_PRE " << std::setw(2) << ":"
              << this->CAP_PRE << std::endl;

    std::cout << std::left << std::setw(30) << "FP_FE " << std::setw(2) << ":"
              << this->FP_FE << std::endl;
    std::cout << std::left << std::setw(30) << "PT " << std::setw(2) << ":"
              << this->PT << std::endl;

    std::cout << std::left << std::setw(30) << "SEL_POL " << std::setw(2) << ":"
              << this->SEL_POL << std::endl;

    std::cout << std::left << std::setw(30) << "THR_ZCC_DAC " << std::setw(2)
              << ":" << this->THR_ZCC_DAC << std::endl;

    std::cout << std::left << std::setw(30) << "THR_ARM_DAC " << std::setw(2)
              << ":" << this->THR_ARM_DAC << std::endl;

    std::cout << std::left << std::setw(30) << "SEL_COMP_MODE " << std::setw(2)
              << ":" << this->SEL_COMP_MODE << std::endl;
    std::cout << std::left << std::setw(30) << "FORCE_EN_ZCC " << std::setw(2)
              << ":" << this->FORCE_EN_ZCC << std::endl;
    std::cout << std::left << std::setw(30) << "EN_HYST " << std::setw(2) << ":"
              << this->EN_HYST << std::endl;
    std::cout << std::left << std::setw(30) << "FORCE_TH " << std::setw(2) << ":"
              << this->FORCE_TH << std::endl;

    std::cout << std::left << std::setw(30) << "SYNC_LEVEL_MODE " << std::setw(2)
              << ":" << this->SYNC_LEVEL_MODE << std::endl;

    std::cout << std::left << std::setw(30) << "PULSE_STRETCH " << std::setw(2)
              << ":" << this->PULSE_STRETCH << std::endl;

    std::cout << std::left << std::setw(30) << "SELF_TRIGGER_MODE " << std::setw(2)
              << ":" << this->SELF_TRIGGER_MODE << std::endl;
    std::cout << std::left << std::setw(30) << "DDR_TRIGGER_MODE " << std::setw(2)
              << ":" << this->DDR_TRIGGER_MODE << std::endl;

    std::cout << std::left << std::setw(30) << "SPZS_SUMMARY_ONLY " << std::setw(2)
              << ":" << this->SPZS_SUMMARY_ONLY << std::endl;
    std::cout << std::left << std::setw(30) << "SPZS_MAX_PARTITIONS "
              << std::setw(2) << ":" << this->SPZS_MAX_PARTITIONS << std::endl;
    std::cout << std::left << std::setw(30) << "SPZS_ENABLE " << std::setw(2)
              << ":" << this->SPZS_ENABLE << std::endl;
    std::cout << std::left << std::setw(30) << "SZP_ENABLE " << std::setw(2) << ":"
              << this->SZP_ENABLE << std::endl;
    std::cout << std::left << std::setw(30) << "SZD_ENABLE " << std::setw(2) << ":"
              << this->SZD_ENABLE << std::endl;

    std::cout << std::left << std::setw(30) << "TIME_TAG " << std::setw(2) << ":"
              << this->TIME_TAG << std::endl;
    std::cout << std::left << std::setw(30) << "EC_BYTES " << std::setw(2) << ":"
              << this->EC_BYTES << std::endl;
    std::cout << std::left << std::setw(30) << "BC_BYTES " << std::setw(2) << ":"
              << this->BC_BYTES << std::endl;

    std::cout << std::left << std::setw(30) << "LATENCY " << std::setw(2) << ":"
              << this->LATENCY << std::endl;

    std::cout << std::left << std::setw(30) << "CAL_MODE " << std::setw(2) << ":"
              << this->CAL_MODE << std::endl;

    std::cout << std::left << std::setw(30) << "CAL_SEL_POL " << std::setw(2)
              << ":" << this->CAL_SEL_POL << std::endl;

    std::cout << std::left << std::setw(30) << "CAL_DAC " << std::setw(2) << ":"
              << this->CAL_DAC << std::endl;

    std::cout << std::left << std::setw(30) << "CAL_EXT " << std::setw(2) << ":"
              << this->CAL_EXT << std::endl;
    std::cout << std::left << std::setw(30) << "CAL_PHI " << std::setw(2) << ":"
              << this->CAL_PHI << std::endl;
    std::cout << std::left << std::setw(30) << "CAL_FS " << std::setw(2) << ":"
              << this->CAL_FS << std::endl;
    std::cout << std::left << std::setw(30) << "CAL_DUR " << std::setw(2) << ":"
              << this->CAL_DUR << std::endl;

    std::cout << std::left << std::setw(30) << "VFAT_CHANNELS_CHANNEL_0_to_128 "
              << std::setw(2) << ":"
              << "[ ";
    for (int i = 0; i < 128 - 1; i++) {
        std::cout << this->VFAT_CHANNELS_CHANNEL_0_to_128[i] << ", ";
    }
    std::cout << this->VFAT_CHANNELS_CHANNEL_0_to_128[127] << "] " << std::endl
              << std::endl;
}

// Display results
void vfat_settings::display_results(std::vector<vfat_settings>& data)
{
    int i = 1;
    for (auto rowObject = data.begin(); rowObject != data.end(); ++rowObject) {
        /// Insert data of a particular object
        (*rowObject).display_row();
        std::cout << "------" << std::endl
                  << std::endl;
        i++;
        if (i == 10)
            break;
    }
}

int vfat_settings::compareSettings(const vfat_settings& ob1,
    const vfat_settings& ob2)
{
    // compares all fields of two objects and returns value 1 if unequal, 0 if
    // equal

    int flag = 0;
    if (ob1.IREF != ob2.IREF || ob1.HYST != ob2.HYST || ob1.BIAS_CFD_DAC_2 != ob2.BIAS_CFD_DAC_2 || ob1.BIAS_CFD_DAC_1 != ob2.BIAS_CFD_DAC_1 || ob1.BIAS_PRE_I_BSF != ob2.BIAS_PRE_I_BSF || ob1.BIAS_PRE_I_BIT != ob2.BIAS_PRE_I_BIT || ob1.BIAS_PRE_I_BLCC != ob2.BIAS_PRE_I_BLCC || ob1.BIAS_PRE_VREF != ob2.BIAS_PRE_VREF || ob1.BIAS_SH_I_BFCAS != ob2.BIAS_SH_I_BFCAS || ob1.BIAS_SH_I_BDIFF != ob2.BIAS_SH_I_BDIFF || ob1.BIAS_SH_I_BFAMP != ob2.BIAS_SH_I_BFAMP || ob1.BIAS_SD_I_BDIFF != ob2.BIAS_SD_I_BDIFF || ob1.BIAS_SD_I_BSF != ob2.BIAS_SD_I_BSF || ob1.BIAS_SD_I_BFCAS != ob2.BIAS_SD_I_BFCAS || ob1.VREF_ADC != ob2.VREF_ADC || ob1.MON_GAIN != ob2.MON_GAIN || ob1.MONITOR_SELECT != ob2.MONITOR_SELECT || ob1.RES_PRE != ob2.RES_PRE || ob1.CAP_PRE != ob2.CAP_PRE || ob1.FP_FE != ob2.FP_FE || ob1.PT != ob2.PT || ob1.SEL_POL != ob2.SEL_POL || ob1.THR_ZCC_DAC != ob2.THR_ZCC_DAC || ob1.THR_ARM_DAC != ob2.THR_ARM_DAC || ob1.SEL_COMP_MODE != ob2.SEL_COMP_MODE || ob1.FORCE_EN_ZCC != ob2.FORCE_EN_ZCC || ob1.EN_HYST != ob2.EN_HYST || ob1.FORCE_TH != ob2.FORCE_TH || ob1.SYNC_LEVEL_MODE != ob2.SYNC_LEVEL_MODE || ob1.PULSE_STRETCH != ob2.PULSE_STRETCH || ob1.SELF_TRIGGER_MODE != ob2.SELF_TRIGGER_MODE || ob1.DDR_TRIGGER_MODE != ob2.DDR_TRIGGER_MODE || ob1.SPZS_SUMMARY_ONLY != ob2.SPZS_SUMMARY_ONLY || ob1.SPZS_MAX_PARTITIONS != ob2.SPZS_MAX_PARTITIONS || ob1.SPZS_ENABLE != ob2.SPZS_ENABLE || ob1.SZP_ENABLE != ob2.SZP_ENABLE || ob1.SZD_ENABLE != ob2.SZD_ENABLE || ob1.TIME_TAG != ob2.TIME_TAG || ob1.EC_BYTES != ob2.EC_BYTES || ob1.BC_BYTES != ob2.BC_BYTES || ob1.LATENCY != ob2.LATENCY || ob1.CAL_MODE != ob2.CAL_MODE || ob1.CAL_SEL_POL != ob2.CAL_SEL_POL || ob1.CAL_DAC != ob2.CAL_DAC || ob1.CAL_EXT != ob2.CAL_EXT || ob1.CAL_PHI != ob2.CAL_PHI || ob1.CAL_FS != ob2.CAL_FS || ob1.CAL_DUR != ob2.CAL_DUR) {
        flag = 1;
    }

    if (flag != 0)
        return 1;
    else {
        if (!(ob1.VFAT_CHANNELS_CHANNEL_0_to_128 == ob2.VFAT_CHANNELS_CHANNEL_0_to_128))
            return 1;
        else
            return 0;
    }
}

std::vector<vfat_settings> vfat_settings::getNewSettings(
    pqxx::connection* db_client, std::vector<vfat_settings> vfat_ob,
    std::vector<vfat_settings> ref_ob, long config_id)
{
    std::vector<vfat_settings> insert_vfats;

    for (auto rowObject = vfat_ob.begin(); rowObject != vfat_ob.end();
         ++rowObject) {
        for (auto refObject = ref_ob.begin(); refObject != ref_ob.end();
             ++refObject) {

            if ((*rowObject).VFAT_ID == (*refObject).VFAT_ID) {
                if (compareSettings((*rowObject), (*refObject)) == 1)
                    insert_vfats.push_back((*rowObject));
                else {
                    vfat_indexes obj;
                    obj.initialize(config_id, (*refObject).id());
                    obj.insert_row(&(*db_client));
                }
            }
        }
    }
    std::cout << "ALL References Resolved !" << std::endl
              << std::endl;
    return insert_vfats;
}