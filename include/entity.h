
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
        virtual int access(int mask);
		virtual int read(char* buf, size_t size, off_t offset, struct fuse_file_info* fi);
		virtual int open(struct fuse_file_info* fi);
        virtual int mknod(mode_t mode, dev_t rdev);
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
	};
}

#endif

