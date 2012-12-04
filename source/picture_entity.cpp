
#include <iostream>

#include "picture_entity.h"

using namespace pfs;
using namespace std;

PictureEntity::PictureEntity(Photo& p) : FileEntity(p.get_name()), photo_(p) {
    
}

Entity* PictureEntity::clone() {
    return new PictureEntity(*this);
}

size_t PictureEntity::length() {
    return photo_.get_size();
}

const char* PictureEntity::content() {
	cout << endl<<endl<<"PICTUREENTITY DATA " << photo_.get_data() << endl;
    return photo_.get_data();
}

