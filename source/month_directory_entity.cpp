
#include <vector>

#include "month_directory_entity.h"
#include "storage.h"
#include "picture_entity.h"
#include "util.h"

using namespace pfs;
using namespace std;

MonthDirectoryEntity::MonthDirectoryEntity(int year, int month) : DirectoryEntity(month_to_str(month)), year_(year), month_(month) {

}

Entity* MonthDirectoryEntity::clone() {
    return new MonthDirectoryEntity(*this);
}

vector<shared_ptr<Entity> > MonthDirectoryEntity::get_children() {
	vector<shared_ptr<Entity> > children;
    vector<Photo> photos(Storage::get_photos(year_, month_));

    for (auto i = photos.begin(); i != photos.end(); ++i) {
    	children.push_back(shared_ptr<Entity>(new PictureEntity(*i)));
    }

    return children;
}
