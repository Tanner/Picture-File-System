
#ifndef NULL_ENTITY_H_
#define NULL_ENTITY_H_

#include "entity.h"

namespace pfs {
    using namespace std;
    
    class NullEntity : public Entity {
    public:
        NullEntity(string name);
        Entity* clone();
        shared_ptr<Entity> route_path(string full_path, string relative_path);
        int getattr(struct stat* stbuf);
        int readdir(void *buf, fuse_fill_dir_t filler, off_t offset, struct fuse_file_info *fi);
        int chmod(mode_t mode);
        int chown(uid_t uid, gid_t gid);
        int truncate(off_t size);
        int utimens(const struct timespec ts[2]);
        int access(int mask);
        int open(struct fuse_file_info* fi);
        int read(char* buf, size_t size, off_t offset, struct fuse_file_info* fi);
        int write(const char* buf, size_t size, off_t off, struct fuse_file_info* fi);
        int mknod(mode_t mode, dev_t rdev);
        int release(struct fuse_file_info* fi);
        int rename(string new_name);
    };
}

#endif

