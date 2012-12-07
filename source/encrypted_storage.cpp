
#include <openssl/blowfish.h>
#include <iostream>
#include <sstream>
#include <cstdlib>
#include <cstring>

#include "encrypted_storage.h"

using namespace pfs;
using namespace std;

EncryptedStorage::EncryptedStorage(string path) : Storage(path) {
    key_phrase_ = "pack12";

    encrypt(key_phrase_);

    path_ = "/nethome/tsmith84/.pfs_result";

    decrypt(key_phrase_);
    exit(0);
}

sqlite3* EncryptedStorage::open() {
    if(file_exist()) {
        decrypt(key_phrase_);
    }

    return Storage::open();
}

int EncryptedStorage::close(sqlite3* db) {
    encrypt(key_phrase_);

    return Storage::close(db);
}

bool EncryptedStorage::file_exist() {
    FILE *file = fopen(path_.c_str(), "r");

    if (file) {
        fclose(file);

        return true;
    } else {
        return false;
    }
}

void EncryptedStorage::encrypt(string key_phrase) {
    return encrypt_decrypt(key_phrase, BF_ENCRYPT);
}

void EncryptedStorage::decrypt(string key_phrase) {
    return encrypt_decrypt(key_phrase, BF_DECRYPT);
}

void EncryptedStorage::encrypt_decrypt(string key_phrase, int enc) {
    BF_KEY key;
    unsigned char data_in[8];
    unsigned char data_out[8];

    stringstream result_path;
    result_path << path_ << "_result";

    BF_set_key(&key, key_phrase.length(), (const unsigned char*) key_phrase.c_str());

    FILE *input_file = fopen(path_.c_str(), "r");
    FILE *output_file = fopen(result_path.str().c_str(), "w");

    int bytes_read;
    do {
        memset(data_in, 0, 8);
        memset(data_out, 0, 8);
        
        bytes_read = fread(data_in, 1, 8, input_file);

        BF_ecb_encrypt(data_in, data_out, &key, enc);

        fwrite(data_out, 1, bytes_read, output_file);
    } while (bytes_read == 8);

    fclose(output_file);
    fclose(input_file);

    return;
}

