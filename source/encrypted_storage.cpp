
#include "encrypted_storage.h"

using namespace pfs;
using namespace std;

EncryptedStorage::EncryptedStorage(string path) : Storage(path) {

}

sqlite3* EncryptedStorage::open() {
    return Storage::open();
}

int EncryptedStorage::close(sqlite3* db) {
    return Storage::close(db);
}

