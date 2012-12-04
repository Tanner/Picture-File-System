
#ifndef PHOTO_H_
#define PHOTO_H_

#include <string>

namespace pfs {
    using namespace std;

    class Photo {
    public:
        virtual ~Photo() { }

        Photo(string& name, const char* data, size_t size);

        string get_name();
        const char* get_data();
        int get_size();
        int get_month();
        int get_year();
    protected:
        string name_;
        const char* data_;
        int size_;
    };
}

#endif

