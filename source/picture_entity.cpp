
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

int PictureEntity::rename(string new_name) {
	Storage::rename_picture(photo_, new_name);

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
