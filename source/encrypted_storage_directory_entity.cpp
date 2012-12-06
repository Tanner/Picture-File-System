
#include <vector>
#include <sstream>

#include "encrypted_storage_directory_entity.h"
#include "year_directory_entity.h"
#include "encrypted_storage.h"

using namespace pfs;
using namespace std;

EncryptedStorageDirectoryEntity::EncryptedStorageDirectoryEntity(string name, string storage_path) : StorageDirectoryEntity(name, storage_path) {
    storage_ = shared_ptr<EncryptedStorage>(new EncryptedStorage(storage_path));
}

Entity* EncryptedStorageDirectoryEntity::clone() {
    return new EncryptedStorageDirectoryEntity(*this);
}

