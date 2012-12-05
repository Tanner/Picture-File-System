
#include <libexif/exif-data.h>
#include <libexif/exif-tag.h>
#include <iostream>

#include "photo.h"
#include "storage.h"

using namespace pfs;
using namespace std;

Photo::Photo(int id, string& name, int size) : id_(id), name_(name), size_(size) {
    data_ = "";
    size_ = 0;
}

Photo::Photo(string& name, string& data) : name_(name), data_(data) {
    id_ = -1;
    size_ = data.length();
}

int Photo::get_id() {
    return id_;
}

string Photo::get_name() {
    return name_;
}

string Photo::data() {
    if (data_.length() == 0) {
        data_ = Storage::get_data_for_photo(id_);
        size_ = data_.length();
    }

    return data_;
}

int Photo::size() {
    return size_;
}

int Photo::get_month() {
    return 12;
}

int Photo::get_year() {
    return 1261;
}

