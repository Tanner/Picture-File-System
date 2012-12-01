
#ifndef DATES_DIRECTORY_ENTITY_H_
#define DATES_DIRECTORY_ENTITY_H_

#include "directory_entity.h"

namespace pfs {
	using namespace std;

	class DatesDirectoryEntity : public DirectoryEntity {
	public:
		DatesDirectoryEntity(string& path);
        int readdir(void *buf, fuse_fill_dir_t filler, off_t offset, struct fuse_file_info *fi);
		int getattr(struct stat* stbuf);
	};
}

#endif

