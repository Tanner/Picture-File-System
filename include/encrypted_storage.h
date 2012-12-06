
#ifndef ENCRYPTED_STORAGE_H_
#define ENCRYPTED_STORAGE_H_

#include "storage.h"

namespace pfs {
    using namespace std;

    class EncryptedStorage : public Storage {
    public:
        EncryptedStorage(string path);
    protected:
        sqlite3* open();
        int close(sqlite3*);
    };
}

#endif

