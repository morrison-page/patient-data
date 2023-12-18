#include <iostream>
#include <string>
#include <mysql_driver.h>
#include <mysql_connection.h>
#include <mysql_error.h>

#include <cppconn/prepared_statement.h>
#include <cppconn/exception.h>
#include <cppconn/driver.h>
#include <cppconn/statement.h>
#include <cppconn/prepared_statement.h>

using namespace std;

int main()
{
    // Database Pointer Declaration
    sql::mysql::MySQL_Driver* driver;
    sql::Connection* conn;
    sql::Statement* stmt;
    sql::PreparedStatement* pstmt;
    sql::ResultSet* res;

    // DB Connection Info
    const string server = "plesk.remote.ac";
    const string username = "ws344889_db_user";
    const string password = "1w^9Hcf16";

    // Grab driver and Connect to DB
    driver = sql::mysql::get_mysql_driver_instance();
    conn = driver->connect(server, username, password);

    if (conn) 
    {
        // Use this database for query exec
        conn->setSchema("ws344889_patient_data");
        
        // Create statement Obj
        stmt = conn->createStatement();

        // SQL statements to create tables
        const string createUsersTable = "CREATE TABLE IF NOT EXISTS users ("
            "user_id INT PRIMARY KEY AUTO_INCREMENT,"
            "username VARCHAR(255) NOT NULL,"
            "password VARCHAR(255) NOT NULL"
            ");";

        const string createRolesTable = "CREATE TABLE IF NOT EXISTS roles ("
            "role_id INT PRIMARY KEY,"
            "role_name VARCHAR(255) NOT NULL"
            ");";

        const string createRolesData = "INSERT IGNORE INTO roles (role_id, role_name) VALUES (1, 'patient'), (2, 'doctor/nurse'), (3, 'pharmacist');";

        const string createUserRolesTable = "CREATE TABLE IF NOT EXISTS user_roles ("
            "user_id INT NOT NULL,"
            "role_id INT NOT NULL,"
            "PRIMARY KEY(user_id, role_id),"
            "FOREIGN KEY(user_id) REFERENCES users(user_id),"
            "FOREIGN KEY(role_id) REFERENCES roles(role_id)"
            ");";

        const string createPatientsTable = "CREATE TABLE IF NOT EXISTS patients ("
            "patient_id INT PRIMARY KEY AUTO_INCREMENT,"
            "user_id INT NOT NULL,"
            "other_patient_info VARCHAR(255),"
            "FOREIGN KEY(user_id) REFERENCES users(user_id)"
            ");";

        const string createCancerTable = "CREATE TABLE IF NOT EXISTS cancer ("
            "cancer_id INT PRIMARY KEY AUTO_INCREMENT,"
            "user_id INT NOT NULL,"
            "cancer_stage INT NOT NULL"
            ");";

        const string createDiabetesTable = "CREATE TABLE IF NOT EXISTS diabetes ("
            "diabetes_id INT PRIMARY KEY AUTO_INCREMENT,"
            "patient_id INT NOT NULL,"
            "diabetes_type INT,"
            "FOREIGN KEY(patient_id) REFERENCES patients(patient_id)"
            ");";

        const string createSmokingTable = "CREATE TABLE IF NOT EXISTS smoking ("
            "smoking_id INT PRIMARY KEY AUTO_INCREMENT,"
            "patient_id INT NOT NULL,"
            "pack_frequency VARCHAR(255),"
            "FOREIGN KEY(patient_id) REFERENCES patients(patient_id)"
            ");";

        // Exec all SQL to create tables
        stmt->execute(createUsersTable);
        stmt->execute(createRolesTable);
        stmt->execute(createRolesData);
        stmt->execute(createUserRolesTable);
        stmt->execute(createPatientsTable);
        stmt->execute(createCancerTable);
        stmt->execute(createDiabetesTable);
        stmt->execute(createSmokingTable);



        /* ------------ Working with query results ------------ */

        // Execute statement and grab result
        stmt->execute("SELECT * FROM users WHERE user_id = 1;");
        res = stmt->getResultSet();

        // Get Result
        while (res->next())
        {
            // Grab specific column data
            int userId = res->getInt("user_id");
            string username = res->getString("username");

            // Print out results
            cout << "User ID: " << userId << endl;
            cout << "Username: " << username << endl;
        }

        delete res;
        delete stmt;
    }

    delete conn;
    return 0;
}