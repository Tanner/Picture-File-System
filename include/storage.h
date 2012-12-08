
#ifndef STORAGE_H_
#define STORAGE_H_

#include <string>
#include <vector>
#include <sqlite3.h>

#include "photo.h"

namespace pfs {
    using namespace std;

    class Photo;

    class Storage {
    public:
        virtual ~Storage();
        Storage(string path);
        int add_picture(Photo& photo);
        int rename_picture(Photo& photo, string new_name);
        int set_data_for_photo(int id, string& data);
        vector<int> get_years();
        vector<int> get_months(int year);
        vector<Photo> get_photos(int year, int month);
        string get_data_for_photo(int id);
        int delete_photo(int id);
        string get_path() {
            return path_;
        }
        virtual void open();
        virtual int close();
    protected:
        string path_;
        sqlite3* db_;
    private:
        Storage* clone();
        string get_database_path();
        void log(string message);
    };
}

#endif

