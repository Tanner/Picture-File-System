
#include <iostream>
#include <vector>

#include "entity.h"
#include "regex_matcher.h"
#include "directory_entity.h"
#include "root_entity.h"
#include "file_entity.h"
#include "picture_entity.h"
#include "null_entity.h"
#include "dates_directory_entity.h"
#include "year_directory_entity.h"
#include "month_directory_entity.h"

using namespace pfs;
using namespace std;

Entity::Entity(string name) : name_(name) {

}

shared_ptr<Entity> Entity::route_path(string full_path, string relative_path) {
    string root(root_for_path(relative_path));
    
    if (root == name_) {
        return shared_ptr<Entity>(clone());
    }

    vector<shared_ptr<Entity> > children(get_children());
    for (vector<shared_ptr<Entity> >::iterator i = children.begin(); i != children.end(); ++i) {
        if (i->get()->get_name() == relative_path) {
            return i->get()->route_path(full_path, relative_path.substr(root.length())); 
        }
    }
    
    return shared_ptr<Entity>(new NullEntity(relative_path));
}

vector<shared_ptr<Entity> > Entity::get_children() {
    return vector<shared_ptr<Entity> >();
}

int Entity::getattr(struct stat* stbuf) {
    return -ENOENT;
}

int Entity::read(char* buf, size_t size, off_t offset, struct fuse_file_info* fi) {
    return -ENOENT;
}

int Entity::readdir(void *buf, fuse_fill_dir_t filler, off_t offset, struct fuse_file_info *fi) {
    return -ENOENT;
}

int Entity::open(struct fuse_file_info* fi) {
    if ((fi->flags & 3) != O_RDONLY) {
        return -EACCES;
    }

    return 0;
}

int Entity::mknod(mode_t mode, dev_t rdev) {
    return -ENOENT;
}

