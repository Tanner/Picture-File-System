
#include <iostream>

#include "root_entity.h"
#include "storage_directory_entity.h"
#include "encrypted_storage_directory_entity.h"
#include "new_file_entity.h"
#include "null_entity.h"
#include "storage.h"

using namespace pfs;
using namespace std;

RootEntity* RootEntity::singleton = NULL;
string RootEntity::pass_;

RootEntity* RootEntity::get() {
    if (RootEntity::singleton == NULL) {
        RootEntity::singleton = new RootEntity();
    }

    return RootEntity::singleton;
}

RootEntity::RootEntity() : DirectoryEntity("") {
    // Set up the private storage directory
    string home(getenv("HOME"));
    string private_storage_dir_location(home+ "/.pfs");

    private_storage_dir_ = shared_ptr<StorageDirectoryEntity>(new EncryptedStorageDirectoryEntity("My Private Photos", private_storage_dir_location, pass_));
    children_.push_back(private_storage_dir_);

    // Set up the public storage directory
    public_storage_dir_ = shared_ptr<StorageDirectoryEntity>(new StorageDirectoryEntity("Shared Photos", "/tmp/.pfs"));
    children_.push_back(public_storage_dir_);
}

Entity* RootEntity::clone() {
    return new RootEntity(*this);
}

void RootEntity::set_password(string pass) {
    pass_ = pass;
}

shared_ptr<Entity> RootEntity::route_path(string path) {
	if (root_for_path(path) == name_) {
        return shared_ptr<Entity>(clone());
    }

    vector<shared_ptr<Entity> > children(get_children());
    for (auto i = children.begin(); i != children.end(); ++i) {
        if (i->get()->get_name() == root_for_path(path)) {
            if (i->get()->get_name() == path.erase(0, 1)) {
                return *i;
            }

            return i->get()->route_path(path, deeper_path(path)); 
        }
    }

	if (path_depth(path) == 0 && is_image_path(path)) {
        shared_ptr<Entity> entity(new NewFileEntity(root_for_path(path)));

        // Determine which directory to send a file to
        if (is_file_private(filename_for_path(path))) {
            entity->set_storage(private_storage_dir_->get_storage());
        } else {
            entity->set_storage(public_storage_dir_->get_storage());
        }

		return entity;
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
