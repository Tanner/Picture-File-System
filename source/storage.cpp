
#include <cstdlib>
#include <cstring>
#include <iostream>
#include <stdlib.h>
#include <sstream>

#include "storage.h"
#include "base64.h"

using namespace pfs;
using namespace std;

Storage::Storage(string path) : path_(path), db_(NULL) {

}

Storage::~Storage() {
    if (db_ == NULL)
        return;

    close();
}

int Storage::add_picture(Photo& photo) {
    open();

    // Check to see if we could open the database
    if (!db_) {
        return -1;
    }

    string encoded_data(base64_encode((unsigned char*)photo.data().c_str(), photo.size()));
    struct tm time = photo.get_time();

    // Insert the new data
    stringstream insert_query;
    insert_query << "INSERT INTO photos VALUES(";
    insert_query << "'" << photo.get_name() << "', ";
    insert_query << photo.data().length() << ", ";
    insert_query << "'" << encoded_data << "', ";
    insert_query << mktime(&time) << ", ";
    insert_query << photo.get_year() << ", ";
    insert_query << "'" << photo.get_month() << "') ";

    stringstream message;
    message << "INSERTING " << photo.get_name() << " INTO DATABASE";
    log(message.str());
    
    if (sqlite3_exec(db_, insert_query.str().c_str(), 0, 0, 0) != SQLITE_OK) {
        log("Could not insert photo in database");

        return -1;
    }

    return 0;
}

Storage* Storage::clone() {
    return new Storage(*this);
}

int Storage::rename_picture(Photo& photo, string new_name) {
    open();
    
    // Check to see if we could open the database
    if (!db_) {
        return -1;
    }

    stringstream query;
    query << "UPDATE photos ";
    query << "SET name='" << new_name << "' ";
    query << "WHERE rowid='" << photo.get_id() << "'";

    log(query.str());

    if (sqlite3_exec(db_, query.str().c_str(), 0, 0, 0) != SQLITE_OK) {
        stringstream message;
        message << "Could not rename photo in database to " << new_name;
        log(message.str());

        return -1;
    }

    return 0;
}

int Storage::set_data_for_photo(int id, string& data) {
    open();
    
    // Check to see if we could open the database
    if (!db_) {
        return -1;
    }

    string encoded_data(base64_encode((unsigned char*)data.c_str(), data.size()));

    // Insert the new data
    stringstream query;
    query << "UPDATE photos ";
    query << "SET contents='" << encoded_data << "', ";
    query << "size='" << data.length() << "' ";
    query << "WHERE rowid='" << id << "'";

    log(query.str());

    if (sqlite3_exec(db_, query.str().c_str(), 0, 0, 0) != SQLITE_OK) {
        log("Could not set photo data in database");

        return -1;
    }

    return 0;
}

vector<int> Storage::get_years() {
    open();
    sqlite3_stmt *statement;

    vector<int> years;

    // Check to see if we could open the database
    if (!db_) {
        return years;
    }

    // Run the query
    string select_query = "SELECT year from photos";

    log(select_query);

    if (sqlite3_prepare(db_, select_query.c_str(), -1, &statement, 0) != SQLITE_OK) {
        log("Could not select years from database");
        
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
    open();
    sqlite3_stmt *statement;

    vector<int> months;

    // Check to see if we could open the database
    if (!db_) {
        return months;
    }

    // Run the query
    stringstream select_query;
    select_query << "SELECT month from photos WHERE (year=" << year << ")";

    log(select_query.str());

    if (sqlite3_prepare(db_, select_query.str().c_str(), -1, &statement, 0) != SQLITE_OK) {
        stringstream message;
        message << "Could not select months for year " << year << " from database";
        log(message.str());
        
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
    open();
    sqlite3_stmt *statement;

    vector<Photo> photos;

    // Check to see if we could open the database
    if (!db_) {
        return photos;
    }

    // Run the query
    stringstream select_query;
    select_query << "SELECT rowid, name, size, time from photos WHERE (year=" << year << " AND month=" << month << ")";

    log(select_query.str());

    if (sqlite3_prepare(db_, select_query.str().c_str(), -1, &statement, 0) != SQLITE_OK) {
        stringstream message;
        message << "Could not select photos for " << month << " in " << year << " from database";
        log(message.str());
        
        return photos;
    }

    // Add all the photos to our vector
    int result = 0;

    do {
        result = sqlite3_step(statement);
        
        if (result == SQLITE_ROW) {
            int id = sqlite3_column_int(statement, 0);
            string name = (const char*) sqlite3_column_text(statement, 1);
            int size = sqlite3_column_int(statement, 2);
            time_t time = sqlite3_column_int(statement, 3);

            photos.push_back(Photo(id, name, size, time, shared_ptr<Storage>(this->clone())));
        }
    } while (result != SQLITE_DONE);

    return photos;
}

string Storage::get_data_for_photo(int id) {
    open();
    sqlite3_stmt *statement;

    string data = "";
    
    // Check to see if we could open the database
    if (!db_) {
        return "";
    }

    // Run the query
    stringstream select_query;
    select_query << "SELECT contents from photos WHERE (rowid=" << id << ")";

    log(select_query.str());

    if (sqlite3_prepare(db_, select_query.str().c_str(), -1, &statement, 0) != SQLITE_OK) {
        stringstream message;
        message << "Could not select photo with id " << id << " from database";
        log(message.str());
        
        return data;
    }

    // Get the data for the query
    int result = -1;

    do {
        result = sqlite3_step(statement);
        
        if (result == SQLITE_ROW) {
            const void* blob = sqlite3_column_blob(statement, 0);
            int size = sqlite3_column_bytes(statement, 0);

            data = string((const char*) blob, size);
        }
    } while (result != SQLITE_DONE);

    return base64_decode(data);
}

int Storage::delete_photo(int id) {
    open();

    // Check to see if we could open the database
    if (!db_) {
        return -1;
    }

    // Run the query
    stringstream delete_query;
    delete_query << "DELETE from photos WHERE (rowid=" << id << ")";

    log(delete_query.str());
    
    if (sqlite3_exec(db_, delete_query.str().c_str(), 0, 0, 0) != SQLITE_OK) {
        stringstream message;
        message << "Could not delete photo with id " << id << " from database";
        log(message.str());
        
        return -1;
    }

    return 0;
}

void Storage::open() {
    if (db_ != NULL) {
        return;
    }

    if(sqlite3_open(path_.c_str(), &db_) != SQLITE_OK) {
        log("Could not open database");
        return;
    }
    
    // Init with default tables if they do not exist.
    string create_table_query = "CREATE TABLE IF NOT EXISTS photos (name TEXT UNIQUE NOT NULL, size INTEGER NOT NULL, contents BLOB NOT NULL, time INTEGER NOT NULL, year INTEGER NOT NULL, month INTEGER NOT NULL)";
    sqlite3_exec(db_, create_table_query.c_str(), 0, 0, 0);
}

int Storage::close() {
    return sqlite3_close(db_);
}

void Storage::log(string message) {
    cout << path_ << " - " << message << endl;
}

