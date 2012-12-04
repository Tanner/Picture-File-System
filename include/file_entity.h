
#ifndef FILE_ENTITY_H_
#define FILE_ENTITY_H_

#include "entity.h"

namespace pfs {
    using namespace std;
    
    class FileEntity : public Entity {
    public:
        FileEntity(string path);
        int getattr(struct stat* stbuf);
        int access(int mask);
        int open(struct fuse_file_info* fi);
        int read(char* buf, size_t size, off_t offset, struct fuse_file_info* fi);
    protected:
        virtual const char* content() = 0;
        virtual size_t length() = 0;
    };
}

#endif

