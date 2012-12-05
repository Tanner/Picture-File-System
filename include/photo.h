
#ifndef PHOTO_H_
#define PHOTO_H_

#include <string>

namespace pfs {
    using namespace std;

    class Photo {
    public:
        virtual ~Photo() { }

        Photo(int id, string& name, int size, time_t time);
        Photo(string& name, string& data);

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
    };
}

#endif


