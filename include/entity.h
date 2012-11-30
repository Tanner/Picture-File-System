
#ifndef ENTITY_H_
#define ENTITY_H_

#include <fuse.h>
#include <stdio.h>
#include <string.h>
#include <errno.h>
#include <fcntl.h>

#include <string>
#include <memory>

namespace pfs {
	using namespace std;

	class Entity {
	public:
		virtual ~Entity() { }
		
		static auto_ptr<Entity> entity_for_path(string path);
		
		virtual int getattr(struct stat* stbuf) = 0;

        virtual int readdir(void *buf, fuse_fill_dir_t filler, off_t offset, struct fuse_file_info *fi);
		
		virtual int read(char* buf, size_t size, off_t offset, struct fuse_file_info* fi) = 0;

		virtual int open(struct fuse_file_info* fi);
		
		void set_permissions(int permissions) {
			permissions_ = permissions;
		}
	protected:
		Entity(string& path);
		string path_;
		unsigned int permissions_;
	};
}

#endif

