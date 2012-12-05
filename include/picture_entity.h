
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
        int getattr(struct stat* stbuf);
        int rename(string new_name);
        int write(const char* buf, size_t size, off_t offset, struct fuse_file_info* fi);
    protected:
        size_t length();
        string content();
    private:
    	Photo photo_;
    };
}

#endif

