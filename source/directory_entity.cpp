
#include "directory_entity.h"

using namespace pfs;
using namespace std;

DirectoryEntity::DirectoryEntity(string& path) : Entity(path) {

}

int DirectoryEntity::readdir(void *buf, fuse_fill_dir_t filler, off_t offset, struct fuse_file_info *fi) {
    filler(buf, ".", NULL, 0);
    filler(buf, "..", NULL, 0);

    return 0;
}

int DirectoryEntity::getattr(struct stat* stbuf) {
	stbuf->st_mode = S_IFDIR | permissions_;
	stbuf->st_nlink = 2;

	return 0;
}

int DirectoryEntity::read(char* buf, size_t size, off_t offset, struct fuse_file_info* fi) {
	return 0;	
}

