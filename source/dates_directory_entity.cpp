
#include <vector>
#include <sstream>

#include "dates_directory_entity.h"
#include "storage.h"

using namespace pfs;
using namespace std;

DatesDirectoryEntity::DatesDirectoryEntity(string& path) : DirectoryEntity(path) {

}

int DatesDirectoryEntity::readdir(void *buf, fuse_fill_dir_t filler, off_t offset, struct fuse_file_info *fi) {
    DirectoryEntity::readdir(buf, filler, offset, fi);    

    vector<int> years(Storage::get_years());
    for (vector<int>::iterator i = years.begin(); i != years.end(); ++i) {
        stringstream ss;
        ss << *i;
        filler(buf, ss.str().c_str(), NULL, 0);
    }

    return 0;
}

int DatesDirectoryEntity::getattr(struct stat* stbuf) {
	stbuf->st_mode = S_IFDIR | permissions_;
	stbuf->st_nlink = 2;

	return 0;
}

