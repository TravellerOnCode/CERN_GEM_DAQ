#include <iostream>
#include <fstream>

#include <bsoncxx/builder/stream/document.hpp>
#include <bsoncxx/json.hpp>

#include <mongocxx/client.hpp>
#include <mongocxx/instance.hpp>
#include <string>

using namespace std;

using bsoncxx::builder::stream::close_array;
using bsoncxx::builder::stream::close_document;
using bsoncxx::builder::stream::document;
using bsoncxx::builder::stream::finalize;
using bsoncxx::builder::stream::open_array;
using bsoncxx::builder::stream::open_document;

//connect the client
mongocxx::instance inst{};
mongocxx::client conn{mongocxx::uri{}};

int record = 0;

void insert_records(vector<string> row,string database,string collections)
{
    auto collection = conn[database][collections];
    auto builder = bsoncxx::builder::stream::document{};
   			 bsoncxx::document::value doc_value = builder
     		        << "cernid" << row[0]
            	    << "temperature" << row[1]
            		<< "pressure" << row[2]
                 	<< "muons" << row[3]
            		<< "description" << row[4]
            			<< bsoncxx::builder::stream::finalize;
    		bsoncxx::document::view view = doc_value.view();

  	//insert into collection
    collection.insert_one(view);
    record = record + 1;
}

void display_db(string database,string collections)
{
    auto collection = conn[database][collections];
    auto cursor = collection.find({});

    cout << "GEM DATABASE " << endl;
    cout << "CERN ID" << "\t" << "TEMPERATURE" 
            << "\t" << "PRESSURE" << "\t" << "MUONS" << "\t" << "DESCRIPTION" << endl;

    for (auto&& doc : cursor) {

        /*
        ifstream record_file (bsoncxx::to_json(doc), ifstream::binary);
        record_file >> record;
        cout << record << endl;
        cout << record["_id"]["$oid"] << "\t"
             << record["cernid"] << "\t"
             << record["temperature"] << "\t"
             << record["pressure"] << "\t"
             << record["muons"] << "\t"
             << record["description"] << endl;
        */
        cout << bsoncxx::to_json(doc) << endl;
    }

}

void clear_db(string database,string collections)
{
    auto collection = conn[database][collections];
    auto cursor = collection.find({});

    for (auto&& doc : cursor) {
        collection.delete_one(document{} << finalize);
    }
}

void read_csv_file(string database,string collections)
{
    vector<string> row(5,"");

    ifstream ip("../data/sample_data.csv");
  	if(!ip.is_open()) std::cout << "ERROR: File Open" << '\n';
	while(ip.good()){

   		 	 getline(ip,row[0],',');
    		 getline(ip,row[1],',');
    		 getline(ip,row[2],',');
		 	 getline(ip,row[3],',');
    		 getline(ip,row[4],'\n');

             insert_records(row,database,collections);
    }
}


int main(int, char**) {

    string database = "GEMDB_TEST";
    string collections = "GEMCollection_TEST";

    //read data from the csv file
	read_csv_file( database, collections);

	if (record == 0) 
		cout << "Record not found\n"; 
    else
        cout << record << " Records inserted ! " << endl;
    
    //Display the contents of the database
    display_db( database, collections);

    //to clear all entries of the database
    //clear_db(database, collections); 
    //display_db( database, collections);
}

