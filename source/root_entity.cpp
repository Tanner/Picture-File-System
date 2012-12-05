
#include <iostream>

#include "root_entity.h"
#include "dates_directory_entity.h"
#include "new_file_entity.h"
#include "null_entity.h"
#include "storage.h"

using namespace pfs;
using namespace std;

RootEntity* RootEntity::singleton = NULL;

RootEntity* RootEntity::get() {
    if (RootEntity::singleton == NULL) {
        RootEntity::singleton = new RootEntity();
    }

    return RootEntity::singleton;
}

RootEntity::RootEntity() : DirectoryEntity("") {
    children_.push_back(shared_ptr<Entity>(new DatesDirectoryEntity("Dates")));
}

Entity* RootEntity::clone() {
    return new RootEntity(*this);
}

shared_ptr<Entity> RootEntity::route_path(string path) {
	if (pfs::root_for_path(path) == name_) {
        return shared_ptr<Entity>(clone());
    }

    vector<shared_ptr<Entity> > children(get_children());
    for (auto i = children.begin(); i != children.end(); ++i) {
        if (i->get()->get_name() == root_for_path(path)) {
            if (i->get()->get_name() == path.erase(0, 1)) {
                return *i;
            }

            return i->get()->route_path(path, pfs::deeper_path(path)); 
        }
    }

	if (pfs::path_depth(path) == 0) {
		return shared_ptr<Entity>(new NewFileEntity(pfs::root_for_path(path)));
	}

    return shared_ptr<Entity>(new NullEntity(path));
}

vector<shared_ptr<Entity> > RootEntity::get_children() {
    return children_;
}

void RootEntity::add_file(shared_ptr<Entity> entity) {
	children_.push_back(entity);
}

void RootEntity::remove_file(shared_ptr<Entity> entity) {
    for (auto i = children_.begin(); i != children_.end(); ++i) {
        if ((*i)->get_name() == entity->get_name()) {
            children_.erase(i);
            break;
        }
    }
}
