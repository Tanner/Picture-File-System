
#include "photo.h"

using namespace pfs;
using namespace std;

Photo::Photo(string& name, string data) : name_(name), data_(data) {

}

string Photo::get_name() {
    return name_;
}

const char* Photo::data() {
    return data_.c_str();
}

int Photo::size() {
    return data_.length();
}

int Photo::get_month() {
    return 12;
}

int Photo::get_year() {
    return 1261;
}
