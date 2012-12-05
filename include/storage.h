
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
        static int add_picture(Photo photo);
        static int rename_picture(Photo photo, string new_name);
        static vector<int> get_years();
        static vector<int> get_months(int year);
        static vector<Photo> get_photos(int year, int month);
        static string get_data_for_photo(int id);
    private:
        static sqlite3* open();
        static string get_database_path();
    };
}

#endif

