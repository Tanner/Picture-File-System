
#ifndef STORAGE_H_
#define STORAGE_H_

#include <string>
#include <vector>
#include <sqlite3.h>

#include "photo.h"

namespace pfs {
    using namespace std;

    class Storage {
    public:
        virtual ~Storage() { }
        int add_picture(Photo& photo);
        int rename_picture(Photo& photo, string new_name);
        int set_data_for_photo(int id, string& data);
        vector<int> get_years();
        vector<int> get_months(int year);
        vector<Photo> get_photos(int year, int month);
        string get_data_for_photo(int id);
        string get_path() {
            return path_;
        }
    private:
        Storage(string path);
        sqlite3* open();
        string get_database_path();

        string path_;
    };
}

#endif

