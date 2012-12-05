
#include <vector>
#include <sstream>

#include "storage_directory_entity.h"
#include "year_directory_entity.h"
#include "storage.h"

using namespace pfs;
using namespace std;

StorageDirectoryEntity::StorageDirectoryEntity(string name) : DirectoryEntity(name) {

}

Entity* StorageDirectoryEntity::clone() {
    return new StorageDirectoryEntity(*this);
}

vector<shared_ptr<Entity> > StorageDirectoryEntity::get_children() {
    vector<shared_ptr<Entity >> children;
    vector<int> years(Storage::get_years());
    for (vector<int>::iterator i = years.begin(); i != years.end(); ++i) {
        children.push_back(shared_ptr<Entity>(new YearDirectoryEntity(*i)));
    }

    return children;
}

