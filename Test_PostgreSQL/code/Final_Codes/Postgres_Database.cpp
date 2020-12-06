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
	/*function takes filename, reads all VFATS and makes objects out of them and passes it to main
	*/
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
		vector<long> field_data(48, 0);
		vector<long> array_data(128, 0);
        //cout << "Passed point 3" << endl;
		for(auto data_ele = j[vfat_ele.key()].begin(); data_ele!=j[vfat_ele.key()].end(); data_ele++)
		{
			//iterating through individual data elements
			if(data_ele.value().size() > 1)
			{
                /*
                cout << "Passed point 3 --- 1" << endl;
                
				//case where the 128 sized array is encountered
				for(auto arr_itr = data_ele.value().begin(); arr_itr!=data_ele.value().end(); data_ele++)
				{
                    try
                    {
                        cout<<arr_itr.value()<<" "<<endl;
                        cout<<typeid(arr_itr.value()).name()<<" "<< endl << endl << endl;
					    array_data.push_back(long(arr_itr.value()));
                        
                    }
                    catch(const std::exception& e)
                    {
                        cout<<"Error ---- "<<" "<<endl;
                        std::cerr << e.what() << '\n';
                    }
				}
                */
                
			}
			else
            {
                //cout << "Passed point 3 --- 1 ----- " << endl;
                //cout<<typeid(data_ele.value()).name()<<" "<< endl;
				field_data.push_back(data_ele.value());
            }
		}
        //cout << "Passed point 4" << endl;
		vfat_id = vfat_ele.key();
		vfat_id = vfat_id.substr(1,vfat_id.length());
		//cout << vfat_id << endl;

		ob.initialize(stoi(vfat_id),field_data,array_data);
		ob2.initialize(stoi(config_id),stoi(vfat_id));
		

		vfat_obs.push_back(ob);
		vfat_indexes.push_back(ob2);
		

		freqq = freqq + 1;
	}
	cout << "No. of VFAT Configurations scanned -> " << freqq << endl;
	return vfat_obs;
}
