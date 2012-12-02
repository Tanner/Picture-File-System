
#include "photo.h"

using namespace pfs;
using namespace std;

Photo::Photo(string& name, const void* data, size_t size) : name_(name), data_(data), size_(size) {

}

string Photo::get_name() {
    return name_;
}

const void* Photo::get_data() {
    return data_;
}

int Photo::get_size() {
    return size_;
}
