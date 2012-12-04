
#ifndef PHOTO_H_
#define PHOTO_H_

#include <string>

namespace pfs {
    using namespace std;

    class Photo {
    public:
        virtual ~Photo() { }

        Photo(string& name, string data);

        const char* data();
        int size();
        
        string get_name();
        int get_month();
        int get_year();
    protected:
        string name_;
        string data_;
    };
}

#endif

