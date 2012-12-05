
#include <iostream>

#include "new_file_entity.h"
#include "root_entity.h"
#include "photo.h"
#include "storage.h"

using namespace pfs;
using namespace std;

NewFileEntity::NewFileEntity(string name) : FileEntity(name) {
	permissions_ = 666;
}

Entity* NewFileEntity::clone() {
	return new NewFileEntity(*this);
}

string NewFileEntity::content() {
	return content_;
}

size_t NewFileEntity::length() {
	return content_.length();
}

int NewFileEntity::getattr(struct stat* stbuf) {
	if (!open_) {
		return -ENOENT;
	}

	stbuf->st_mode = S_IFREG | permissions_;
    stbuf->st_nlink = 1;
    stbuf->st_size = length();

    return 0;
}

int NewFileEntity::chmod(mode_t mode) {
	return is_open();
}

int NewFileEntity::chown(uid_t uid, gid_t gid) {
	return is_open();
}

int NewFileEntity::truncate(off_t size) {
	return is_open();
}

int NewFileEntity::utimens(const struct timespec ts[2]) {
	return is_open();
}

int NewFileEntity::access(int mask) {
	return is_open();
}

int NewFileEntity::open(struct fuse_file_info* fi) {

	return 0;
}

int NewFileEntity::write(const char* buf, size_t size, off_t off, struct fuse_file_info* fi) {
	if (!open_) {
		return -ENOENT;
	}

    content_.append(buf, size);

    return size;
}

int NewFileEntity::mknod(mode_t mode, dev_t rdev) {
	open_ = true;
	RootEntity::get()->add_file(shared_ptr<Entity>(new NewFileEntity(*this)));

    return 0;
}

int NewFileEntity::release(struct fuse_file_info* fi) {
	if (!open_) {
		return -ENOENT;
	}

	open_ = false;
    Photo photo = Photo(name_, content_);
	Storage::add_picture(photo);

	RootEntity::get()->remove_file(shared_ptr<Entity>(new NewFileEntity(*this)));

	return 0;
}
