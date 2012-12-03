
#include <vector>
#include <sstream>

#include "dates_directory_entity.h"
#include "year_directory_entity.h"
#include "storage.h"

using namespace pfs;
using namespace std;

DatesDirectoryEntity::DatesDirectoryEntity(string name) : DirectoryEntity(name) {

}

shared_ptr<Entity> DatesDirectoryEntity::route_path(string full_path, string relative_path) {
    return shared_ptr<Entity>(new DatesDirectoryEntity(*this));
}

vector<shared_ptr<Entity> > DatesDirectoryEntity::get_children() {
    vector<shared_ptr<Entity >> children;
    vector<int> years(Storage::get_years());
    for (vector<int>::iterator i = years.begin(); i != years.end(); ++i) {
        children.push_back(shared_ptr<Entity>(new YearDirectoryEntity(*i)));
    }

    return children;
}

