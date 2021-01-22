/// Include the Header File
#include "../interface/vfat_data_table.h"

const std::string vfat_columns[] = { "CFG_IREF",
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
        "CFG_CAL_DUR" };

void vfat_data_table::create_table(pqxx::connection* db_client)
{
    pqxx::work WW(*db_client);
    /// Structure the PostgreSQL Statement to create a table
    std::string query = std::string("CREATE TABLE IF NOT EXISTS ") + VFAT_DATA_TABLE + "(ID SERIAL PRIMARY KEY, VFAT_ID bigint,";
    /// Append the VFAT Column Names
    for (int i = 0; i < 48; i++)
        query = query + vfat_columns[i] + " bigint" + ", ";
    query = query + "VFAT_CHANNELS_CHANNEL_0_to_128" + " integer[]);";

    // std::cout << "Executed Query : " << std::endl << query << std::endl;
    /// Execute the PostgreSQL Statement and create the table
    WW.exec(query);
    std::cout << std::string("Table Created -> ") << VFAT_DATA_TABLE << std::endl;
    /// Commit pqxx::Work to the database
    WW.commit();
}

long vfat_data_table::get_id()
{
    /// Access the id
    return this->id;
}

void vfat_data_table::initialize(long VFAT_ID,
    std::unordered_map<std::string, long> field_val,
    const std::vector<long> &array_val)
{
    /// Initialize the Field Vales
    this->VFAT_ID = VFAT_ID;

    this->CFG_IREF = field_val["CFG_IREF"];
    this->CFG_HYST = field_val["CFG_HYST"];

    this->CFG_BIAS_CFD_DAC_2 = field_val["CFG_BIAS_CFD_DAC_2"];
    this->CFG_BIAS_CFD_DAC_1 = field_val["CFG_BIAS_CFD_DAC_1"];
    this->CFG_BIAS_PRE_I_BSF = field_val["CFG_BIAS_PRE_I_BSF"];

    this->CFG_BIAS_PRE_I_BIT = field_val["CFG_BIAS_PRE_I_BIT"];
    this->CFG_BIAS_PRE_I_BLCC = field_val["CFG_BIAS_PRE_I_BLCC"];
    this->CFG_BIAS_PRE_VREF = field_val["CFG_BIAS_PRE_VREF"];
    this->CFG_BIAS_SH_I_BFCAS = field_val["CFG_BIAS_SH_I_BFCAS"];
    this->CFG_BIAS_SH_I_BDIFF = field_val["CFG_BIAS_SH_I_BDIFF"];
    this->CFG_BIAS_SH_I_BFAMP = field_val["CFG_BIAS_SH_I_BFAMP"];
    this->CFG_BIAS_SD_I_BDIFF = field_val["CFG_BIAS_SD_I_BDIFF"];
    this->CFG_BIAS_SD_I_BSF = field_val["CFG_BIAS_SD_I_BSF"];
    this->CFG_BIAS_SD_I_BFCAS = field_val["CFG_BIAS_SD_I_BFCAS"];

    this->CFG_VREF_ADC = field_val["CFG_VREF_ADC"];
    this->CFG_MON_GAIN = field_val["CFG_MON_GAIN"];
    this->CFG_MONITOR_SELECT = field_val["CFG_MONITOR_SELECT"];

    this->CFG_RES_PRE = field_val["CFG_RES_PRE"];
    this->CFG_CAP_PRE = field_val["CFG_CAP_PRE"];

    this->CFG_FP_FE = field_val["CFG_FP_FE"];
    this->CFG_PT = field_val["CFG_PT"];

    this->CFG_SEL_POL = field_val["CFG_SEL_POL"];

    this->CFG_THR_ZCC_DAC = field_val["CFG_THR_ZCC_DAC"];

    this->CFG_THR_ARM_DAC = field_val["CFG_THR_ARM_DAC"];

    this->CFG_SEL_COMP_MODE = field_val["CFG_SEL_COMP_MODE"];
    this->CFG_FORCE_EN_ZCC = field_val["CFG_FORCE_EN_ZCC"];
    this->CFG_EN_HYST = field_val["CFG_EN_HYST"];
    this->CFG_FORCE_TH = field_val["CFG_FORCE_TH"];

    this->CFG_SYNC_LEVEL_MODE = field_val["CFG_SYNC_LEVEL_MODE"];

    this->CFG_PULSE_STRETCH = field_val["CFG_PULSE_STRETCH"];

    this->CFG_SELF_TRIGGER_MODE = field_val["CFG_SELF_TRIGGER_MODE"];
    this->CFG_DDR_TRIGGER_MODE = field_val["CFG_DDR_TRIGGER_MODE"];

    this->CFG_SPZS_SUMMARY_ONLY = field_val["CFG_SPZS_SUMMARY_ONLY"];
    this->CFG_SPZS_MAX_PARTITIONS = field_val["CFG_SPZS_MAX_PARTITIONS"];
    this->CFG_SPZS_ENABLE = field_val["CFG_SPZS_ENABLE"];
    this->CFG_SZP_ENABLE = field_val["CFG_SZP_ENABLE"];
    this->CFG_SZD_ENABLE = field_val["CFG_SZD_ENABLE"];

    this->CFG_TIME_TAG = field_val["CFG_TIME_TAG"];
    this->CFG_EC_BYTES = field_val["CFG_EC_BYTES"];
    this->CFG_BC_BYTES = field_val["CFG_BC_BYTES"];

    this->CFG_LATENCY = field_val["CFG_LATENCY"];

    this->CFG_CAL_MODE = field_val["CFG_CAL_MODE"];

    this->CFG_CAL_SEL_POL = field_val["CFG_CAL_SEL_POL"];

    this->CFG_CAL_DAC = field_val["CFG_CAL_DAC"];

    this->CFG_CAL_EXT = field_val["CFG_CAL_EXT"];
    this->CFG_CAL_PHI = field_val["CFG_CAL_PHI"];
    this->CFG_CAL_FS = field_val["CFG_CAL_FS"];
    this->CFG_CAL_DUR = field_val["CFG_CAL_DUR"];

    for (auto value = array_val.begin(); value != array_val.end(); ++value) {
        VFAT_CHANNELS_CHANNEL_0_to_128.push_back(*value);
    }

    // std::cout << "******" << array_val[0] << std::endl;
}

