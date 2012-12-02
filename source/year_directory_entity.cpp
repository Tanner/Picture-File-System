
#include <vector>

#include "year_directory_entity.h"
#include "storage.h"

using namespace pfs;
using namespace std;

YearDirectoryEntity::YearDirectoryEntity(string& path, string year) : DirectoryEntity(path), year_(year) {

}

int YearDirectoryEntity::readdir(void *buf, fuse_fill_dir_t filler, off_t offset, struct fuse_file_info *fi) {
    DirectoryEntity::readdir(buf, filler, offset, fi);

    vector<string> months(Storage::get_months(atoi(year_.c_str())));
    for (vector<string>::iterator i = months.begin(); i != months.end(); ++i) {
        filler(buf, i->c_str(), NULL, 0); 
    }

    return 0;
}

int YearDirectoryEntity::getattr(struct stat* stbuf) {
	DirectoryEntity::getattr(stbuf);

	return 0;
}

