#pragma once

#include <bits/stdc++.h>
#include <iomanip>
#include <iostream>
#include <pqxx/pqxx>
#include <sstream>
#include <string>


using namespace std;
using namespace pqxx;

class Tree_Database {
public:
  /// Create the data table
  void create_table(connection *dbClient);

  /// Access the id
  long get_id();

  /// Initialize the class objects
  void initialize();

  /// Insert a row into the Table
  long insert_row(connection *dbClient);

  /// Insert data from the class objects into the Table
  void insert_data();

private:
  long serial;
  long id;
  long parent_id;
  string type;
};
