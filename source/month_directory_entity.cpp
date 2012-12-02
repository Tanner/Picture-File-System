
#include <vector>

#include "month_directory_entity.h"
#include "storage.h"
#include "photo.h"

using namespace pfs;
using namespace std;

MonthDirectoryEntity::MonthDirectoryEntity(string& path, string year, string month) : DirectoryEntity(path), year_(year), month_(month) {

}

int MonthDirectoryEntity::readdir(void *buf, fuse_fill_dir_t filler, off_t offset, struct fuse_file_info *fi) {
    DirectoryEntity::readdir(buf, filler, offset, fi);

    vector<Photo> photos(Storage::get_photos(atoi(year_.c_str()), month_));
    for (vector<Photo>::iterator i = photos.begin(); i != photos.end(); ++i) {
        filler(buf, i->get_name().c_str(), NULL, 0); 
    }

    return 0;
}

int MonthDirectoryEntity::getattr(struct stat* stbuf) {
	DirectoryEntity::getattr(stbuf);

	return 0;
}

