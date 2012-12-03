
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
    vector<string> years(Storage::get_months(year_));
    for (vector<string>::iterator i = years.begin(); i != years.end(); ++i) {
        children.push_back(shared_ptr<Entity>(new MonthDirectoryEntity(year_, *i)));
    }

    return children;
}

