
#include "picture_entity.h"

using namespace pfs;
using namespace std;

const string test_string = "Hello, World!";

PictureEntity::PictureEntity(Photo& p) : FileEntity(p.get_name()) {
    
}

Entity* PictureEntity::clone() {
    return new PictureEntity(*this);
}

size_t PictureEntity::length() {
    return test_string.length();
}

const char* PictureEntity::content() {
    return test_string.c_str();
}

