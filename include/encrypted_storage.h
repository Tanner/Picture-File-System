
#ifndef ENCRYPTED_STORAGE_H_
#define ENCRYPTED_STORAGE_H_

#include "storage.h"

namespace pfs {
    using namespace std;

    class EncryptedStorage : public Storage {
    public:
        EncryptedStorage(string path);
    private:
        sqlite3* open();
    };
}

#endif

