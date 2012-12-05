
#include "picture_entity.h"
#include "storage.h"

using namespace pfs;
using namespace std;

PictureEntity::PictureEntity(Photo& p) : FileEntity(p.get_name()), photo_(p) {
    
}

int PictureEntity::rename(string new_name) {
	Storage::rename_picture(photo_, new_name);

	return 0;
}

Entity* PictureEntity::clone() {
    return new PictureEntity(*this);
}

size_t PictureEntity::length() {
    return photo_.size();
}

const char* PictureEntity::content() {
    return photo_.data();
}
