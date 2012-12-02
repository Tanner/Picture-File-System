
#include <iostream>
#include <stdlib.h>
#include <sstream>

#include "storage.h"

using namespace pfs;
using namespace std;

int Storage::add_picture(string name, const char* data, size_t size, int year, string month) {
    sqlite3 *db = open();

    // Init with default tables if they do not exist.
    char *create_table_query = "CREATE TABLE IF NOT EXISTS photos (name TEXT NOT NULL, size INTEGER NOT NULL, contents BLOB NOT NULL, year INTEGER NOT NULL, month TEXT NOT NULL)";
    sqlite3_exec(db, create_table_query, 0, 0, 0);

    // Insert the new data
    stringstream insert_query;
    insert_query << "INSERT INTO photos VALUES(";
    insert_query << "'" << name << "', ";
    insert_query << size << ", ";
    insert_query << "'" << data << "', ";
    insert_query << year << ", ";
    insert_query << "'" << month << "') ";

    cout << insert_query.str() << endl;

    if (sqlite3_exec(db, insert_query.str().c_str(), 0, 0, 0) != SQLITE_OK) {
        cout << "Could not insert photo in database" << endl;

        sqlite3_close(db);

        return -1;
    }

    sqlite3_close(db);

    return 0;
}

vector<int> Storage::get_years() {
    sqlite3 *db = open();
    sqlite3_stmt *statement;

    vector<int> years;

    // Run the query
    char *select_query = "SELECT year from photos";

    cout << select_query << endl;

    if (sqlite3_prepare(db, select_query, -1, &statement, 0) != SQLITE_OK) {
        cout << "Could not select years from database" << endl;
        
        return years;
    }

    // Add all the years to our vector
    int result = 0;

    do {
        result = sqlite3_step(statement);
        
        if (result == SQLITE_ROW) {
            years.push_back(sqlite3_column_int(statement, 0));
        }
    } while (result != SQLITE_DONE);

    sqlite3_close(db);

    // Remove duplicate elements
    for (vector<int>::iterator i = years.begin(); i != years.end(); ++i) {
        for (vector<int>::iterator j = i + 1; j != years.end(); ++j) {
            if (*i == *j) {
                years.erase(j);

                i = years.begin();
                j = years.begin();
            }
        }
    }

    return years;
}

vector<string> Storage::get_months(int year) {
    sqlite3 *db = open();
    sqlite3_stmt *statement;

    vector<string> months;

    // Run the query
    stringstream select_query;
    select_query << "SELECT month from photos WHERE (year=" << year << ")";

    cout << select_query.str() << endl;

    if (sqlite3_prepare(db, select_query.str().c_str(), -1, &statement, 0) != SQLITE_OK) {
        stringstream message;
        message << "Could not select months for year " << year << " from database";

        cout << message.str() << endl;
        
        return months;
    }

    // Add all the months to our vector
    int result = 0;

    do {
        result = sqlite3_step(statement);
        
        if (result == SQLITE_ROW) {
            months.push_back((const char *) sqlite3_column_text(statement, 0));
        }
    } while (result != SQLITE_DONE);

    sqlite3_close(db);

    // Remove duplicate elements
    for (vector<string>::iterator i = months.begin(); i != months.end(); ++i) {
        for (vector<string>::iterator j = i + 1; j != months.end(); ++j) {
            if (*i == *j) {
                months.erase(j);

                i = months.begin();
                j = months.begin();
            }
        }
    }

    return months;
}

sqlite3* Storage::open() {
    sqlite3 *db;

    if(sqlite3_open(get_database_path().c_str(), &db) != SQLITE_OK) {
        cout << "Could not open database at " << get_database_path() << endl;
        return NULL;
    }

    return db;
}

string Storage::get_database_path() {
    string home_dir = getenv("HOME");
    string path = "/.pfs";
    return home_dir + path;
}
