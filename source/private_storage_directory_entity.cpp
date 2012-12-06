
#include "private_storage_directory_entity.h"

using namespace pfs;
using namespace std;

PrivateStorageDirectoryEntity::PrivateStorageDirectoryEntity(string name) : StorageDirectoryEntity(name, get_private_path()) {
}

Entity* PrivateStorageDirectoryEntity::clone() {
    return new PrivateStorageDirectoryEntity(*this);
}

string PrivateStorageDirectoryEntity::get_private_path() {
    string home_dir = getenv("HOME");
    string path = "/.pfs";
    return home_dir + path;
}
