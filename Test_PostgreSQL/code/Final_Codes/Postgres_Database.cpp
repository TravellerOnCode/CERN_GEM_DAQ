#include "Postgres_Database.h"

//Returns the query response of a query 
result Postgres_Database ::query_response(connection *C,string table_name)
{
        work WW(*C);
        string query = "SELECT * FROM " + table_name +";";

        result r = WW.exec(query);
        for (auto const &row: r)
        {
           //cout << row["ID"].c_str() << "   " << row["NAME"].c_str();
           for (auto const &field: row) 
               cout << field.c_str() << '\t';
           cout << endl;
        }
        cout << "Table displayed successfully" << endl;
        return r;
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
	config_id = filename.substr(0,filename.length()-4);
	
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
			}
			else
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

/*
vector<VFAT_Data_Table> VFAT_json_to_vec(string filename)
{
        //function takes filename, reads all VFATS and makes objects out of them and passes it to main
        

        ifstream in(filename, ios::in);

        //parsing file into JSON object
        json j;
        in>>j;

        int i = 0;

        vector<VFAT_Data_Table> vfat_obs;

        for(auto vfat_ele : j.items())
        {
                cout<<"Outer Loop passed"<<endl;
                //loop iterating through all the VFAT elements
                if(vfat_ele.key()[0] != 'v')
                {
                        //case where other components are found
                        //vfat elements ID always assumed to start with a 'v'
                        continue;
                }

                cout<<vfat_ele.key()<<endl;

                VFAT_Data_Table ob;
                //1 vector and 1 map for each vfat element
                unordered_map<string, long> field_data;
                vector<long> array_data;

		for(auto data_ele : vfat_ele.value().items())
                {
                        cout<<"Data field inner loop entered"<<endl;
                        //iterating through individual data elements
                        if(data_ele.value().size() > 1)
                        {
                                //case where the 128 sized array is encountered
                                for(auto arr_itr : data_ele.value().items())
                                {
                                        cout<<"Array inner loop entered"<<endl;
                                        array_data.push_back(stol(arr_itr.value().dump()));
                                        cout<<"Array value pushed"<<endl;
                                }
                        }
                        else
                        {
                                field_data[data_ele.key()] = (stol(data_ele.value().dump()));
                                cout<<"Data field value pushed"<<endl;
                        }
                }

                ob.initialize(field_data,array_data);
                vfat_obs.push_back(ob);
		
		//printing all field and array values for every VFAT element to cross-check
		
                cout<<"field data:"<<endl;

                for(auto k = field_data.begin(); k!=field_data.end(); k++)
                        cout<<k->first<<":"<<k->second<<endl;

                cout<<"array data:"<<endl;

                for(int k = 0; k<array_data.size(); k++)
                        cout<<array_data[k]<<endl;

	}
        return vfat_obs;
}
*/
