
#include "month_directory_entity.h"

using namespace pfs;
using namespace std;

MonthDirectoryEntity::MonthDirectoryEntity(string& path, string year, string month) : DirectoryEntity(path), year_(year), month_(month) {

}

int MonthDirectoryEntity::readdir(void *buf, fuse_fill_dir_t filler, off_t offset, struct fuse_file_info *fi) {
    DirectoryEntity::readdir(buf, filler, offset, fi);

    filler(buf, "hello", NULL, 0);

    return 0;
}

int MonthDirectoryEntity::getattr(struct stat* stbuf) {
	DirectoryEntity::getattr(stbuf);

	return 0;
}