long vfat_data_table::insert_row(pqxx::connection* db_client)
{
    pqxx::work WW(*db_client);
    long id;

    /// Structure the PostgreSQL Statement to insert data
    std::string field_values = "", arrays = "'{";
    std::string sql = std::string("INSERT INTO ") + VFAT_DATA_TABLE + "(VFAT_ID,";
    for (int i = 0; i < 48; i++) {
        sql = sql + vfat_columns[i] + ", ";
    }
    sql = sql + "VFAT_CHANNELS_CHANNEL_0_to_128) VALUES (";

    /// Append the field values to the SQL Statement.
    field_values = std::to_string(this->VFAT_ID) + ", ";
    field_values = field_values + std::to_string(this->CFG_IREF) + ", " + std::to_string(this->CFG_HYST) + ", " + std::to_string(this->CFG_BIAS_CFD_DAC_2) + ", " + std::to_string(this->CFG_BIAS_CFD_DAC_1) + ", " + std::to_string(this->CFG_BIAS_PRE_I_BSF) + ", " + std::to_string(this->CFG_BIAS_PRE_I_BIT) + ", " + std::to_string(this->CFG_BIAS_PRE_I_BLCC) + ", " + std::to_string(this->CFG_BIAS_PRE_VREF) + ", " + std::to_string(this->CFG_BIAS_SH_I_BFCAS) + ", " + std::to_string(this->CFG_BIAS_SH_I_BDIFF) + ", " + std::to_string(this->CFG_BIAS_SH_I_BFAMP) + ", " + std::to_string(this->CFG_BIAS_SD_I_BDIFF) + ", " + std::to_string(this->CFG_BIAS_SD_I_BSF) + ", " + std::to_string(this->CFG_BIAS_SD_I_BFCAS) + ", " + std::to_string(this->CFG_VREF_ADC) + ", " + std::to_string(this->CFG_MON_GAIN) + ", " + std::to_string(this->CFG_MONITOR_SELECT) + ", " + std::to_string(this->CFG_RES_PRE) + ", " + std::to_string(this->CFG_CAP_PRE) + ", " + std::to_string(this->CFG_FP_FE) + ", " + std::to_string(this->CFG_PT) + ", " + std::to_string(this->CFG_SEL_POL) + ", " + std::to_string(this->CFG_THR_ZCC_DAC) + ", " + std::to_string(this->CFG_THR_ARM_DAC) + ", " + std::to_string(this->CFG_SEL_COMP_MODE) + ", " + std::to_string(this->CFG_FORCE_EN_ZCC) + ", " + std::to_string(this->CFG_EN_HYST) + ", " + std::to_string(this->CFG_FORCE_TH) + ", " + std::to_string(this->CFG_SYNC_LEVEL_MODE) + ", " + std::to_string(this->CFG_PULSE_STRETCH) + ", " + std::to_string(this->CFG_SELF_TRIGGER_MODE) + ", " + std::to_string(this->CFG_DDR_TRIGGER_MODE) + ", " + std::to_string(this->CFG_SPZS_SUMMARY_ONLY) + ", " + std::to_string(this->CFG_SPZS_MAX_PARTITIONS) + ", " + std::to_string(this->CFG_SPZS_ENABLE) + ", " + std::to_string(this->CFG_SZP_ENABLE) + ", " + std::to_string(this->CFG_SZD_ENABLE) + ", " + std::to_string(this->CFG_TIME_TAG) + ", " + std::to_string(this->CFG_EC_BYTES) + ", " + std::to_string(this->CFG_BC_BYTES) + ", " + std::to_string(this->CFG_LATENCY) + ", " + std::to_string(this->CFG_CAL_MODE) + ", " + std::to_string(this->CFG_CAL_SEL_POL) + ", " + std::to_string(this->CFG_CAL_DAC) + ", " + std::to_string(this->CFG_CAL_EXT) + ", " + std::to_string(this->CFG_CAL_PHI) + ", " + std::to_string(this->CFG_CAL_FS) + ", " + std::to_string(this->CFG_CAL_DUR) + ", ";

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
void vfat_data_table::insert_data(pqxx::connection* db_client,
    std::vector<vfat_data_table> data,
    long config_id)
{
    long id;
    /// Insert extracted data, Iterate the Object std::vector
    for (auto rowObject = data.begin(); rowObject != data.end(); ++rowObject) {
        /// Insert data of a particular object
        id = (*rowObject).insert_row(&(*db_client));

        // Insert into Index Table along with Config
        vfat_index_table obj;
        obj.initialize(config_id, id);
        obj.insert_row(&(*db_client));
    }
    std::cout << "Values inserted into table : " << VFAT_DATA_TABLE << std::endl;
}

std::vector<vfat_data_table> vfat_data_table::row_to_object(pqxx::result R)
{
    std::vector<vfat_data_table> query_results;

    for (auto const& row : R) {
        vfat_data_table obj;
        obj.id = row["ID"].as<long>(); // System Generated ID

        obj.VFAT_ID = row["VFAT_ID"].as<long>();

        // Actual VFAT Columns
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
        // long CFG_RES_PRE;// 2
        // long CFG_CAP_PRE;// 1
        //# Preamp gain - low
        // long CFG_RES_PRE;// 4
        // long CFG_CAP_PRE;// 3

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
        // std::vector<int> VFAT_CHANNELS_CHANNEL_0_to_128;// 0
        std::string str = row["VFAT_CHANNELS_CHANNEL_0_to_128"].c_str();
        str = str.substr(1, str.length());

        std::stringstream ss(str);
        while (ss.good()) {
            std::string sub;
            getline(ss, sub, ',');
            int d = stoi(sub);
            obj.VFAT_CHANNELS_CHANNEL_0_to_128.push_back(d);
        }

        // obj.display_row();
        query_results.push_back(obj);
    }
    // display_results(query_results);
    return query_results;
}

// Display a particular row of the table
void vfat_data_table::display_row()
{
    std::cout << std::left << std::setw(30) << "ID " << std::setw(2) << ":" << this->id
              << std::endl;
    std::cout << std::left << std::setw(30) << "VFAT_ID " << std::setw(2) << ":"
              << this->VFAT_ID << std::endl;
    std::cout << std::left << std::setw(30) << "CFG_IREF " << std::setw(2) << ":"
              << this->CFG_IREF << std::endl;
    std::cout << std::left << std::setw(30) << "CFG_HYST " << std::setw(2) << ":"
              << this->CFG_HYST << std::endl;

    std::cout << std::left << std::setw(30) << "CFG_BIAS_CFD_DAC_2 " << std::setw(2)
              << ":" << this->CFG_BIAS_CFD_DAC_2 << std::endl;
    std::cout << std::left << std::setw(30) << "CFG_BIAS_CFD_DAC_1 " << std::setw(2)
              << ":" << this->CFG_BIAS_CFD_DAC_1 << std::endl;
    std::cout << std::left << std::setw(30) << "CFG_BIAS_PRE_I_BSF " << std::setw(2)
              << ":" << this->CFG_BIAS_PRE_I_BSF << std::endl;

    std::cout << std::left << std::setw(30) << "CFG_BIAS_PRE_I_BIT " << std::setw(2)
              << ":" << this->CFG_BIAS_PRE_I_BIT << std::endl;
    std::cout << std::left << std::setw(30) << "CFG_BIAS_PRE_I_BLCC " << std::setw(2)
              << ":" << this->CFG_BIAS_PRE_I_BLCC << std::endl;
    std::cout << std::left << std::setw(30) << "CFG_BIAS_PRE_VREF " << std::setw(2)
              << ":" << this->CFG_BIAS_PRE_VREF << std::endl;
    std::cout << std::left << std::setw(30) << "CFG_BIAS_SH_I_BFCAS " << std::setw(2)
              << ":" << this->CFG_BIAS_SH_I_BFCAS << std::endl;
    std::cout << std::left << std::setw(30) << "CFG_BIAS_SH_I_BDIFF " << std::setw(2)
              << ":" << this->CFG_BIAS_SH_I_BDIFF << std::endl;
    std::cout << std::left << std::setw(30) << "CFG_BIAS_SH_I_BFAMP " << std::setw(2)
              << ":" << this->CFG_BIAS_SH_I_BFAMP << std::endl;
    std::cout << std::left << std::setw(30) << "CFG_BIAS_SD_I_BDIFF " << std::setw(2)
              << ":" << this->CFG_BIAS_SD_I_BDIFF << std::endl;
    std::cout << std::left << std::setw(30) << "CFG_BIAS_SD_I_BSF " << std::setw(2)
              << ":" << this->CFG_BIAS_SD_I_BSF << std::endl;
    std::cout << std::left << std::setw(30) << "CFG_BIAS_SD_I_BFCAS " << std::setw(2)
              << ":" << this->CFG_BIAS_SD_I_BFCAS << std::endl;

    std::cout << std::left << std::setw(30) << "CFG_VREF_ADC " << std::setw(2) << ":"
              << this->CFG_VREF_ADC << std::endl;
    std::cout << std::left << std::setw(30) << "CFG_MON_GAIN " << std::setw(2) << ":"
              << this->CFG_MON_GAIN << std::endl;
    std::cout << std::left << std::setw(30) << "CFG_MONITOR_SELECT " << std::setw(2)
              << ":" << this->CFG_MONITOR_SELECT << std::endl;

    std::cout << std::left << std::setw(30) << "CFG_RES_PRE " << std::setw(2) << ":"
              << this->CFG_RES_PRE << std::endl;
    std::cout << std::left << std::setw(30) << "CFG_CAP_PRE " << std::setw(2) << ":"
              << this->CFG_CAP_PRE << std::endl;

    std::cout << std::left << std::setw(30) << "CFG_FP_FE " << std::setw(2) << ":"
              << this->CFG_FP_FE << std::endl;
    std::cout << std::left << std::setw(30) << "CFG_PT " << std::setw(2) << ":"
              << this->CFG_PT << std::endl;

    std::cout << std::left << std::setw(30) << "CFG_SEL_POL " << std::setw(2) << ":"
              << this->CFG_SEL_POL << std::endl;

    std::cout << std::left << std::setw(30) << "CFG_THR_ZCC_DAC " << std::setw(2)
              << ":" << this->CFG_THR_ZCC_DAC << std::endl;

    std::cout << std::left << std::setw(30) << "CFG_THR_ARM_DAC " << std::setw(2)
              << ":" << this->CFG_THR_ARM_DAC << std::endl;

    std::cout << std::left << std::setw(30) << "CFG_SEL_COMP_MODE " << std::setw(2)
              << ":" << this->CFG_SEL_COMP_MODE << std::endl;
    std::cout << std::left << std::setw(30) << "CFG_FORCE_EN_ZCC " << std::setw(2)
              << ":" << this->CFG_FORCE_EN_ZCC << std::endl;
    std::cout << std::left << std::setw(30) << "CFG_EN_HYST " << std::setw(2) << ":"
              << this->CFG_EN_HYST << std::endl;
    std::cout << std::left << std::setw(30) << "CFG_FORCE_TH " << std::setw(2) << ":"
              << this->CFG_FORCE_TH << std::endl;

    std::cout << std::left << std::setw(30) << "CFG_SYNC_LEVEL_MODE " << std::setw(2)
              << ":" << this->CFG_SYNC_LEVEL_MODE << std::endl;

    std::cout << std::left << std::setw(30) << "CFG_PULSE_STRETCH " << std::setw(2)
              << ":" << this->CFG_PULSE_STRETCH << std::endl;

    std::cout << std::left << std::setw(30) << "CFG_SELF_TRIGGER_MODE " << std::setw(2)
              << ":" << this->CFG_SELF_TRIGGER_MODE << std::endl;
    std::cout << std::left << std::setw(30) << "CFG_DDR_TRIGGER_MODE " << std::setw(2)
              << ":" << this->CFG_DDR_TRIGGER_MODE << std::endl;

    std::cout << std::left << std::setw(30) << "CFG_SPZS_SUMMARY_ONLY " << std::setw(2)
              << ":" << this->CFG_SPZS_SUMMARY_ONLY << std::endl;
    std::cout << std::left << std::setw(30) << "CFG_SPZS_MAX_PARTITIONS "
              << std::setw(2) << ":" << this->CFG_SPZS_MAX_PARTITIONS << std::endl;
    std::cout << std::left << std::setw(30) << "CFG_SPZS_ENABLE " << std::setw(2)
              << ":" << this->CFG_SPZS_ENABLE << std::endl;
    std::cout << std::left << std::setw(30) << "CFG_SZP_ENABLE " << std::setw(2) << ":"
              << this->CFG_SZP_ENABLE << std::endl;
    std::cout << std::left << std::setw(30) << "CFG_SZD_ENABLE " << std::setw(2) << ":"
              << this->CFG_SZD_ENABLE << std::endl;

    std::cout << std::left << std::setw(30) << "CFG_TIME_TAG " << std::setw(2) << ":"
              << this->CFG_TIME_TAG << std::endl;
    std::cout << std::left << std::setw(30) << "CFG_EC_BYTES " << std::setw(2) << ":"
              << this->CFG_EC_BYTES << std::endl;
    std::cout << std::left << std::setw(30) << "CFG_BC_BYTES " << std::setw(2) << ":"
              << this->CFG_BC_BYTES << std::endl;

    std::cout << std::left << std::setw(30) << "CFG_LATENCY " << std::setw(2) << ":"
              << this->CFG_LATENCY << std::endl;

    std::cout << std::left << std::setw(30) << "CFG_CAL_MODE " << std::setw(2) << ":"
              << this->CFG_CAL_MODE << std::endl;

    std::cout << std::left << std::setw(30) << "CFG_CAL_SEL_POL " << std::setw(2)
              << ":" << this->CFG_CAL_SEL_POL << std::endl;

    std::cout << std::left << std::setw(30) << "CFG_CAL_DAC " << std::setw(2) << ":"
              << this->CFG_CAL_DAC << std::endl;

    std::cout << std::left << std::setw(30) << "CFG_CAL_EXT " << std::setw(2) << ":"
              << this->CFG_CAL_EXT << std::endl;
    std::cout << std::left << std::setw(30) << "CFG_CAL_PHI " << std::setw(2) << ":"
              << this->CFG_CAL_PHI << std::endl;
    std::cout << std::left << std::setw(30) << "CFG_CAL_FS " << std::setw(2) << ":"
              << this->CFG_CAL_FS << std::endl;
    std::cout << std::left << std::setw(30) << "CFG_CAL_DUR " << std::setw(2) << ":"
              << this->CFG_CAL_DUR << std::endl;

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
void vfat_data_table::display_results(std::vector<vfat_data_table>& data)
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

int vfat_data_table::compareSettings(const vfat_data_table& ob1,
    const vfat_data_table& ob2)
{
    // compares all fields of two objects and returns value 1 if unequal, 0 if
    // equal

    int flag = 0;
    if (ob1.CFG_IREF != ob2.CFG_IREF || ob1.CFG_HYST != ob2.CFG_HYST || ob1.CFG_BIAS_CFD_DAC_2 != ob2.CFG_BIAS_CFD_DAC_2 || ob1.CFG_BIAS_CFD_DAC_1 != ob2.CFG_BIAS_CFD_DAC_1 || ob1.CFG_BIAS_PRE_I_BSF != ob2.CFG_BIAS_PRE_I_BSF || ob1.CFG_BIAS_PRE_I_BIT != ob2.CFG_BIAS_PRE_I_BIT || ob1.CFG_BIAS_PRE_I_BLCC != ob2.CFG_BIAS_PRE_I_BLCC || ob1.CFG_BIAS_PRE_VREF != ob2.CFG_BIAS_PRE_VREF || ob1.CFG_BIAS_SH_I_BFCAS != ob2.CFG_BIAS_SH_I_BFCAS || ob1.CFG_BIAS_SH_I_BDIFF != ob2.CFG_BIAS_SH_I_BDIFF || ob1.CFG_BIAS_SH_I_BFAMP != ob2.CFG_BIAS_SH_I_BFAMP || ob1.CFG_BIAS_SD_I_BDIFF != ob2.CFG_BIAS_SD_I_BDIFF || ob1.CFG_BIAS_SD_I_BSF != ob2.CFG_BIAS_SD_I_BSF || ob1.CFG_BIAS_SD_I_BFCAS != ob2.CFG_BIAS_SD_I_BFCAS || ob1.CFG_VREF_ADC != ob2.CFG_VREF_ADC || ob1.CFG_MON_GAIN != ob2.CFG_MON_GAIN || ob1.CFG_MONITOR_SELECT != ob2.CFG_MONITOR_SELECT || ob1.CFG_RES_PRE != ob2.CFG_RES_PRE || ob1.CFG_CAP_PRE != ob2.CFG_CAP_PRE || ob1.CFG_FP_FE != ob2.CFG_FP_FE || ob1.CFG_PT != ob2.CFG_PT || ob1.CFG_SEL_POL != ob2.CFG_SEL_POL || ob1.CFG_THR_ZCC_DAC != ob2.CFG_THR_ZCC_DAC || ob1.CFG_THR_ARM_DAC != ob2.CFG_THR_ARM_DAC || ob1.CFG_SEL_COMP_MODE != ob2.CFG_SEL_COMP_MODE || ob1.CFG_FORCE_EN_ZCC != ob2.CFG_FORCE_EN_ZCC || ob1.CFG_EN_HYST != ob2.CFG_EN_HYST || ob1.CFG_FORCE_TH != ob2.CFG_FORCE_TH || ob1.CFG_SYNC_LEVEL_MODE != ob2.CFG_SYNC_LEVEL_MODE || ob1.CFG_PULSE_STRETCH != ob2.CFG_PULSE_STRETCH || ob1.CFG_SELF_TRIGGER_MODE != ob2.CFG_SELF_TRIGGER_MODE || ob1.CFG_DDR_TRIGGER_MODE != ob2.CFG_DDR_TRIGGER_MODE || ob1.CFG_SPZS_SUMMARY_ONLY != ob2.CFG_SPZS_SUMMARY_ONLY || ob1.CFG_SPZS_MAX_PARTITIONS != ob2.CFG_SPZS_MAX_PARTITIONS || ob1.CFG_SPZS_ENABLE != ob2.CFG_SPZS_ENABLE || ob1.CFG_SZP_ENABLE != ob2.CFG_SZP_ENABLE || ob1.CFG_SZD_ENABLE != ob2.CFG_SZD_ENABLE || ob1.CFG_TIME_TAG != ob2.CFG_TIME_TAG || ob1.CFG_EC_BYTES != ob2.CFG_EC_BYTES || ob1.CFG_BC_BYTES != ob2.CFG_BC_BYTES || ob1.CFG_LATENCY != ob2.CFG_LATENCY || ob1.CFG_CAL_MODE != ob2.CFG_CAL_MODE || ob1.CFG_CAL_SEL_POL != ob2.CFG_CAL_SEL_POL || ob1.CFG_CAL_DAC != ob2.CFG_CAL_DAC || ob1.CFG_CAL_EXT != ob2.CFG_CAL_EXT || ob1.CFG_CAL_PHI != ob2.CFG_CAL_PHI || ob1.CFG_CAL_FS != ob2.CFG_CAL_FS || ob1.CFG_CAL_DUR != ob2.CFG_CAL_DUR) {
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

std::vector<vfat_data_table> vfat_data_table::getNewSettings(
    pqxx::connection* db_client, std::vector<vfat_data_table> vfat_ob,
    std::vector<vfat_data_table> ref_ob, long config_id)
{
    std::vector<vfat_data_table> insert_vfats;

    for (auto rowObject = vfat_ob.begin(); rowObject != vfat_ob.end();
         ++rowObject) {
        for (auto refObject = ref_ob.begin(); refObject != ref_ob.end();
             ++refObject) {

            if ((*rowObject).VFAT_ID == (*refObject).VFAT_ID) {
                if (compareSettings((*rowObject), (*refObject)) == 1)
                    insert_vfats.push_back((*rowObject));
                else {
                    vfat_index_table obj;
                    obj.initialize(config_id, (*refObject).get_id());
                    obj.insert_row(&(*db_client));
                }
            }
        }
    }
    std::cout << "ALL References Resolved !" << std::endl
              << std::endl;
    return insert_vfats;
}