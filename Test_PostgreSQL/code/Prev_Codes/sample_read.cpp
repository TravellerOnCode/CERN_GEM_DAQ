#include<bits/stdc++.h>
#include "json.hpp"

using namespace std;
using json = nlohmann::json;

int main(int argc, char** argv)
{
	ifstream in(argv[1], ios::in);

	json j;

	in >> j;

	int count = 1;

	cout<<j.size()<<endl;

	for(auto vfat_ele = j.begin(); vfat_ele!=j.end(); vfat_ele++)
	{
		cout<<vfat_ele.key()[0]<<endl;	
		for(auto data_ele = j[vfat_ele.key()].begin(); data_ele!=j[vfat_ele.key()].end();data_ele++)
		{
			if(data_ele.value().size() > 1)
                        {
                                //case where the 128 sized array is encountered
                                /*for(auto arr_itr = data_ele.value().begin(); arr_itr!=data_ele.value().end(); data_ele++)
                                {
                                        cout<<(arr_itr.value())<<" ";
                                }*/

				for(auto arr_itr : data_ele.value().items())
					cout<<arr_itr.value()<<" "<<endl;
                        }
			else
				cout<<data_ele.key()<<" : "<<data_ele.value()<<endl;
		}
	

		//cout<<vfat_ele.key()<<" : "<<vfat_ele.value()<<endl;
		count++;
		if(count > 1)
			break;
	}

	in.close();
	return 0;
}
