
#ifndef NEW_FILE_ENTITY_H_
#define NEW_FILE_ENTITY_H_

#include "file_entity.h"

namespace pfs {
	using namespace std;

	class NewFileEntity : public Entity {
	public:
		NewFileEntity(string name);
		Entity* clone();
		int getattr(struct stat* stbuf);
		int access(int mask);
		int open(struct fuse_file_info* fi);
		int mknod(mode_t mode, dev_t rdev);
	protected:
		const char* content();
		size_t length();
	private:
		string content_;
	};
}

#endif