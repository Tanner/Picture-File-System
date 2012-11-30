
#ifndef ROOT_ENTITY_H_
#define ROOT_ENTITY_H_

#include "directory_entity.h"

namespace pfs {
	using namespace std;

	class RootEntity : public DirectoryEntity {
	public:
		RootEntity(string& path);
		int getattr(struct stat* stbuf);
		int read(char* buf, size_t size, off_t offset, struct fuse_file_info* fi);
	};
}

#endif