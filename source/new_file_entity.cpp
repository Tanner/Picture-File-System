
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

int NewFileEntity::chmod(mode_t mode) {
	return 0;
}

int NewFileEntity::chown(uid_t uid, gid_t gid) {
	return 0;
}

int NewFileEntity::truncate(off_t size) {
	return 0;
}

int NewFileEntity::utimens(const struct timespec ts[2]) {
	return 0;
}

int NewFileEntity::access(int mask) {
	return 0;
}

int NewFileEntity::open(struct fuse_file_info* fi) {
	RootEntity::get()->add_file(shared_ptr<Entity>(new NewFileEntity(*this)));

	return 0;
}

int NewFileEntity::write(const char* buf, size_t size, off_t off, struct fuse_file_info* fi) {
    content_.append(buf);

	cout << "NEWFILE write" << this << endl;
    cout << content_ << endl;

    return size;
}

int NewFileEntity::mknod(mode_t mode, dev_t rdev) {
    return 0;
}

int NewFileEntity::release(struct fuse_file_info* fi) {
    Photo photo = Photo(name_, content_.c_str(), content_.length());
	Storage::add_picture(photo);

	RootEntity::get()->remove_file(shared_ptr<Entity>(new NewFileEntity(*this)));

	return 0;
}
