#pragma once

#include <mysql_driver.h>
#include <mysql_connection.h>
#include <mysql_error.h>

#include <cppconn/prepared_statement.h>
#include <cppconn/exception.h>
#include <cppconn/driver.h>
#include <cppconn/statement.h>
#include <cppconn/prepared_statement.h>

using namespace std;

namespace Database 
{
	class Database
	{
	public:
		// Constructor & Destructor
		Database();
		~Database();
		
		// Class Functions
		inline bool connect();
		bool createDatabase();
		void error(const string query);

		// Data Fetch Functions
		

	private:
		// Database Pointer Declaration
		sql::mysql::MySQL_Driver* driver;
		sql::Connection* conn;
		sql::Statement* stmt;
		sql::PreparedStatement* pstmt;
		sql::ResultSet* res;

		// Database Connection Info
		const string server = "plesk.remote.ac";
		const string username = "ws344889_db_user";
		const string password = "1w^9Hcf16";
	};
}
