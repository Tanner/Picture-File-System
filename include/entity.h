
#ifndef ENTITY_H_
#define ENTITY_H_

#include <fuse.h>
#include <stdio.h>
#include <string.h>
#include <errno.h>
#include <fcntl.h>
#include <string>
#include <memory>
#include <vector>

#include "util.h"
#include "storage.h"

namespace pfs {
	using namespace std;

	class Entity {
	public:
		virtual ~Entity() { }
		virtual Entity* clone() = 0;
        virtual shared_ptr<Entity> route_path(string full_path, string relative_path);
        virtual vector<shared_ptr<Entity> > get_children();
		virtual int getattr(struct stat* stbuf);
        virtual int readdir(void *buf, fuse_fill_dir_t filler, off_t offset, struct fuse_file_info *fi);
        virtual int chmod(mode_t mode);
        virtual int chown(uid_t uid, gid_t gid);
        virtual int truncate(off_t size);
        virtual int utimens(const struct timespec ts[2]);
        virtual int access(int mask);
		virtual int open(struct fuse_file_info* fi);
		virtual int read(char* buf, size_t size, off_t offset, struct fuse_file_info* fi);
        virtual int write(const char* buf, size_t size, off_t off, struct fuse_file_info* fi);
        virtual int mknod(mode_t mode, dev_t rdev);
        virtual int release(struct fuse_file_info* fi);
        virtual int rename(string new_name);
        void set_storage(shared_ptr<Storage> storage) {
            storage_ = storage;
        }
        string get_name() {
            return name_;
        }
		void set_permissions(int permissions) {
			permissions_ = permissions;
		}
	protected:
		Entity(string name);
        string name_;
		unsigned int permissions_;
        shared_ptr<Storage> storage_;
	};
}

#endif

