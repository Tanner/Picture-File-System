
#include <libexif/exif-data.h>
#include <libexif/exif-tag.h>
#include <iostream>

#include "photo.h"

using namespace pfs;
using namespace std;

Photo::Photo(string& name, string data) : name_(name), data_(data) {
    // Try to get the EXIF data
    ExifData *exif_data = exif_data_new_from_data((const unsigned char*) data.c_str(), size());
    ExifEntry *entry = exif_content_get_entry(exif_data->ifd[EXIF_IFD_0], EXIF_TAG_DATE_TIME);

    if (entry) {
        char buf[1024];

        exif_entry_get_value(entry, buf, sizeof(buf));
        
        cout << "EXIF data found for" << name << endl;
    } else {
        cout << "EXIF data not found for " << name << endl;
    }
}

string Photo::get_name() {
    return name_;
}

string Photo::data() {
    return data_;
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

