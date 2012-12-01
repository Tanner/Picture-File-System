
#include <iostream>
#include <stdlib.h>

#include "storage.h"

using namespace pfs;
using namespace std;

int Storage::add_picture(string name, const char* data, size_t size) {
    sqlite3 *db = open();

    // Init with default tables if they do not exist.
    char *create_table_query = "CREATE TABLE IF NOT EXISTS photos (name TEXT NOT NULL, size INTEGER NOT NULL, contents BLOB NOT NULL, year INTEGER NOT NULL, month TEXT NOT NULL)";
    sqlite3_exec(db, create_table_query, 0, 0, 0);

    return 0;
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
