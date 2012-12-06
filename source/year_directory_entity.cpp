
#include <vector>

#include "year_directory_entity.h"
#include "month_directory_entity.h"
#include "storage.h"
#include "util.h"

using namespace pfs;
using namespace std;

YearDirectoryEntity::YearDirectoryEntity(int year) : DirectoryEntity(pfs::int_to_str(year)), year_(year) {

}

Entity* YearDirectoryEntity::clone() {
	return new YearDirectoryEntity(*this);
}

vector<shared_ptr<Entity> > YearDirectoryEntity::get_children() {
    vector<shared_ptr<Entity >> children;
    vector<int> years(storage_->get_months(year_));
    for (vector<int>::iterator i = years.begin(); i != years.end(); ++i) {
        shared_ptr<Entity> entity(new MonthDirectoryEntity(year_, *i));
        entity->set_storage(storage_);

        children.push_back(entity);
    }

    return children;
}

