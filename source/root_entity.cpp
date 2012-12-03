
#include <iostream>

#include "root_entity.h"
#include "null_entity.h"
#include "storage.h"

#include "util.h"

using namespace pfs;
using namespace std;

shared_ptr<RootEntity> RootEntity::get() { 
    static shared_ptr<RootEntity> singleton(new RootEntity("/"));
    return singleton;
}

RootEntity::RootEntity(string path) : DirectoryEntity(path) {
    children_.push_back(shared_ptr<Entity>(new DirectoryEntity("Dates")));
}

shared_ptr<Entity> RootEntity::route_path(string path) {
    string root(root_for_path(path));
    
    if (path == name_) {
        return RootEntity::get();
    }

    vector<shared_ptr<Entity> > children(get_children());
    for (vector<shared_ptr<Entity> >::iterator i = children.begin(); i != children.end(); ++i) {
        if (i->get()->get_name() == root) {
            return i->get()->route_path(path, path); 
        }
    }
    
    return shared_ptr<Entity>(new NullEntity(path));
}

vector<shared_ptr<Entity> > RootEntity::get_children() {
    return children_;
}

int RootEntity::readdir(void *buf, fuse_fill_dir_t filler, off_t offset, struct fuse_file_info *fi) {
    DirectoryEntity::readdir(buf, filler, offset, fi);

    vector<shared_ptr<Entity> > children(get_children());
    for (vector<shared_ptr<Entity> >::iterator i = children.begin(); i != children.end(); ++i) {
        filler(buf, i->get()->get_name().c_str(), NULL, 0); 
    }

    return 0;
}

int RootEntity::getattr(struct stat* stbuf) {
	DirectoryEntity::getattr(stbuf);

	return 0;
}

int RootEntity::mknod(mode_t mode, dev_t rdev) {
    return 0;
}

