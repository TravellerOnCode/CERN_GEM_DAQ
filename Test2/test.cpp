#include <iostream>

#include <bsoncxx/builder/stream/document.hpp>
#include <bsoncxx/json.hpp>

#include <mongocxx/client.hpp>
#include <mongocxx/instance.hpp>


using bsoncxx::builder::stream::close_array;
using bsoncxx::builder::stream::close_document;
using bsoncxx::builder::stream::document;
using bsoncxx::builder::stream::finalize;
using bsoncxx::builder::stream::open_array;
using bsoncxx::builder::stream::open_document;

int main(int, char**) {
    std::cout << "In ... \n";

    mongocxx::instance inst{};
    mongocxx::client conn{mongocxx::uri{}};
	/*
    bsoncxx::builder::stream::document document{};

    auto collection = conn["testdb"]["testcollection"];
    document << "hello" << "world";

    collection.insert_one(document.view());
	*/

auto collection = conn["testdb"]["testcollection"];
auto builder = bsoncxx::builder::stream::document{};
    bsoncxx::document::value doc_value = builder
            << "cernid" << "c10"
            << "temperature" << "200"
            << "pressure" << "300"
            << "muons" << "3"
            << "description" << "CMS GEM"
            << bsoncxx::builder::stream::finalize;
    
    bsoncxx::document::view view = doc_value.view();
collection.insert_one(view);
    auto cursor = collection.find({});

    for (auto&& doc : cursor) {
        std::cout << bsoncxx::to_json(doc) << std::endl;
    }


    std::cout << "In ... \n";
}

