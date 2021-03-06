
#include "directory_entity.h"

using namespace pfs;
using namespace std;

DirectoryEntity::DirectoryEntity(string name) : Entity(name) {

}

int DirectoryEntity::readdir(void *buf, fuse_fill_dir_t filler, off_t offset, struct fuse_file_info *fi) {
    filler(buf, ".", NULL, 0);
    filler(buf, "..", NULL, 0);

    vector<shared_ptr<Entity> > children(get_children());
    for (vector<shared_ptr<Entity> >::iterator i = children.begin(); i != children.end(); ++i) {
        filler(buf, i->get()->get_name().c_str(), NULL, 0); 
    }

    return 0;
}

int DirectoryEntity::getattr(struct stat* stbuf) {
	stbuf->st_mode = S_IFDIR | permissions_;
	stbuf->st_nlink = 2 + get_children().size();

	return 0;
}

int DirectoryEntity::access(int mask) {
    return 0;
}

int DirectoryEntity::read(char* buf, size_t size, off_t offset, struct fuse_file_info* fi) {
	return 0;	
}
