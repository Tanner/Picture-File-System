
#include <iostream>

#include "root_entity.h"
#include "dates_directory_entity.h"
#include "null_entity.h"
#include "storage.h"

using namespace pfs;
using namespace std;

shared_ptr<RootEntity> RootEntity::get() { 
    static shared_ptr<RootEntity> singleton(new RootEntity("/"));
    return singleton;
}

RootEntity::RootEntity(string path) : DirectoryEntity(path) {
    children_.push_back(shared_ptr<Entity>(new DatesDirectoryEntity("Dates")));
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
