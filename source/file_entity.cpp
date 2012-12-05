
#include "file_entity.h"

using namespace pfs;
using namespace std;

FileEntity::FileEntity(string name) : Entity(name) {

}

int FileEntity::getattr(struct stat* stbuf) {
    stbuf->st_mode = S_IFREG | permissions_;
    stbuf->st_nlink = 1;
    stbuf->st_size = length();

    return 0;
}

int FileEntity::access(int mask) {
    return 0;
}

int FileEntity::open(struct fuse_file_info* fi) {
    return 0;
}

int FileEntity::read(char* buf, size_t size, off_t offset, struct fuse_file_info* fi) {
    string data(content());
    size_t len(length());

    if (offset < (long)len) {
        if (offset + size > len) {
            size = len - offset; 
        }

        memcpy(buf, data.c_str() + offset, size);
    } else {
        size = 0;
    }

    return size;
}

