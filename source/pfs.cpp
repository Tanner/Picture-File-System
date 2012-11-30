
#include <iostream>
#include <fstream>

#include "entity.h"

using namespace pfs;

static const char *hello_str = "Hello World Kitty!\n";
static const char *hello_path = "/hello";

// static ofstream log("pfs.log", ios::in | ios::out | ios::trunc);

static int hello_getattr(const char *path, struct stat *stbuf) {
    // if (!log.is_open()) {
    //     log.open("pfs.log", ios::in | ios::out | ios::trunc);
    // }
    cout << path << endl;
    auto_ptr<Entity> entity(Entity::entity_for_path(path));
    return entity.get()->getattr(stbuf);

    // int res = 0;

    // memset(stbuf, 0, sizeof(struct stat));

    // if (strcmp(path, "/") == 0) {
    //     stbuf->st_mode = S_IFDIR | 0755;
    //     stbuf->st_nlink = 2;
    // } else if (strcmp(path, hello_path) == 0) {
    //     stbuf->st_mode = S_IFREG | 0444;
    //     stbuf->st_nlink = 1;
    //     stbuf->st_size = strlen(hello_str);
    // } else {
    //     res = -ENOENT;
    // }

    // return res;
}

static int hello_readdir(const char *path, void *buf, fuse_fill_dir_t filler, off_t offset, struct fuse_file_info *fi) {
    (void) offset;
    (void) fi;

    if (strcmp(path, "/") != 0) {
        return -ENOENT;
    }

    filler(buf, ".", NULL, 0);
    filler(buf, "..", NULL, 0);
    filler(buf, hello_path + 1, NULL, 0);

    return 0;
}

static int hello_open(const char *path, struct fuse_file_info *fi) {
    if (strcmp(path, hello_path) != 0) {
        return -ENOENT;
    } else if ((fi->flags & 3) != O_RDONLY) {
        return -EACCES;
    } else {
        return 0;
    }
}

static int hello_read(const char *path, char *buf, size_t size, off_t offset, struct fuse_file_info *fi) {
    size_t len;

    (void) fi;

    if (strcmp(path, hello_path) != 0) {
        return -ENOENT;
    }

    len = strlen(hello_str);

    if (offset < len) {
        if (offset + size > len) {
            size = len - offset;
        }

        memcpy(buf, hello_str + offset, size);
    } else {
        size = 0;
    }

    return size;
}

static struct fuse_operations hello_operations;

int main(int argc, char **argv) {
    hello_operations.getattr = hello_getattr;
    hello_operations.readdir = hello_readdir;
    hello_operations.open = hello_open;
    hello_operations.read = hello_read;

    return fuse_main(argc, argv, &hello_operations, NULL);
}
