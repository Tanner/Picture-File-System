
#include "file_entity.h"

using namespace pfs;
using namespace std;

FileEntity::FileEntity(string& path) : Entity(path) {

}

int FileEntity::getattr(struct stat* stbuf) {
    stbuf->st_mode = S_IFREG | permissions_;
    stbuf->st_nlink = 1;
    stbuf->st_size = length();

    return 0;
}

int FileEntity::read(char* buf, size_t size, off_t offset, struct fuse_file_info* fi) {
    const char* data(content());
    size_t len(length());

    if (offset < (long)len) {
        if (offset + size > len) {
            size = len - offset; 
        }

        memcpy(buf, data + offset, size);
    } else {
        size = 0;
    }

    return size;
}

