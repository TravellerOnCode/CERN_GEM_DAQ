#include "./interface/infoTree.h"
#include "./interface/Tree_Database.h"

int main(int argc, char **argv) {
  try {

    // connect to the database
    connection dbClient("dbname = " + to_string(DBNAME) + "\
                            user = " +
                        USER + "\
                            password = " +
                        PASSWORD + " \
                            hostaddr = " +
                        IP + "\
                            port = " +
                        PORT);

    if (dbClient.is_open())
      cout << "Opened database successfully: " << dbClient.dbname() << endl;
    else {
      cout << "Can't open database" << endl;
      return 1;
    }

    dbClient.disconnect();
  } catch (const std::exception &e) {
    cerr << e.what() << std::endl;
  }

  return 0;
}