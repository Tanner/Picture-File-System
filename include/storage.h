
#ifndef STORAGE_H_
#define STORAGE_H_

#include <string>
#include <vector>
#include <sqlite3.h>

namespace pfs {
    using namespace std;

    class Storage {
    public:
        static int add_picture(string name, const char* data, size_t size, int year, string month);
        static vector<int> get_years();
    private:
        static sqlite3* open();
        static string get_database_path();
    };
}

#endif

