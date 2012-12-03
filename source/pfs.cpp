
#include <iostream>
#include <fstream>

#include "root_entity.h"

using namespace pfs;

namespace pfs {
    int getattr(const char* path, struct stat* stbuf);
    int readdir(const char* path, void* buf, fuse_fill_dir_t filler, off_t offset, struct fuse_file_info* fi);
    int open(const char* path, struct fuse_file_info* fi);
    int read(const char* path, char* buf, size_t size, off_t offset, struct fuse_file_info* fi);
    int mknod(const char* path, mode_t mode, dev_t rdev);
}

static struct fuse_operations operations;

int main(int argc, char** argv) {
    operations.getattr = pfs::getattr;
    operations.readdir = pfs::readdir;
    operations.open = pfs::open;
    operations.read = pfs::read;
    operations.mknod = pfs::mknod;

    return fuse_main(argc, argv, &operations, NULL);
}

int pfs::getattr(const char* path, struct stat* stbuf) {
    memset(stbuf, 0, sizeof(struct stat));

    shared_ptr<Entity> entity(RootEntity().route_path(path));
    return entity->getattr(stbuf);
}

int pfs::readdir(const char* path, void* buf, fuse_fill_dir_t filler, off_t offset, struct fuse_file_info* fi) {
    shared_ptr<Entity> entity(RootEntity().route_path(path));
    return entity->readdir(buf, filler, offset, fi);
}

int pfs::open(const char* path, struct fuse_file_info* fi) {
    shared_ptr<Entity> entity(RootEntity().route_path(path));
    return entity->open(fi);
}

int pfs::read(const char* path, char* buf, size_t size, off_t offset, struct fuse_file_info* fi) {
    shared_ptr<Entity> entity(RootEntity().route_path(path));
    return entity->read(buf, size, offset, fi);
}

int pfs::mknod(const char* path, mode_t mode, dev_t rdev) {
    shared_ptr<Entity> entity(RootEntity().route_path(path));
    return entity->mknod(mode, rdev);
}

