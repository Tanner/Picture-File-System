
#include "null_entity.h"

using namespace pfs;
using namespace std;

NullEntity::NullEntity(string path) : Entity(path) {

}

auto_ptr<Entity> NullEntity::route_path(string full_path, string relative_path) {
    return auto_ptr<Entity>(this);
}

int NullEntity::getattr(struct stat* stbuf) {
    return -ENOENT;
}

int NullEntity::read(char* buf, size_t size, off_t offset, struct fuse_file_info* fi) {
    return -ENOENT;
}

int NullEntity::open(struct fuse_file_info* fi) {
    return -ENOENT;
}
