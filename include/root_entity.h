
#ifndef ROOT_ENTITY_H_
#define ROOT_ENTITY_H_

#include "directory_entity.h"

namespace pfs {
	using namespace std;

	class RootEntity : public DirectoryEntity {
	public:
        static shared_ptr<RootEntity> get();
        shared_ptr<Entity> route_path(string full_path);
        vector<Entity> get_children();
        int readdir(void *buf, fuse_fill_dir_t filler, off_t offset, struct fuse_file_info *fi);
		int getattr(struct stat* stbuf);
        int mknod(mode_t mode, dev_t rdev);
    private:
		RootEntity(string name);
        vector<Entity> children_;
	};
}

#endif

