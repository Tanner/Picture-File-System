
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
		static unique_ptr<Entity> entity_for_path(string path);
		
		virtual int getattr(struct stat* stbuf) = 0;
		
		virtual int read(char* buf, size_t size, off_t offset, struct fuse_file_info* fi) = 0;
		
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