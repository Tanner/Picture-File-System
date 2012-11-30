
#include "entity.h"
#include "directory_entity.h"
#include "root_entity.h"
#include "file_entity.h"
#include "picture_entity.h"
#include "null_entity.h"

using namespace pfs;
using namespace std;

auto_ptr<Entity> Entity::entity_for_path(string path) {
	if (path == "/") {
        RootEntity* root = new RootEntity(path);
        root->set_permissions(0755);
		return auto_ptr<Entity>(root);
	}

    else if (path == "/hello") {
        PictureEntity* hello_file = new PictureEntity(path);
        hello_file->set_permissions(0755);
        return auto_ptr<Entity>(hello_file);
    }

	return auto_ptr<Entity>(new NullEntity(path));
}

int Entity::readdir(void *buf, fuse_fill_dir_t filler, off_t offset, struct fuse_file_info *fi) {
    return -ENOENT;
}

int Entity::open(struct fuse_file_info* fi) {
    if ((fi->flags & 3) != O_RDONLY) {
        return -EACCES;
    }

    return 0;
}

Entity::Entity(string& path) : path_(path) {

}
