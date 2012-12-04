
#include <iostream>

#include "new_file_entity.h"
#include "root_entity.h"

using namespace pfs;
using namespace std;

NewFileEntity::NewFileEntity(string name) : Entity(name) {
	permissions_ = 666;
	cout << "[NewFileEntity] " << name << endl;
}

Entity* NewFileEntity::clone() {
	return new NewFileEntity(*this);
}

const char* NewFileEntity::content() {
	return content_.c_str();
}

size_t NewFileEntity::length() {
	return content_.length();
}

int NewFileEntity::getattr(struct stat* stbuf) {
	stbuf->st_mode = S_IFREG | permissions_;
    stbuf->st_nlink = 1;
    stbuf->st_size = length();

    return 0;
}

int NewFileEntity::access(int mask) {
	return 0;
}

int NewFileEntity::open(struct fuse_file_info* fi) {
	cout << "NewFileEntity open" << endl;
	return 0;
}

int NewFileEntity::mknod(mode_t mode, dev_t rdev) {
	RootEntity().add_file(shared_ptr<Entity>(new NewFileEntity(*this)));

    return 0;
}
