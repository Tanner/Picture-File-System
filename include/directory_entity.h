
#ifndef DIRECTORY_ENTITY_H_
#define DIRECTORY_ENTITY_H_

#include "entity.h"

namespace pfs {
	using namespace std;

	class DirectoryEntity : public Entity {
	public:
		DirectoryEntity(string name);
        int readdir(void *buf, fuse_fill_dir_t filler, off_t offset, struct fuse_file_info *fi);
		int getattr(struct stat* stbuf);
		int access(int mask);
		int read(char* buf, size_t size, off_t offset, struct fuse_file_info* fi);
	};
}

#endif

