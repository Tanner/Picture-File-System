
#include "year_directory_entity.h"

using namespace pfs;
using namespace std;

YearDirectoryEntity::YearDirectoryEntity(string& path, string year) : DirectoryEntity(path), year_(year) {

}

int YearDirectoryEntity::readdir(void *buf, fuse_fill_dir_t filler, off_t offset, struct fuse_file_info *fi) {
    DirectoryEntity::readdir(buf, filler, offset, fi);

    filler(buf, "January", NULL, 0);

    return 0;
}

int YearDirectoryEntity::getattr(struct stat* stbuf) {
	DirectoryEntity::getattr(stbuf);

	return 0;
}

