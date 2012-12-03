
#include <iostream>

#include "root_entity.h"
#include "dates_directory_entity.h"
#include "null_entity.h"
#include "storage.h"

using namespace pfs;
using namespace std;

RootEntity::RootEntity() : DirectoryEntity("/") {
    children_.push_back(shared_ptr<Entity>(new DatesDirectoryEntity("Dates")));
}

Entity* RootEntity::clone() {
    return new RootEntity(*this);
}

shared_ptr<Entity> RootEntity::route_path(string path) {
    return Entity::route_path(path, path);
}

vector<shared_ptr<Entity> > RootEntity::get_children() {
    return children_;
}
