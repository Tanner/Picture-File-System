
#ifndef STORAGE_DIRECTORY_ENTITY_H_
#define STORAGE_DIRECTORY_ENTITY_H_

#include "directory_entity.h"

namespace pfs {
	using namespace std;

	class StorageDirectoryEntity : public DirectoryEntity {
	public:
		StorageDirectoryEntity(string path);
		Entity* clone();
		vector<shared_ptr<Entity> > get_children();
	};
}

#endif

