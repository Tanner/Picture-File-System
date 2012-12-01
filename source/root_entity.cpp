
#include "root_entity.h"

using namespace pfs;
using namespace std;

RootEntity::RootEntity(string& path) : DirectoryEntity(path) {

}

int RootEntity::readdir(void *buf, fuse_fill_dir_t filler, off_t offset, struct fuse_file_info *fi) {
    DirectoryEntity::readdir(buf, filler, offset, fi);

    filler(buf, "Dates", NULL, 0);

    return 0;
}

int RootEntity::getattr(struct stat* stbuf) {
	DirectoryEntity::getattr(stbuf);

	return 0;
}

