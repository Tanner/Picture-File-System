
#include "root_entity.h"

using namespace pfs;
using namespace std;

RootEntity::RootEntity(string& path) : DirectoryEntity(path) {

}

int RootEntity::getattr(struct stat* stbuf) {
	DirectoryEntity::getattr(stbuf);

	return 0;
}

int RootEntity::read(char* buf, size_t size, off_t offset, struct fuse_file_info* fi) {
	return 0;
}

