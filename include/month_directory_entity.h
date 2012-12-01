
#ifndef MONTH_DIRECTORY_ENTITY_H_
#define MONTH_DIRECTORY_ENTITY_H_

#include "directory_entity.h"

namespace pfs {
	using namespace std;

	class MonthDirectoryEntity : public DirectoryEntity {
	public:
		MonthDirectoryEntity(string& path, string year, string month);
        int readdir(void *buf, fuse_fill_dir_t filler, off_t offset, struct fuse_file_info *fi);
		int getattr(struct stat* stbuf);
    private:
        string year_;
        string month_;
	};
}

#endif

