
#include <vector>

#include "entity.h"
#include "regex_matcher.h"
#include "directory_entity.h"
#include "root_entity.h"
#include "file_entity.h"
#include "picture_entity.h"
#include "null_entity.h"
#include "dates_directory_entity.h"
#include "year_directory_entity.h"
#include "month_directory_entity.h"

using namespace pfs;
using namespace std;

auto_ptr<Entity> Entity::entity_for_path(string path) {
    if (path == "/") {
        RootEntity* root = new RootEntity(path);
        root->set_permissions(0755);
        return auto_ptr<Entity>(root);
    }

    else if (path == "/Dates") {
        DatesDirectoryEntity* dates_dir = new DatesDirectoryEntity(path);
        dates_dir->set_permissions(0755);
        return auto_ptr<Entity>(dates_dir);
    }

    else if (path.find("/Dates") == 0) {
        RegexMatcher dates_regex("/Dates/([0-9]+)/?([A-Za-z]*)");
        vector<string> matches(dates_regex.find_matches(path));
        if (matches.size() == 2) {
            YearDirectoryEntity* year_dir = new YearDirectoryEntity(path, matches[1]);
            year_dir->set_permissions(0755);
            return auto_ptr<Entity>(year_dir);
        } else if (matches.size() == 3) {
            MonthDirectoryEntity* month_dir = new MonthDirectoryEntity(path, matches[1], matches[2]);
            month_dir->set_permissions(0755);
            return auto_ptr<Entity>(month_dir);
        }
    }

    return auto_ptr<Entity>(new NullEntity(path));
}

int Entity::readdir(void *buf, fuse_fill_dir_t filler, off_t offset, struct fuse_file_info *fi) {
    return -ENOENT;
}

int Entity::open(struct fuse_file_info* fi) {
    if ((fi->flags & 3) != O_RDONLY) {
        return -EACCES;
    }

    return 0;
}

Entity::Entity(string& path) : path_(path) {

}

