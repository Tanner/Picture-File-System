
#include "dates_directory_entity.h"

using namespace pfs;
using namespace std;

DatesDirectoryEntity::DatesDirectoryEntity(string& path) : DirectoryEntity(path) {

}

int DatesDirectoryEntity::readdir(void *buf, fuse_fill_dir_t filler, off_t offset, struct fuse_file_info *fi) {
    DirectoryEntity::readdir(buf, filler, offset, fi);    

    filler(buf, "2010", NULL, 0);

    return 0;
}

int DatesDirectoryEntity::getattr(struct stat* stbuf) {
	stbuf->st_mode = S_IFDIR | permissions_;
	stbuf->st_nlink = 2;

	return 0;
}

