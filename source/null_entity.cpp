
#include "null_entity.h"

using namespace pfs;
using namespace std;

NullEntity::NullEntity(string path) : Entity(path) {

}

Entity* NullEntity::clone() {
	return new NullEntity(*this);
}

shared_ptr<Entity> NullEntity::route_path(string full_path, string relative_path) {
    return shared_ptr<Entity>(new NullEntity(*this));
}

int NullEntity::getattr(struct stat* stbuf) {
    return -ENOENT;
}

int NullEntity::readdir(void *buf, fuse_fill_dir_t filler, off_t offset, struct fuse_file_info *fi) {
    return -ENOENT;
}

int NullEntity::chmod(mode_t mode) {
    return -ENOENT;
}

int NullEntity::chown(uid_t uid, gid_t gid) {
    return -ENOENT;
}

int NullEntity::truncate(off_t size) {
    return -ENOENT;
}

int NullEntity::utimens(const struct timespec ts[2]) {
    return -ENOENT;
}

int NullEntity::access(int mask) {
    return -ENOENT;
}

int NullEntity::open(struct fuse_file_info* fi) {
    return -ENOENT;
}

int NullEntity::read(char* buf, size_t size, off_t off, struct fuse_file_info* fi) {
    return -ENOENT;
}

int NullEntity::write(const char* buf, size_t size, off_t off, struct fuse_file_info* fi) {
    return -ENOENT;
}

int NullEntity::mknod(mode_t mode, dev_t rdev) {
    return -ENOENT;
}

int NullEntity::release(struct fuse_file_info* fi) {
    return -ENOENT;
}

int NullEntity::rename(string new_name) {
    return -ENOENT;
}
