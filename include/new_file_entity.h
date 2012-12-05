
#ifndef NEW_FILE_ENTITY_H_
#define NEW_FILE_ENTITY_H_

#include "file_entity.h"

namespace pfs {
	using namespace std;

	class NewFileEntity : public FileEntity {
	public:
		NewFileEntity(string name);
		Entity* clone();
		int getattr(struct stat* stbuf);
		int chmod(mode_t mode);
		int chown(uid_t uid, gid_t gid);
		int truncate(off_t size);
		int utimens(const struct timespec ts[2]);
		int access(int mask);
		int open(struct fuse_file_info* fi);
		int write(const char* buf, size_t size, off_t off, struct fuse_file_info* fi);
		int mknod(mode_t mode, dev_t rdev);
		int release(struct fuse_file_info* fi);
	protected:
		string content();
		size_t length();
	private:
		string content_;
	};
}

#endif