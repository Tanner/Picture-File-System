
#include <openssl/blowfish.h>

#include "encrypted_storage.h"

using namespace pfs;
using namespace std;

EncryptedStorage::EncryptedStorage(string path) : Storage(path) {
    key_phrase_ = "thisisakitty";
}

sqlite3* EncryptedStorage::open() {
    decrypt(key_phrase_);

    return Storage::open();
}

int EncryptedStorage::close(sqlite3* db) {
    encrypt(key_phrase_);

    return Storage::close(db);
}

void EncryptedStorage::encrypt(string key_phrase) {
    return encrypt_decrypt(key_phrase, BF_ENCRYPT);
}

void EncryptedStorage::decrypt(string key_phrase) {
    return encrypt_decrypt(key_phrase, BF_DECRYPT);
}

void EncryptedStorage::encrypt_decrypt(string key_phrase, int enc) {
    BF_KEY key;
    unsigned char data_in[64];
    unsigned char data_out[64];

    BF_set_key(&key, key_phrase.length(), (const unsigned char*) key_phrase.c_str());

    FILE *file = fopen(path_.c_str(), "rw");

        string path_;

    int bytes_read;
    do {
        bytes_read = fread(data_in, 1, 64, file);

        BF_ecb_encrypt(data_in, data_out, &key, enc);

        fwrite(data_out, 1, bytes_read, file);
    } while (bytes_read < 64);

    fclose(file);

    return;
}

