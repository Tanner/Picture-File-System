
#ifndef DIRECTORY_ENTITY_H_
#define DIRECTORY_ENTITY_H_

#include "entity.h"

namespace pfs {
	using namespace std;

	class DirectoryEntity : public Entity {
	public:
		DirectoryEntity(string& path);
		int getattr(struct stat* stbuf);
		int read(char* buf, size_t size, off_t offset, struct fuse_file_info* fi);
	};
}

#endif