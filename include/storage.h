
#ifndef STORAGE_H_
#define STORAGE_H_

#include <string>
#include <sqlite3.h>

namespace pfs {
    using namespace std;

    class Storage {
    public:
        static int add_picture(string name, const char* data, size_t size);
    private:
        static sqlite3* open();
        static string get_database_path();
    };
}

#endif

