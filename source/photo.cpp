
#include "photo.h"

using namespace pfs;
using namespace std;

Photo::Photo(string& name, const char* data, size_t size) : name_(name), data_(data), size_(size) {

}

string Photo::get_name() {
    return name_;
}

const char* Photo::get_data() {
    return data_;
}

int Photo::get_size() {
    return size_;
}

int Photo::get_month() {
    return 12;
}

int Photo::get_year() {
    return 1261;
}
