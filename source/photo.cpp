
#include <libexif/exif-data.h>
#include <libexif/exif-tag.h>
#include <iostream>

#include "photo.h"
#include "storage.h"

using namespace pfs;
using namespace std;

Photo::Photo(int id, string& name, int size, time_t time, shared_ptr<Storage> storage) : id_(id), name_(name), size_(size), storage_(storage) {
    struct tm* temp_time = gmtime(&time);
    time_ = *temp_time;;
}

Photo::Photo(string& name, string& data, shared_ptr<Storage> storage) : name_(name), data_(data), storage_(storage) {
    id_ = -1;
    size_ = data.length();
    
    // Get time/date from EXIF data
    ExifData *exif_data = exif_data_new_from_data((const unsigned char*) data.c_str(), size());
    exif_data_fix(exif_data);

    ExifEntry *entry = exif_content_get_entry(exif_data->ifd[EXIF_IFD_EXIF], EXIF_TAG_DATE_TIME_ORIGINAL);

    if (entry) {
        // EXIF tag exists
        char buf[1024];

        exif_entry_get_value(entry, buf, sizeof(buf));

        strptime(buf, "%Y:%m:%d %H:%M:%S", &time_);
    } else {
        // EXIF tag does not exist, use something else
        time_t raw_time;

        time(&raw_time);
        time_ = *localtime(&raw_time);

        cout << asctime(&time_) << endl;
    }
}

int Photo::get_id() {
    return id_;
}

string Photo::get_name() {
    return name_;
}

string Photo::data() {
    if (data_.length() == 0) {
        data_ = storage_->get_data_for_photo(id_);
    }

    return data_;
}

int Photo::size() {
    return size_;
}

void Photo::set_data(string& data) {
    data_ = data;
    storage_->set_data_for_photo(id_, data_);
}

void Photo::set_name(string &name) {
    name_ = name;
}

int Photo::get_month() {
    return time_.tm_mon;
}

int Photo::get_year() {
    return time_.tm_year + 1900;
}

struct tm Photo::get_time() {
    return time_;
}

void Photo::set_time(struct tm time) {
    time_ = time;
}

