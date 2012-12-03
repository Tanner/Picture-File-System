
#include <vector>

#include "year_directory_entity.h"
#include "storage.h"
#include "util.h"

using namespace pfs;
using namespace std;

YearDirectoryEntity::YearDirectoryEntity(int year) : DirectoryEntity(pfs::int_to_str(year)), year_(year) {

}
