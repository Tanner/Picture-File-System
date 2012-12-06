
#include "root_entity.h"
#include "picture_entity.h"
#include "storage.h"

using namespace pfs;
using namespace std;

PictureEntity::PictureEntity(Photo& p) : FileEntity(p.get_name()), photo_(p) {
    
}

Entity* PictureEntity::clone() {
    return new PictureEntity(*this);
}

size_t PictureEntity::length() {
    return photo_.size();
}

string PictureEntity::content() {
    return photo_.data();
}

int PictureEntity::getattr(struct stat* stbuf) {
    int result;
    
    if ((result = FileEntity::getattr(stbuf)) < 0) {
        return result;
    }

    struct tm time = photo_.get_time();
    time_t epoch_time = mktime(&time);

    stbuf->st_atime = epoch_time;
    stbuf->st_mtime = epoch_time;
    stbuf->st_ctime = epoch_time;

    return 0;
}

int PictureEntity::rename(string new_name) {
    if (is_file_private(name_) && !is_file_private(new_name)) {
        photo_.data();
        storage_->delete_photo(photo_.get_id());

        storage_ = RootEntity::get()->get_public_storage();
        photo_.set_name(new_name);

        storage_->add_picture(photo_);

        return 0;
    } else if (!is_file_private(name_) && is_file_private(new_name)) {
        photo_.data();
        storage_->delete_photo(photo_.get_id());

        storage_ = RootEntity::get()->get_private_storage();
        photo_.set_name(new_name);

        storage_->add_picture(photo_);

        return 0;
    }

	storage_->rename_picture(photo_, new_name);

	return 0;
}

int PictureEntity::write(const char* buf, size_t size, off_t offset, struct fuse_file_info* fi) {
    // string data(content());
    // char* data_buf = (char*)calloc(sizeof(char), data.length());
    // memcpy(data_buf, data.c_str(), data.length());

    // size_t len(length());

    // if (offset < (long)len) {
    //     if (offset + size > len) {
    //         size = len - offset; 
    //     }

    //     memcpy(data_buf + offset, buf, size);

    //     photo_.set_data(string(data_buf, );
    // }

    // free(data_buf);

    return -1;
}
