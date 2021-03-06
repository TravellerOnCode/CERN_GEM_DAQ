/// Include the Header File
#include "../interface/VFAT_Data_Table.h"

void VFAT_Data_Table::create_table(connection *dbClient) {
  work WW(*dbClient);
  /// Structure the PostgreSQL Statement to create a table
  string query = "CREATE TABLE IF NOT EXISTS " + to_string(VFAT_DATA_TABLE) +
                 "(ID SERIAL PRIMARY KEY, VFAT_ID bigint,";
  /// Append the VFAT Column Names
  for (int i = 0; i < 48; i++)
    query = query + vfat_columns[i] + " bigint" + ", ";
  query = query + "VFAT_CHANNELS_CHANNEL_0_to_128" + " integer[]);";

  // cout << "Executed Query : " << endl << query << endl;
  /// Execute the PostgreSQL Statement and create the table
  WW.exec(query);
  cout << "Table Created -> " << to_string(VFAT_DATA_TABLE) << endl;
  /// Commit Work to the database
  WW.commit();
}

long VFAT_Data_Table::get_id() {
  /// Access the id
  return this->id;
}

void VFAT_Data_Table::initialize(long VFAT_ID,
                                 unordered_map<string, long> field_val,
                                 vector<long> array_val) {
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

  for (int i = 0; i < array_val.size(); i++) {
    VFAT_CHANNELS_CHANNEL_0_to_128.push_back(array_val[i]);
  }
  // cout << "******" << array_val[0] << endl;
}

long VFAT_Data_Table::insert_row(connection *dbClient) {
  work WW(*dbClient);
  long id;

  /// Structure the PostgreSQL Statement to insert data
  string field_values = "", arrays = "'{";
  string sql = "INSERT INTO " + to_string(VFAT_DATA_TABLE) + "(VFAT_ID,";
  for (int i = 0; i < 48; i++) {
    sql = sql + vfat_columns[i] + ", ";
  }
  sql = sql + "VFAT_CHANNELS_CHANNEL_0_to_128) VALUES (";

  /// Append the field values to the SQL Statement.
  field_values = to_string(this->VFAT_ID) + ", ";
  field_values =
      field_values + to_string(this->CFG_IREF) + ", " +
      to_string(this->CFG_HYST) + ", " + to_string(this->CFG_BIAS_CFD_DAC_2) +
      ", " + to_string(this->CFG_BIAS_CFD_DAC_1) + ", " +
      to_string(this->CFG_BIAS_PRE_I_BSF) + ", " +
      to_string(this->CFG_BIAS_PRE_I_BIT) + ", " +
      to_string(this->CFG_BIAS_PRE_I_BLCC) + ", " +
      to_string(this->CFG_BIAS_PRE_VREF) + ", " +
      to_string(this->CFG_BIAS_SH_I_BFCAS) + ", " +
      to_string(this->CFG_BIAS_SH_I_BDIFF) + ", " +
      to_string(this->CFG_BIAS_SH_I_BFAMP) + ", " +
      to_string(this->CFG_BIAS_SD_I_BDIFF) + ", " +
      to_string(this->CFG_BIAS_SD_I_BSF) + ", " +
      to_string(this->CFG_BIAS_SD_I_BFCAS) + ", " +
      to_string(this->CFG_VREF_ADC) + ", " + to_string(this->CFG_MON_GAIN) +
      ", " + to_string(this->CFG_MONITOR_SELECT) + ", " +
      to_string(this->CFG_RES_PRE) + ", " + to_string(this->CFG_CAP_PRE) +
      ", " + to_string(this->CFG_FP_FE) + ", " + to_string(this->CFG_PT) +
      ", " + to_string(this->CFG_SEL_POL) + ", " +
      to_string(this->CFG_THR_ZCC_DAC) + ", " +
      to_string(this->CFG_THR_ARM_DAC) + ", " +
      to_string(this->CFG_SEL_COMP_MODE) + ", " +
      to_string(this->CFG_FORCE_EN_ZCC) + ", " + to_string(this->CFG_EN_HYST) +
      ", " + to_string(this->CFG_FORCE_TH) + ", " +
      to_string(this->CFG_SYNC_LEVEL_MODE) + ", " +
      to_string(this->CFG_PULSE_STRETCH) + ", " +
      to_string(this->CFG_SELF_TRIGGER_MODE) + ", " +
      to_string(this->CFG_DDR_TRIGGER_MODE) + ", " +
      to_string(this->CFG_SPZS_SUMMARY_ONLY) + ", " +
      to_string(this->CFG_SPZS_MAX_PARTITIONS) + ", " +
      to_string(this->CFG_SPZS_ENABLE) + ", " +
      to_string(this->CFG_SZP_ENABLE) + ", " + to_string(this->CFG_SZD_ENABLE) +
      ", " + to_string(this->CFG_TIME_TAG) + ", " +
      to_string(this->CFG_EC_BYTES) + ", " + to_string(this->CFG_BC_BYTES) +
      ", " + to_string(this->CFG_LATENCY) + ", " +
      to_string(this->CFG_CAL_MODE) + ", " + to_string(this->CFG_CAL_SEL_POL) +
      ", " + to_string(this->CFG_CAL_DAC) + ", " +
      to_string(this->CFG_CAL_EXT) + ", " + to_string(this->CFG_CAL_PHI) +
      ", " + to_string(this->CFG_CAL_FS) + ", " + to_string(this->CFG_CAL_DUR) +
      ", ";

  for (int i = 0; i < 127; i++) {
    arrays = arrays + to_string(this->VFAT_CHANNELS_CHANNEL_0_to_128[i]) + ", ";
  }

  /// PostgreSQL Insert Statement
  sql = sql + field_values + arrays +
        to_string(this->VFAT_CHANNELS_CHANNEL_0_to_128[127]) +
        "}') RETURNING ID;";

  /// Execute the PostgreSQL Statement and insert data into the table.
  /// Insertion returns a system generated ID into R
  result R = WW.exec(sql);
  /// Extracts the ID from the response and store in id.
  for (auto const &row : R)
    id = row["ID"].as<long>();

  /// Commit Work to the database
  WW.commit();

  /// Return the id
  return id;
}

