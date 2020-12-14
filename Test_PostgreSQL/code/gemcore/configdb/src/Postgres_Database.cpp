#include "../interface/Postgres_Database.h"

//Returns the query response of a query 
result Postgres_Database ::query_response(connection *C,string table_name,string query)
{
	work WW(*C);
	//string query = "SELECT * FROM " + table_name +";";
	result r = WW.exec(query);
	return r;
}

string Postgres_Database ::extract_configid(string filename)
{
	int l1,l2;
	string config_id = "";
	l1 = filename.find_last_of('/');
	l2 = filename.find_last_of('.');
	config_id = filename.substr(l1+1,l2);
	return config_id;

}

//to store the index values
vector<VFAT_Index_Table> Postgres_Database ::Index_json_to_vec()
{
	return vfat_indexes;
}

//to store the config values
vector<VFAT_Config_Table> Postgres_Database ::Config_json_to_vec()
{
	return vfat_configs;
}


vector<VFAT_Data_Table> Postgres_Database ::VFAT_json_to_vec(string filename)
{
	//function takes filename, reads all VFATS and makes objects out of them and passes it to main
	
    cout << "File Name: " << filename << endl;
	ifstream in(filename, ios::in);

	//parsing file into JSON object
	json j;
	in>>j;

	vector<VFAT_Data_Table> vfat_obs;

	//cout << j.begin().key() << "------" << j.end().key() << endl;
    //cout << "Passed point 2" << endl;
	int freqq = 0;
	string vfat_id = "", config_id = "";
	//config_id = filename.substr(3,filename.length()-4);
	config_id = extract_configid(filename);
	
	VFAT_Config_Table ob3;
	ob3.initialize(stoi(config_id));
	vfat_configs.push_back(ob3);

	for(auto vfat_ele = j.begin(); vfat_ele!=j.end(); vfat_ele++)
	{
		//loop iterating through all the VFAT elements
		if(vfat_ele.key()[0] != 'v')
		{
			//case where other components are found
			//vfat elements ID always assumed to start with a 'v'
			continue;
		}
		
		VFAT_Data_Table ob;
		VFAT_Index_Table ob2;
		
		//2 vectors for each vfat element
		unordered_map<string, long> field_data;
        vector<long> array_data;

        //cout << "Passed point 3" << endl;
		for(auto data_ele = j[vfat_ele.key()].begin(); data_ele!=j[vfat_ele.key()].end(); data_ele++)
		{
			//cout<<"Data field inner loop entered"<<endl;
			//iterating through individual data elements
			if(data_ele.value().size() > 1)
			{
				//case where the 128 sized array is encountered
				for(auto arr_itr : data_ele.value().items())
				{
					//cout<<"Array inner loop entered"<<endl;
					array_data.push_back(stoi(arr_itr.value().dump()));
					//cout<<"Array value pushed"<<endl;
				}
			} else
			{
				field_data[data_ele.key()] = (stoi(data_ele.value().dump()));
				//cout<<"Data field value pushed"<<endl;
			}
		}
        //cout << "Passed point 4" << endl;
		vfat_id = vfat_ele.key();
		vfat_id = vfat_id.substr(1,vfat_id.length());
		//cout << vfat_id << endl;

		ob.initialize(stoi(vfat_id),field_data,array_data);
		ob2.initialize(stoi(config_id),stoi(vfat_id));
		
		//cout << "VFAT_ID -> " << vfat_id << "CFG_IREF -> " << field_data["CFG_IREF"] << endl;

		vfat_obs.push_back(ob);
		vfat_indexes.push_back(ob2);
		freqq = freqq + 1;
	}
	cout << "No. of VFAT Configurations scanned -> " << freqq << endl;
	return vfat_obs;
}

vector<VFAT_Data_Table> Postgres_Database ::GET_DATA_FROM_REFCONFIG(connection *C,long reference_config_id)
{
	VFAT_Index_Table obj;
	VFAT_Data_Table obj2;

	vector<VFAT_Index_Table> v;
	vector<VFAT_Data_Table> vfat_data;

	//vector<long> id_list;
	work WW(*C);
	string query = "SELECT * FROM "+to_string(VFAT_INDEX_TABLE)+" WHERE CONFIG_ID = " + to_string(reference_config_id) + ";";
	string id_list = "";
	result r = WW.exec(query);
	v = obj.row_to_object(r);

	for (int i=0;i<v.size()-1;i++)
	{
		//id_list.push_back(v[i].get_id());
		id_list = id_list + to_string(v[i].get_id()) + ", ";
	}
	id_list = id_list + to_string(v[v.size()-1].get_id());
	query = "SELECT * FROM "+to_string(VFAT_DATA_TABLE)+" WHERE ID IN (" + id_list + ");";
	r = WW.exec(query);
	vfat_data = obj2.row_to_object(r);

	return vfat_data;
}