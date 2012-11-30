
#ifndef NULL_ENTITY_H_
#define NULL_ENTITY_H_

#include "entity.h"

namespace pfs {
    using namespace std;
    
    class NullEntity : public Entity {
    public:
        NullEntity(string& path);
        int getattr(struct stat* stbuf);
        int read(char* buf, size_t size, off_t offset, struct fuse_file_info* fi);
		int open(struct fuse_file_info* fi);
    };
}

#endif
