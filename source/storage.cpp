
#include <cstdlib>
#include <cstring>
#include <iostream>
#include <stdlib.h>
#include <sstream>

#include "storage.h"

using namespace pfs;
using namespace std;

int Storage::add_picture(Photo photo) {
    sqlite3 *db = open();

    // Insert the new data
    stringstream insert_query;
    insert_query << "INSERT INTO photos VALUES(";
    insert_query << "'" << photo.get_name() << "', ";
    insert_query << photo.size() << ", ";
    insert_query << "'" << photo.data() << "', ";
    insert_query << photo.get_year() << ", ";
    insert_query << "'" << photo.get_month() << "') ";

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
    string select_query = "SELECT year from photos";

    cout << select_query << endl;

    if (sqlite3_prepare(db, select_query.c_str(), -1, &statement, 0) != SQLITE_OK) {
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

vector<int> Storage::get_months(int year) {
    sqlite3 *db = open();
    sqlite3_stmt *statement;

    vector<int> months;

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
            months.push_back(sqlite3_column_int(statement, 0));
        }
    } while (result != SQLITE_DONE);

    sqlite3_close(db);

    // Remove duplicate elements
    for (vector<int>::iterator i = months.begin(); i != months.end(); ++i) {
        for (vector<int>::iterator j = i + 1; j != months.end(); ++j) {
            if (*i == *j) {
                months.erase(j);

                i = months.begin();
                j = months.begin();
            }
        }
    }

    return months;
}

vector<Photo> Storage::get_photos(int year, int month) {
    sqlite3 *db = open();
    sqlite3_stmt *statement;

    vector<Photo> photos;

    // Run the query
    stringstream select_query;
    select_query << "SELECT * from photos WHERE (year=" << year << " AND month=" << month << ")";

    cout << select_query.str() << endl;

    if (sqlite3_prepare(db, select_query.str().c_str(), -1, &statement, 0) != SQLITE_OK) {
        stringstream message;
        message << "Could not select photos for " << month << " in " << year << " from database";

        cout << message.str() << endl;
        
        return photos;
    }

    // Add all the photos to our vector
    int result = 0;

    do {
        result = sqlite3_step(statement);
        
        if (result == SQLITE_ROW) {
            string name = (const char*) sqlite3_column_text(statement, 0);
            int size = sqlite3_column_int(statement, 1);
            const void* blob = sqlite3_column_blob(statement, 2);

            char* blob_copy = (char*)malloc(size);
            memcpy(blob_copy, blob, size);
            string data(blob_copy, size);
            free(blob_copy);

            photos.push_back(Photo(name, data));
        }
    } while (result != SQLITE_DONE);

    sqlite3_close(db);

    return photos;
}

sqlite3* Storage::open() {
    sqlite3 *db;

    if(sqlite3_open(get_database_path().c_str(), &db) != SQLITE_OK) {
        cout << "Could not open database at " << get_database_path() << endl;
        return NULL;
    }
    
    // Init with default tables if they do not exist.
    string create_table_query = "CREATE TABLE IF NOT EXISTS photos (name TEXT NOT NULL, size INTEGER NOT NULL, contents BLOB NOT NULL, year INTEGER NOT NULL, month INTEGER NOT NULL)";
    sqlite3_exec(db, create_table_query.c_str(), 0, 0, 0);

    return db;
}

string Storage::get_database_path() {
    string home_dir = getenv("HOME");
    string path = "/.pfs";
    return home_dir + path;
}
