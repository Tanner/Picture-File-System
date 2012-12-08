
#include <iostream>
#include <fstream>
#include <sstream>
#include <signal.h>

#include "root_entity.h"

#include "encrypted_storage.h"

using namespace pfs;

static string pass;

namespace pfs {
    int getattr(const char* path, struct stat* stbuf);
    int readdir(const char* path, void* buf, fuse_fill_dir_t filler, off_t offset, struct fuse_file_info* fi);
    int access(const char* path, int mask);
    int chmod(const char* path, mode_t mode);
    int chown(const char* path, uid_t uid, gid_t gid);
    int truncate(const char* path, off_t size);
    int utimens(const char* path, const struct timespec ts[2]);
    int open(const char* path, struct fuse_file_info* fi);
    int read(const char* path, char* buf, size_t size, off_t offset, struct fuse_file_info* fi);
    int write(const char* path, const char* buf, size_t size, off_t offset, struct fuse_file_info* fi);
    int mknod(const char* path, mode_t mode, dev_t rdev);
    int release(const char* path, struct fuse_file_info* fi);
    int rename(const char* path, const char* new_name);
}

static struct fuse_operations operations;

void exit_handler(int signal) {
    string home(getenv("HOME"));
    string private_storage_dir_location(home + "/.pfs");
    EncryptedStorage private_storage(private_storage_dir_location, pass);
    private_storage.close();

    exit(1);
}

void listen_to_signal(int signal, void(*handler)(int)) {
    struct sigaction sig_action;

    sig_action.sa_handler = handler;
    sigemptyset(&sig_action.sa_mask);
    sig_action.sa_flags = 0;

    sigaction(signal, &sig_action, NULL);
}

int main(int argc, char** argv) {
    operations.getattr = pfs::getattr;
    operations.readdir = pfs::readdir;
    operations.chmod = pfs::chmod;
    operations.chown = pfs::chown;
    operations.truncate = pfs::truncate;
    operations.utimens = pfs::utimens;
    operations.access = pfs::access;
    operations.open = pfs::open;
    operations.read = pfs::read;
    operations.write = pfs::write;
    operations.mknod = pfs::mknod;
    operations.release = pfs::release;
    operations.rename = pfs::rename;

    // intercept ctrl+c
    listen_to_signal(SIGINT, exit_handler);

    // set password
    cout << "Password: " << flush;
    cin >> pass;
    RootEntity::set_password(pass);
    
    int fuse_retval = fuse_main(argc, argv, &operations, NULL);

    if (fuse_retval == 0) {
        // encrypt database
        string home(getenv("HOME"));
        string private_storage_dir_location(home + "/.pfs");
        EncryptedStorage private_storage(private_storage_dir_location, pass);
        private_storage.close();
    }

    return fuse_retval;
}

int pfs::getattr(const char* path, struct stat* stbuf) {
    memset(stbuf, 0, sizeof(struct stat));

    shared_ptr<Entity> entity(RootEntity::get()->route_path(path));
    return entity->getattr(stbuf);
}

int pfs::readdir(const char* path, void* buf, fuse_fill_dir_t filler, off_t offset, struct fuse_file_info* fi) {
    shared_ptr<Entity> entity(RootEntity::get()->route_path(path));
    return entity->readdir(buf, filler, offset, fi);
}

int pfs::chmod(const char* path, mode_t mode) {
    shared_ptr<Entity> entity(RootEntity::get()->route_path(path));
    return entity->chmod(mode);
}

int pfs::chown(const char* path, uid_t uid, gid_t gid) {
    shared_ptr<Entity> entity(RootEntity::get()->route_path(path));
    return entity->chown(uid, gid);
}

int pfs::truncate(const char* path, off_t size) {
    shared_ptr<Entity> entity(RootEntity::get()->route_path(path));
    return entity->truncate(size);
}

int pfs::utimens(const char* path, const struct timespec ts[2]) {
    shared_ptr<Entity> entity(RootEntity::get()->route_path(path));
    return entity->utimens(ts);
}

int pfs::access(const char* path, int mask) {
    shared_ptr<Entity> entity(RootEntity::get()->route_path(path));
    return entity->access(mask);
}

int pfs::open(const char* path, struct fuse_file_info* fi) {
    shared_ptr<Entity> entity(RootEntity::get()->route_path(path));
    return entity->open(fi);
}

int pfs::read(const char* path, char* buf, size_t size, off_t off, struct fuse_file_info* fi) {
    shared_ptr<Entity> entity(RootEntity::get()->route_path(path));
    return entity->read(buf, size, off, fi);
}

int pfs::write(const char* path, const char* buf, size_t size, off_t off, struct fuse_file_info* fi) {
    shared_ptr<Entity> entity(RootEntity::get()->route_path(path));
    return entity->write(buf, size, off, fi);
}

int pfs::mknod(const char* path, mode_t mode, dev_t rdev) {
    shared_ptr<Entity> entity(RootEntity::get()->route_path(path));
    return entity->mknod(mode, rdev);
}

int pfs::release(const char* path, struct fuse_file_info* fi) {
    shared_ptr<Entity> entity(RootEntity::get()->route_path(path));
    return entity->release(fi);
}

int pfs::rename(const char* path, const char* new_name) {
    shared_ptr<Entity> entity(RootEntity::get()->route_path(path));
    return entity->rename(filename_for_path(new_name));
}
