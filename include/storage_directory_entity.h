
#ifndef STORAGE_DIRECTORY_ENTITY_H_
#define STORAGE_DIRECTORY_ENTITY_H_

#include "directory_entity.h"
#include "storage.h"

namespace pfs {
	using namespace std;

	class StorageDirectoryEntity : public DirectoryEntity {
	public:
		StorageDirectoryEntity(string name, string path);
		Entity* clone();
		vector<shared_ptr<Entity> > get_children();
        shared_ptr<Storage> get_storage() {
            return storage_;
        }
	};
}

#endif

