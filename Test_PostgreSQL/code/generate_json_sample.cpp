#include<bits/stdc++.h>
#include<time.h>
using namespace std;

long get_random(long start, long end)
{
	srand(time(0));
	
	return (start + rand()%end);
}

int main()
{
	ifstream text_in("vfat_data_org.txt", ios::in);

	if(!text_in)
	{
		cout<<"File opening error"<<endl;
	}

	vector<string> final_fields;

	string line;

	while(getline(text_in, line))
	{
		istringstream split_line(line);
		string word = "";

		while(split_line>>word)
		{
			if(word[0] == '/')
				break;
			if(word[word.length() - 1] != '/' && word[word.length() - 1] != ';')
				continue;
			
			string add_token = "";
		
			if(word[word.length()-1] == '/')
				add_token = word.substr(0,word.length()-3);
		
			else if(word[word.length()-1] == ';')
				add_token = word.substr(0, word.length()-1);

			if(find(final_fields.begin(), final_fields.end(), add_token) == final_fields.end())
				final_fields.push_back(add_token);
		}

	}
	text_in.close();

	cout<<"Fields have been obtained correctly!"<<endl;
	cout<<"Generating configurations into a JSON file"<<endl;

	cout<<final_fields.size()<<endl;
	fstream sample_file("Sample_JSON.json", ios::app);

	//sample_file<<"{"<<endl;
	//needed only for the first batch of data generation

	string inv_comma = "\"";
	long val = 0;

	srand(time(0));

	for(int i = 20000; i<=20000; i++)
	{
		cout<<"Data record no. "<<i<<" being generated"<<endl;
		
		sample_file<<inv_comma<<("v"+to_string(i))<<inv_comma<<":"<<"{"<<endl;

		//Starting with data fields generation

		for(int j = 0; j<final_fields.size() - 1; j++)
		{
			sample_file<<inv_comma<<final_fields[j]<<inv_comma<<":";
			val = (i%7) + (rand()%10000);
			sample_file<<val<<","<<endl;
		}

		sample_file<<inv_comma<<final_fields[final_fields.size()-1]<<inv_comma<<":[";

		for(int j = 0; j<127; j++)
		{
			val = (i%19) + rand()%200;
			sample_file<<val<<",";
		}
		val = (i%19) + (rand()%200);
		sample_file<<val<<"]}"<<endl;
		//comma needed at the end for all data except the last batch
	} 	

	sample_file<<"}"<<endl;
	//needed only for the last batch of generation

	sample_file.close();

	return 0;
	 
}
