
#ifndef YEAR_DIRECTORY_ENTITY_H_
#define YEAR_DIRECTORY_ENTITY_H_

#include "directory_entity.h"

namespace pfs {
	using namespace std;

	class YearDirectoryEntity : public DirectoryEntity {
	public:
		YearDirectoryEntity(string& path, string year);
        int readdir(void *buf, fuse_fill_dir_t filler, off_t offset, struct fuse_file_info *fi);
		int getattr(struct stat* stbuf);
    private:
        string year_;
	};
}

#endif

