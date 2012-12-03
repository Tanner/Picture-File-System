
#ifndef PICTURE_ENTITY_H_
#define PICTURE_ENTITY_H_

#include "file_entity.h"
#include "photo.h"

namespace pfs {
    using namespace std;
    
    class PictureEntity : public FileEntity {
    public:
        PictureEntity(Photo& p);
        Entity* clone();
    protected:
        size_t length();
        const char* content();
    };
}

#endif

