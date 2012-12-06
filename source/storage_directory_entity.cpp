
#include <vector>
#include <sstream>

#include "storage_directory_entity.h"
#include "year_directory_entity.h"
#include "storage.h"

using namespace pfs;
using namespace std;

StorageDirectoryEntity::StorageDirectoryEntity(string name, string storage_path) : DirectoryEntity(name) {
    storage_ = shared_ptr<Storage>(new Storage(storage_path));
}

Entity* StorageDirectoryEntity::clone() {
    return new StorageDirectoryEntity(*this);
}

vector<shared_ptr<Entity> > StorageDirectoryEntity::get_children() {
    vector<shared_ptr<Entity >> children;
    vector<int> years(storage_->get_years());
    for (vector<int>::iterator i = years.begin(); i != years.end(); ++i) {
        shared_ptr<Entity> entity(new YearDirectoryEntity(*i));
        entity->set_storage(storage_);

        children.push_back(entity);
    }

    return children;
}

