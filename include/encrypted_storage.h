
#ifndef ENCRYPTED_STORAGE_H_
#define ENCRYPTED_STORAGE_H_

#include "storage.h"

namespace pfs {
    using namespace std;

    class EncryptedStorage : public Storage {
    public:
        EncryptedStorage(string path);
        void open();
        int close();
    private:
        string key_phrase_;
        void encrypt(string key_phrase);
        void decrypt(string key_phrase);
        void encrypt_decrypt(string key_phrase, int enc);

        bool file_exist();
    };
}

#endif

