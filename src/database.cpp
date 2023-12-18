#include <iostream>

#include <mysql_driver.h>
#include <mysql_connection.h>
#include <mysql_error.h>

#include <cppconn/prepared_statement.h>
#include <cppconn/exception.h>
#include <cppconn/driver.h>
#include <cppconn/statement.h>
#include <cppconn/prepared_statement.h>

#include "database.h"

using namespace std;

namespace Database
{
	// Constructor
	Database::Database()
	{

	};
	// Destructor
	Database::~Database()
	{

	};

	inline bool Database::connect(sql::mysql::MySQL_Driver* driver, sql::Connection* conn)
	{
		// Grab Database Driver and Connect
		driver = sql::mysql::get_driver_instance();
		conn = driver->connect(server, username, password);

		// Check for Successfull Connection
		if (conn) return true;
		return false;
	};

	bool Database::createDatabase()
	{

	};

	// Error Handling
	inline void Database::error(const string& query, const sql::SQLException& e, sql::Statement* stmt)
	{
		try {
			stmt->execute(query);
		}
		catch (sql::SQLException& e) {
			cout << "# ERR: SQLException in " << __FILE__;
			cout << "(" << __FUNCTION__ << ") on line " << __LINE__ << endl;
			cout << "# ERR: " << e.what();
			cout << " (MySQL error code: " << e.getErrorCode();
			cout << ", SQLState: " << e.getSQLState() << ")" << endl;
		}
	};
}