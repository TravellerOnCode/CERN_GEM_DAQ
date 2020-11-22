/*

CLASSES:
        1. component_name //each component type will have a class of their own
                    Like:
                        vfat class will have vfat columns as their class members

        2. postgre_database  //this will contain functions that will interact with the components

NOTE: CURRENTLY WE ARE UNABLE TO RESOLVE HOW TO WORK WITH  ARRAY VALUES WITH LIBPQXX SO WE ARE USING
EMPLOYEE DATABASE EXAMPLE TO EXPLAIN THE WORKFLOW & CODE


Class: component_name{

    Class variables:
        * int ID,SALARY,AGE;
        * string NAME,ADDRESS;

    Functions:
        * display_row() // displays the values of class vars
        * initialize( ...... ) //takes values and initializes the class vars
        * insert_row() //takes an object and inserts the values into the database
        * insert_data() //takes a vector of objects and inserts the values into the database
        * display_results() //displays the contents of the vector of objects
        * row_to_object() //takes the query response generated by query_response() function and converts
                              it into an vector of objects
}

Class:

    Functions:
        * query_response() //Accepts a query and returns the raw reponse which can be processed
                              by other functions from any component class


*/


//-----------

#include <iostream>
#include <pqxx/pqxx> 
#include <string>
//#include <nlohmann/json.hpp>

//------------

using namespace std;
using namespace pqxx;

string DBNAME = "gemdaq";
string USER = "postgres";
string PASSWORD = "linuxos16";

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

//--------------

class component_name
{
    public:

        //to be used with original database
        long cernid;
        vector<int> settings[128];

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
        vector<int> VFAT_CHANNELS_CHANNEL_0_to_128;// 0


    void create_table(connection *C,string table_name)
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
    
    //Display a particular row of the table
    void display_row()
    {
        
        /*
        cout << "CERN ID: " << this->cernid << endl;
        cout << "DATA: " << this->settings << endl;
        */
    }

    /*
    //Initialize an object with values
    void initialize(int id,string name, int age, int salary,string address)
    {
        this->ID = id;
        this->SALARY = salary;
        this->AGE = age;
        this->NAME = name;
        this->ADDRESS = address;
    }
    */

    /*

    //Insert the values in the database from a single object
    void insert_row(connection *C, string table_name)
    {
        work WW(*C);
        string sql = "INSERT INTO COMPANY(ID,NAME,AGE,ADDRESS,SALARY) VALUES ("+ \
                    to_string(this->ID) + ", '"+to_string(this->NAME)+"', "+ \
                    to_string(this->AGE)+", '"+to_string(this->ADDRESS)+"', "+ \
                    to_string(this->SALARY)+");";
        
        WW.exec(sql);
        WW.commit();
        cout << "Values inserted !" << endl;
    }

    //Insert values into the database from a vector of objects
    void insert_data(connection *C, vector<component_name> data)
    {
        int i;
        for (i=0;i<data.size();i++)
        {
            data[i].insert_row(&(*C),"COMPANY");
        }
    }
    */

    //Display results 
    void display_results(vector<component_name> &data)
    {
        int i;
        for (i=0;i<data.size();i++)
        {
            data[i].display_row();
            cout << "------" << endl << endl;
        }
    }

    //Returns a vector of objects from a query response
    vector<component_name> row_to_object(result R)
    {
        vector<component_name> query_results;

        for (auto const &row: R)
        {
            component_name obj;

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

};

class postgre_database  // : public component_name //-- hiding the imheritange for the moment
{
    public:

    //Returns the query response of a query 
    result query_response(connection *C,string table_name)
    {
            work WW(*C);
            string query = "SELECT * FROM " + table_name +";";

             result r = WW.exec(query);
             for (auto const &row: r)
             {
                //cout << row["ID"].c_str() << "   " << row["NAME"].c_str();
                for (auto const &field: row) 
                        std::cout << field.c_str() << '\t';
                std::cout << std::endl;
             }
              cout << "Table displayed successfully" << endl;
              return r;
    }
};










int main()
{
    try
        {
            connection C("dbname = " + DBNAME + " user = "+ USER +" password = "+ PASSWORD +" \
                hostaddr = 127.0.0.1 port = 5432");
            if (C.is_open()) {
                   cout << "Opened database successfully: " << C.dbname() << endl;
             } 
             else {
                     cout << "Can't open database" << endl;
                     return 1;
              }

              postgre_database ob;
              result r;
              //ob.insert_datanew(&C,"COMPANY");
              //r = ob.query_response(&C,"COMPANY");

              component_name obj;
              obj.create_table(&C,"VFAT_COMPONENT");
              /*
              //NEW DATA
              obj.initialize(10,"Brett",32,10000,"Australia");
              obj.display_row();

              //INSERT DATA
              obj.insert_row(&C,"COMPANY");
              r = ob.query_response(&C,"COMPANY");
              
              vector<component_name> results;
              //RETURNS A VECTOR OF OBJECTS
              results = obj.row_to_object(r);
              obj.display_results(results);
              */

              C.disconnect ();
        }
        catch(const std::exception& e)
        {
            cerr << e.what() << std::endl;
        }

    return 0;
}