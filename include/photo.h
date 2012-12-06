
#ifndef PHOTO_H_
#define PHOTO_H_

#include <string>
#include <memory>

#include "storage.h"

namespace pfs {
    using namespace std;

    class Storage;

    class Photo {
    public:
        virtual ~Photo() { }

        Photo(int id, string& name, int size, time_t time, shared_ptr<Storage> storage);
        Photo(string& name, string& data, shared_ptr<Storage> storage);

        string data();
        int size();

        void set_data(string& data);
        
        int get_id();
        string get_name();
        int get_month();
        int get_year();
        struct tm get_time();
    protected:
        int id_;
        string name_;
        string data_;
        int size_;
        struct tm time_;
        shared_ptr<Storage> storage_;
    };
}

#endif


