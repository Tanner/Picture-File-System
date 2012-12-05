
#include <libexif/exif-data.h>
#include <libexif/exif-tag.h>
#include <iostream>

#include "photo.h"
#include "storage.h"

using namespace pfs;
using namespace std;

Photo::Photo(int id, string& name, int size, time_t time) : id_(id), name_(name), size_(size) {
    struct tm* temp_time = gmtime(&time);
    time_ = *temp_time;;
}

Photo::Photo(string& name, string& data) : name_(name), data_(data) {
    id_ = -1;
    size_ = data.length();
    
    // Get time/date from EXIF data
    ExifData *exif_data = exif_data_new_from_data((const unsigned char*) data.c_str(), size());
    exif_data_fix(exif_data);
    exif_data_dump(exif_data);

    ExifEntry *entry = exif_content_get_entry(exif_data->ifd[EXIF_IFD_EXIF], EXIF_TAG_DATE_TIME_ORIGINAL);

    if (entry) {
        // EXIF tag exists
        char buf[1024];

        exif_entry_get_value(entry, buf, sizeof(buf));

        strptime(buf, "%Y:%m:%d %H:%M:%S", &time_);
    } else {
        // EXIF tag does not exist, use something else
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
        data_ = Storage::get_data_for_photo(id_);
    }

    return data_;
}

int Photo::size() {
    return size_;
}

void Photo::set_data(string& data) {
    data_ = data;
    Storage::set_data_for_photo(id_, data_);
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