// This should accept only those Objects that are unique
void VFAT_Data_Table::insert_data(connection *dbClient,
                                  vector<VFAT_Data_Table> data,
                                  long config_id) {
  int i;
  long id;
  /// Insert extracted data, Iterate the Object vector
  for (auto rowObject = data.begin(); rowObject != data.end(); ++rowObject) {
    /// Insert data of a particular object
    id = (*rowObject).insert_row(&(*dbClient));

    // Insert into Index Table along with Config
    VFAT_Index_Table obj;
    obj.initialize(config_id, id);
    obj.insert_row(&(*dbClient));
  }
  cout << "Values inserted into table : " << VFAT_DATA_TABLE << endl;
}

vector<VFAT_Data_Table> VFAT_Data_Table::row_to_object(result R) {
  vector<VFAT_Data_Table> query_results;

  for (auto const &row : R) {
    VFAT_Data_Table obj;
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
    // vector<int> VFAT_CHANNELS_CHANNEL_0_to_128;// 0
    string str = row["VFAT_CHANNELS_CHANNEL_0_to_128"].c_str();
    str = str.substr(1, str.length());

    stringstream ss(str);
    while (ss.good()) {
      string sub;
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
void VFAT_Data_Table::display_row() {
  cout << std::left << std::setw(30) << "ID " << std::setw(2) << ":" << this->id
       << endl;
  cout << std::left << std::setw(30) << "VFAT_ID " << std::setw(2) << ":"
       << this->VFAT_ID << endl;
  cout << std::left << std::setw(30) << "CFG_IREF " << std::setw(2) << ":"
       << this->CFG_IREF << endl;
  cout << std::left << std::setw(30) << "CFG_HYST " << std::setw(2) << ":"
       << this->CFG_HYST << endl;

  cout << std::left << std::setw(30) << "CFG_BIAS_CFD_DAC_2 " << std::setw(2)
       << ":" << this->CFG_BIAS_CFD_DAC_2 << endl;
  cout << std::left << std::setw(30) << "CFG_BIAS_CFD_DAC_1 " << std::setw(2)
       << ":" << this->CFG_BIAS_CFD_DAC_1 << endl;
  cout << std::left << std::setw(30) << "CFG_BIAS_PRE_I_BSF " << std::setw(2)
       << ":" << this->CFG_BIAS_PRE_I_BSF << endl;

  cout << std::left << std::setw(30) << "CFG_BIAS_PRE_I_BIT " << std::setw(2)
       << ":" << this->CFG_BIAS_PRE_I_BIT << endl;
  cout << std::left << std::setw(30) << "CFG_BIAS_PRE_I_BLCC " << std::setw(2)
       << ":" << this->CFG_BIAS_PRE_I_BLCC << endl;
  cout << std::left << std::setw(30) << "CFG_BIAS_PRE_VREF " << std::setw(2)
       << ":" << this->CFG_BIAS_PRE_VREF << endl;
  cout << std::left << std::setw(30) << "CFG_BIAS_SH_I_BFCAS " << std::setw(2)
       << ":" << this->CFG_BIAS_SH_I_BFCAS << endl;
  cout << std::left << std::setw(30) << "CFG_BIAS_SH_I_BDIFF " << std::setw(2)
       << ":" << this->CFG_BIAS_SH_I_BDIFF << endl;
  cout << std::left << std::setw(30) << "CFG_BIAS_SH_I_BFAMP " << std::setw(2)
       << ":" << this->CFG_BIAS_SH_I_BFAMP << endl;
  cout << std::left << std::setw(30) << "CFG_BIAS_SD_I_BDIFF " << std::setw(2)
       << ":" << this->CFG_BIAS_SD_I_BDIFF << endl;
  cout << std::left << std::setw(30) << "CFG_BIAS_SD_I_BSF " << std::setw(2)
       << ":" << this->CFG_BIAS_SD_I_BSF << endl;
  cout << std::left << std::setw(30) << "CFG_BIAS_SD_I_BFCAS " << std::setw(2)
       << ":" << this->CFG_BIAS_SD_I_BFCAS << endl;

  cout << std::left << std::setw(30) << "CFG_VREF_ADC " << std::setw(2) << ":"
       << this->CFG_VREF_ADC << endl;
  cout << std::left << std::setw(30) << "CFG_MON_GAIN " << std::setw(2) << ":"
       << this->CFG_MON_GAIN << endl;
  cout << std::left << std::setw(30) << "CFG_MONITOR_SELECT " << std::setw(2)
       << ":" << this->CFG_MONITOR_SELECT << endl;

  cout << std::left << std::setw(30) << "CFG_RES_PRE " << std::setw(2) << ":"
       << this->CFG_RES_PRE << endl;
  cout << std::left << std::setw(30) << "CFG_CAP_PRE " << std::setw(2) << ":"
       << this->CFG_CAP_PRE << endl;

  cout << std::left << std::setw(30) << "CFG_FP_FE " << std::setw(2) << ":"
       << this->CFG_FP_FE << endl;
  cout << std::left << std::setw(30) << "CFG_PT " << std::setw(2) << ":"
       << this->CFG_PT << endl;

  cout << std::left << std::setw(30) << "CFG_SEL_POL " << std::setw(2) << ":"
       << this->CFG_SEL_POL << endl;

  cout << std::left << std::setw(30) << "CFG_THR_ZCC_DAC " << std::setw(2)
       << ":" << this->CFG_THR_ZCC_DAC << endl;

  cout << std::left << std::setw(30) << "CFG_THR_ARM_DAC " << std::setw(2)
       << ":" << this->CFG_THR_ARM_DAC << endl;

  cout << std::left << std::setw(30) << "CFG_SEL_COMP_MODE " << std::setw(2)
       << ":" << this->CFG_SEL_COMP_MODE << endl;
  cout << std::left << std::setw(30) << "CFG_FORCE_EN_ZCC " << std::setw(2)
       << ":" << this->CFG_FORCE_EN_ZCC << endl;
  cout << std::left << std::setw(30) << "CFG_EN_HYST " << std::setw(2) << ":"
       << this->CFG_EN_HYST << endl;
  cout << std::left << std::setw(30) << "CFG_FORCE_TH " << std::setw(2) << ":"
       << this->CFG_FORCE_TH << endl;

  cout << std::left << std::setw(30) << "CFG_SYNC_LEVEL_MODE " << std::setw(2)
       << ":" << this->CFG_SYNC_LEVEL_MODE << endl;

  cout << std::left << std::setw(30) << "CFG_PULSE_STRETCH " << std::setw(2)
       << ":" << this->CFG_PULSE_STRETCH << endl;

  cout << std::left << std::setw(30) << "CFG_SELF_TRIGGER_MODE " << std::setw(2)
       << ":" << this->CFG_SELF_TRIGGER_MODE << endl;
  cout << std::left << std::setw(30) << "CFG_DDR_TRIGGER_MODE " << std::setw(2)
       << ":" << this->CFG_DDR_TRIGGER_MODE << endl;

  cout << std::left << std::setw(30) << "CFG_SPZS_SUMMARY_ONLY " << std::setw(2)
       << ":" << this->CFG_SPZS_SUMMARY_ONLY << endl;
  cout << std::left << std::setw(30) << "CFG_SPZS_MAX_PARTITIONS "
       << std::setw(2) << ":" << this->CFG_SPZS_MAX_PARTITIONS << endl;
  cout << std::left << std::setw(30) << "CFG_SPZS_ENABLE " << std::setw(2)
       << ":" << this->CFG_SPZS_ENABLE << endl;
  cout << std::left << std::setw(30) << "CFG_SZP_ENABLE " << std::setw(2) << ":"
       << this->CFG_SZP_ENABLE << endl;
  cout << std::left << std::setw(30) << "CFG_SZD_ENABLE " << std::setw(2) << ":"
       << this->CFG_SZD_ENABLE << endl;

  cout << std::left << std::setw(30) << "CFG_TIME_TAG " << std::setw(2) << ":"
       << this->CFG_TIME_TAG << endl;
  cout << std::left << std::setw(30) << "CFG_EC_BYTES " << std::setw(2) << ":"
       << this->CFG_EC_BYTES << endl;
  cout << std::left << std::setw(30) << "CFG_BC_BYTES " << std::setw(2) << ":"
       << this->CFG_BC_BYTES << endl;

  cout << std::left << std::setw(30) << "CFG_LATENCY " << std::setw(2) << ":"
       << this->CFG_LATENCY << endl;

  cout << std::left << std::setw(30) << "CFG_CAL_MODE " << std::setw(2) << ":"
       << this->CFG_CAL_MODE << endl;

  cout << std::left << std::setw(30) << "CFG_CAL_SEL_POL " << std::setw(2)
       << ":" << this->CFG_CAL_SEL_POL << endl;

  cout << std::left << std::setw(30) << "CFG_CAL_DAC " << std::setw(2) << ":"
       << this->CFG_CAL_DAC << endl;

  cout << std::left << std::setw(30) << "CFG_CAL_EXT " << std::setw(2) << ":"
       << this->CFG_CAL_EXT << endl;
  cout << std::left << std::setw(30) << "CFG_CAL_PHI " << std::setw(2) << ":"
       << this->CFG_CAL_PHI << endl;
  cout << std::left << std::setw(30) << "CFG_CAL_FS " << std::setw(2) << ":"
       << this->CFG_CAL_FS << endl;
  cout << std::left << std::setw(30) << "CFG_CAL_DUR " << std::setw(2) << ":"
       << this->CFG_CAL_DUR << endl;

  cout << std::left << std::setw(30) << "VFAT_CHANNELS_CHANNEL_0_to_128 "
       << std::setw(2) << ":"
       << "[ ";
  for (int i = 0; i < 128 - 1; i++) {
    cout << this->VFAT_CHANNELS_CHANNEL_0_to_128[i] << ", ";
  }
  cout << this->VFAT_CHANNELS_CHANNEL_0_to_128[127] << "] " << endl << endl;
}

// Display results
void VFAT_Data_Table::display_results(vector<VFAT_Data_Table> &data) {
  int i = 0;
  for (auto rowObject = data.begin(); rowObject != data.end(); ++rowObject) {
    /// Insert data of a particular object
    (*rowObject).display_row();
    cout << "------" << endl << endl;
    i++;
    if (i == 10)
      break;
  }
}

int VFAT_Data_Table::compareSettings(const VFAT_Data_Table &ob1,
                                     const VFAT_Data_Table &ob2) {
  // compares all fields of two objects and returns value 1 if unequal, 0 if
  // equal

  int flag = 0;
  if (ob1.CFG_IREF != ob2.CFG_IREF || ob1.CFG_HYST != ob2.CFG_HYST ||
      ob1.CFG_BIAS_CFD_DAC_2 != ob2.CFG_BIAS_CFD_DAC_2 ||
      ob1.CFG_BIAS_CFD_DAC_1 != ob2.CFG_BIAS_CFD_DAC_1 ||
      ob1.CFG_BIAS_PRE_I_BSF != ob2.CFG_BIAS_PRE_I_BSF ||
      ob1.CFG_BIAS_PRE_I_BIT != ob2.CFG_BIAS_PRE_I_BIT ||
      ob1.CFG_BIAS_PRE_I_BLCC != ob2.CFG_BIAS_PRE_I_BLCC ||
      ob1.CFG_BIAS_PRE_VREF != ob2.CFG_BIAS_PRE_VREF ||
      ob1.CFG_BIAS_SH_I_BFCAS != ob2.CFG_BIAS_SH_I_BFCAS ||
      ob1.CFG_BIAS_SH_I_BDIFF != ob2.CFG_BIAS_SH_I_BDIFF ||
      ob1.CFG_BIAS_SH_I_BFAMP != ob2.CFG_BIAS_SH_I_BFAMP ||
      ob1.CFG_BIAS_SD_I_BDIFF != ob2.CFG_BIAS_SD_I_BDIFF ||
      ob1.CFG_BIAS_SD_I_BSF != ob2.CFG_BIAS_SD_I_BSF ||
      ob1.CFG_BIAS_SD_I_BFCAS != ob2.CFG_BIAS_SD_I_BFCAS ||
      ob1.CFG_VREF_ADC != ob2.CFG_VREF_ADC ||
      ob1.CFG_MON_GAIN != ob2.CFG_MON_GAIN ||
      ob1.CFG_MONITOR_SELECT != ob2.CFG_MONITOR_SELECT ||
      ob1.CFG_RES_PRE != ob2.CFG_RES_PRE ||
      ob1.CFG_CAP_PRE != ob2.CFG_CAP_PRE || ob1.CFG_FP_FE != ob2.CFG_FP_FE ||
      ob1.CFG_PT != ob2.CFG_PT || ob1.CFG_SEL_POL != ob2.CFG_SEL_POL ||
      ob1.CFG_THR_ZCC_DAC != ob2.CFG_THR_ZCC_DAC ||
      ob1.CFG_THR_ARM_DAC != ob2.CFG_THR_ARM_DAC ||
      ob1.CFG_SEL_COMP_MODE != ob2.CFG_SEL_COMP_MODE ||
      ob1.CFG_FORCE_EN_ZCC != ob2.CFG_FORCE_EN_ZCC ||
      ob1.CFG_EN_HYST != ob2.CFG_EN_HYST ||
      ob1.CFG_FORCE_TH != ob2.CFG_FORCE_TH ||
      ob1.CFG_SYNC_LEVEL_MODE != ob2.CFG_SYNC_LEVEL_MODE ||
      ob1.CFG_PULSE_STRETCH != ob2.CFG_PULSE_STRETCH ||
      ob1.CFG_SELF_TRIGGER_MODE != ob2.CFG_SELF_TRIGGER_MODE ||
      ob1.CFG_DDR_TRIGGER_MODE != ob2.CFG_DDR_TRIGGER_MODE ||
      ob1.CFG_SPZS_SUMMARY_ONLY != ob2.CFG_SPZS_SUMMARY_ONLY ||
      ob1.CFG_SPZS_MAX_PARTITIONS != ob2.CFG_SPZS_MAX_PARTITIONS ||
      ob1.CFG_SPZS_ENABLE != ob2.CFG_SPZS_ENABLE ||
      ob1.CFG_SZP_ENABLE != ob2.CFG_SZP_ENABLE ||
      ob1.CFG_SZD_ENABLE != ob2.CFG_SZD_ENABLE ||
      ob1.CFG_TIME_TAG != ob2.CFG_TIME_TAG ||
      ob1.CFG_EC_BYTES != ob2.CFG_EC_BYTES ||
      ob1.CFG_BC_BYTES != ob2.CFG_BC_BYTES ||
      ob1.CFG_LATENCY != ob2.CFG_LATENCY ||
      ob1.CFG_CAL_MODE != ob2.CFG_CAL_MODE ||
      ob1.CFG_CAL_SEL_POL != ob2.CFG_CAL_SEL_POL ||
      ob1.CFG_CAL_DAC != ob2.CFG_CAL_DAC ||
      ob1.CFG_CAL_EXT != ob2.CFG_CAL_EXT ||
      ob1.CFG_CAL_PHI != ob2.CFG_CAL_PHI || ob1.CFG_CAL_FS != ob2.CFG_CAL_FS ||
      ob1.CFG_CAL_DUR != ob2.CFG_CAL_DUR) {
    flag = 1;
  }

  if (flag != 0)
    return 1;
  else {
    if (!(ob1.VFAT_CHANNELS_CHANNEL_0_to_128 ==
          ob2.VFAT_CHANNELS_CHANNEL_0_to_128))
      return 1;
    else
      return 0;
  }
}

vector<VFAT_Data_Table> VFAT_Data_Table::getNewSettings(
    connection *dbClient, vector<VFAT_Data_Table> vfat_ob,
    vector<VFAT_Data_Table> ref_ob, long config_id) {
  vector<VFAT_Data_Table> insert_vfats;

  for (auto rowObject = vfat_ob.begin(); rowObject != vfat_ob.end();
       ++rowObject) {
    for (auto refObject = ref_ob.begin(); refObject != ref_ob.end();
         ++refObject) {

      if ((*rowObject).VFAT_ID == (*refObject).VFAT_ID) {
        if (compareSettings((*rowObject), (*refObject)) == 1)
          insert_vfats.push_back((*rowObject));
        else {
          VFAT_Index_Table obj;
          obj.initialize(config_id, (*refObject).get_id());
          obj.insert_row(&(*dbClient));
        }
      }
    }
  }
  cout << "ALL References Resolved !" << endl << endl;
  return insert_vfats;
}