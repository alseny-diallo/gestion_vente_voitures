#include "database.h"
#include <iostream>
using namespace std;

unique_ptr<sql::Connection> connectToDatabase() {
    try {
        sql::mysql::MySQL_Driver* driver = sql::mysql::get_mysql_driver_instance();
        unique_ptr<sql::Connection> con(driver->connect("tcp://localhost:3306", "root", "password"));
        con->setSchema("gestionVenteVoiture");
        return con;
    } catch (sql::SQLException& e) {
        cerr << "Database connection error: " << e.what() << endl;
        return nullptr;
    }
}
