
#include <openssl/blowfish.h>
#include <iostream>
#include <sstream>
#include <cstdlib>
#include <cstring>
#include <fstream>

#include "encrypted_storage.h"

using namespace pfs;
using namespace std;

EncryptedStorage::EncryptedStorage(string path, string& pass) : Storage(path), key_phrase_(pass) {

}

void EncryptedStorage::open() {
    cerr << "OPEN" << endl;

    if (db_ != NULL) {
        return;
    }

    cerr << "REALLY" << endl;

    if (file_exist()) {
        decrypt(key_phrase_);
    }

    return Storage::open();
}

int EncryptedStorage::close() {
    cerr << "CLOSE" << endl;

    Storage::close();

    encrypt(key_phrase_);

    return 0;
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
    char* data_in = (char*)calloc(sizeof(char), 8);
    char* data_out = (char*)calloc(sizeof(char), 8);

    BF_set_key(&key, key_phrase.length(), (const unsigned char*) key_phrase.c_str());

    ifstream input_file(path_, ios::binary);
    input_file.seekg (0, ios::beg);

    vector<char> buf;

    cout << "Start encrypting" << endl;

    streamsize sum_bytes_read = 0;
    streamsize bytes_read;
    do {
        memset(data_in, 0, 8);
        memset(data_out, 0, 8);
        
        input_file.read(data_in, 8);
        bytes_read = input_file.gcount();
        sum_bytes_read += bytes_read;

        if (bytes_read == 0) {
            break;
        }

        BF_ecb_encrypt((unsigned char*)data_in, (unsigned char*)data_out, &key, enc);

        for (int i = 0; i < bytes_read; i++)
            buf.push_back(data_out[i]);
    } while (bytes_read == 8);

    input_file.close();

    ofstream output_file(path_, ios::binary);

    string buf_str(buf.begin(), buf.end());

    output_file.write(buf_str.c_str(), sum_bytes_read);

    output_file.flush();

    cout << "Stop encrypting" << endl;

    return;
}

