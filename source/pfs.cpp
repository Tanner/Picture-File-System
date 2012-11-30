
#include <iostream>
#include <fstream>

#include "entity.h"

using namespace pfs;

static int getattr(const char *path, struct stat *stbuf) {
    memset(stbuf, 0, sizeof(struct stat));

    auto_ptr<Entity> entity(Entity::entity_for_path(path));
    return entity.get()->getattr(stbuf);
}

static int readdir(const char *path, void *buf, fuse_fill_dir_t filler, off_t offset, struct fuse_file_info *fi) {
    auto_ptr<Entity> entity(Entity::entity_for_path(path));
    return entity.get()->readdir(buf, filler, offset, fi);
}

static int open(const char *path, struct fuse_file_info *fi) {
    auto_ptr<Entity> entity(Entity::entity_for_path(path));
    return entity.get()->open(fi);
}

static int read(const char *path, char *buf, size_t size, off_t offset, struct fuse_file_info *fi) {
    auto_ptr<Entity> entity(Entity::entity_for_path(path));
    return entity.get()->read(buf, size, offset, fi);
}

static struct fuse_operations operations;

int main(int argc, char **argv) {
    operations.getattr = getattr;
    operations.readdir = readdir;
    operations.open = open;
    operations.read = read;

    return fuse_main(argc, argv, &operations, NULL);
}
