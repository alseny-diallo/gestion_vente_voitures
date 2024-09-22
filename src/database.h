#ifndef DATABASE_H
#define DATABASE_H

#include <mysql_driver.h>
#include <mysql_connection.h>
#include <cppconn/prepared_statement.h>
#include <memory>

std::unique_ptr<sql::Connection> connectToDatabase();

#endif
