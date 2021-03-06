
#include <iostream>
#include <vector>

#include "entity.h"
#include "regex_matcher.h"
#include "directory_entity.h"
#include "root_entity.h"
#include "file_entity.h"
#include "picture_entity.h"
#include "null_entity.h"
#include "storage_directory_entity.h"
#include "year_directory_entity.h"
#include "month_directory_entity.h"

using namespace pfs;
using namespace std;

Entity::Entity(string name) : name_(name) {
    permissions_ = 755;
}

shared_ptr<Entity> Entity::route_path(string full_path, string relative_path) {    
    if (relative_path.length() == 0) {
        return shared_ptr<Entity>(clone());
    }

    vector<shared_ptr<Entity> > children(get_children());
    for (auto i = children.begin(); i != children.end(); ++i) {
        if (i->get()->get_name() == pfs::root_for_path(relative_path)) {
            if (i->get()->get_name() == relative_path.erase(0, 1)) {
                return *i;
            }

            return i->get()->route_path(full_path, pfs::deeper_path(relative_path)); 
        }
    }
    
    return shared_ptr<Entity>(new NullEntity(relative_path));
}

vector<shared_ptr<Entity> > Entity::get_children() {
    return vector<shared_ptr<Entity> >();
}

int Entity::getattr(struct stat* stbuf) {
    return -1;
}

int Entity::readdir(void *buf, fuse_fill_dir_t filler, off_t offset, struct fuse_file_info *fi) {
    return -1;
}

int Entity::chmod(mode_t mode) {
    return -1;
}

int Entity::chown(uid_t uid, gid_t gid) {
    return -1;
}

int Entity::truncate(off_t size) {
    return -1;
}

int Entity::utimens(const struct timespec ts[2]) {
    return -1;
}

int Entity::access(int mask) {
    return -1;
}

int Entity::open(struct fuse_file_info* fi) {
    return -1;
}

int Entity::read(char* buf, size_t size, off_t off, struct fuse_file_info* fi) {
    return -1;
}

int Entity::write(const char* buf, size_t size, off_t off, struct fuse_file_info* fi) {
    return -1;
}

int Entity::mknod(mode_t mode, dev_t rdev) {
    return -1;
}

int Entity::release(struct fuse_file_info* fi) {
    return -1;
}

int Entity::rename(string new_name) {
    return -1;
}
