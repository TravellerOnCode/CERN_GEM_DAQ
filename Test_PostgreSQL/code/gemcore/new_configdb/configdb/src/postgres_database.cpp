#include "../interface/postgres_database.h"

// Returns the query response of a query
pqxx::result postgres_database::query_response(pqxx::connection* db_client, const std::string& query)
{
    pqxx::work WW(*db_client);

    /// Execute the Query
    pqxx::result r = WW.exec(query);

    /// Return the response
    return r;
}

std::string postgres_database::extract_configid(const std::string& filepath)
{
    /// Extract the filename (excluding extension) from the File Path
    int l1, l2;
    std::string config_id = "";
    l1 = filepath.find_last_of('/');
    l2 = filepath.find_last_of('.');
    config_id = filepath.substr(l1 + 1, l2);
    return config_id;
}

// to store the index values
// std::vector<vfat_index_table> postgres_database ::Index_json_to_vec()
//{
//	return vfat_indexes;
//}

// to store the config values
std::vector<vfat_config_table> postgres_database::getConfigIDs()
{
    return vfat_configs;
}

std::vector<vfat_data_table> postgres_database::getVFATSettings(const std::string& filename)
{
    /// Function takes filename,
    /// Reads all VFATS and makes objects out of them and passes it to main

    std::cout << "File Name: " << filename << std::endl;
    std::ifstream in(filename, std::ios::in);

    // parsing file into JSON object
    nlohmann::json j;
    in >> j;

    std::vector<vfat_data_table> vfat_obs;

    // std::cout << j.begin().key() << "------" << j.end().key() << std::endl;
    // std::cout << "Passed point 2" << std::endl;
    int freqq = 0;
    std::string vfat_id = "", config_id = "";
    // config_id = filename.substr(3,filename.length()-4);
    config_id = extract_configid(filename);

    vfat_config_table ob3;
    ob3.initialize(stoi(config_id));
    vfat_configs.push_back(ob3);

    for (auto vfat_ele = j.begin(); vfat_ele != j.end(); vfat_ele++) {
        // loop iterating through all the VFAT elements
        if (vfat_ele.key()[0] != 'v') {
            // case where other components are found
            // vfat elements ID always assumed to start with a 'v'
            continue;
        }

        vfat_data_table ob;
        vfat_index_table ob2;

        // 2 std::vectors for each vfat element
        std::unordered_map<std::string, long> field_data;
        std::vector<long> array_data;

        // std::cout << "Passed point 3" << std::endl;
        for (auto data_ele = j[vfat_ele.key()].begin();
             data_ele != j[vfat_ele.key()].end(); data_ele++) {
            // std::cout<<"Data field inner loop entered"<<std::endl;
            // iterating through individual data elements
            if (data_ele.value().size() > 1) {
                // case where the 128 sized array is encountered
                for (auto arr_itr : data_ele.value().items()) {
                    // std::cout<<"Array inner loop entered"<<std::endl;
                    array_data.push_back(stoi(arr_itr.value().dump()));
                    // std::cout<<"Array value pushed"<<std::endl;
                }
            } else {
                field_data[data_ele.key()] = (stoi(data_ele.value().dump()));
                // std::cout<<"Data field value pushed"<<std::endl;
            }
        }
        // std::cout << "Passed point 4" << std::endl;
        vfat_id = vfat_ele.key();
        vfat_id = vfat_id.substr(1, vfat_id.length());
        // std::cout << vfat_id << std::endl;

        ob.initialize(stoi(vfat_id), field_data, array_data);
        ob2.initialize(stoi(config_id), stoi(vfat_id));

        // std::cout << "VFAT_ID -> " << vfat_id << "CFG_IREF -> " <<
        // field_data["CFG_IREF"] << std::endl;

        vfat_obs.push_back(ob);
        // vfat_indexes.push_back(ob2);
        freqq = freqq + 1;
    }
    std::cout << "No. of VFAT Configurations scanned -> " << freqq << std::endl;
    return vfat_obs;
}

std::vector<vfat_data_table>
postgres_database::getReferenceVFATSettings(pqxx::connection* db_client,
    long reference_config_id)
{
    vfat_index_table obj;
    vfat_data_table obj2;

    std::vector<vfat_index_table> v;
    std::vector<vfat_data_table> vfat_data;

    // std::vector<long> id_list;
    pqxx::work WW(*db_client);
    std::string query = std::string("SELECT * FROM ") + VFAT_INDEX_TABLE + " WHERE CONFIG_ID = " + std::to_string(reference_config_id) + ";";
    std::string id_list = "";
    pqxx::result r = WW.exec(query);
    v = obj.row_to_object(r);

    for (auto i = v.begin(); i != v.end(); ++i) {
        // id_list.push_back(v[i].get_id());
        id_list = id_list + std::to_string((*i).get_id()) + ", ";
    }
    id_list = id_list + std::to_string(v[v.size() - 1].get_id());
    query = std::string("SELECT * FROM ") + VFAT_DATA_TABLE + " WHERE ID IN (" + id_list + ");";
    r = WW.exec(query);
    vfat_data = obj2.row_to_object(r);

    return vfat_data;
}