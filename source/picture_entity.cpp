
#include "picture_entity.h"

using namespace pfs;
using namespace std;

const string test_string = "Hello, World!";

PictureEntity::PictureEntity(string& path) : FileEntity(path) {
    
}

size_t PictureEntity::length() {
    return test_string.length();
}

const char* PictureEntity::content() {
    return test_string.c_str();
}

