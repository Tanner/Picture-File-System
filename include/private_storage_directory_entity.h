
#ifndef PRIVATE_STORAGE_DIRECTORY_ENTITY_H_
#define PRIVATE_STORAGE_DIRECTORY_ENTITY_H_

#include "storage_directory_entity.h"
#include "storage.h"

namespace pfs {
	using namespace std;

	class PrivateStorageDirectoryEntity : public StorageDirectoryEntity {
	public:
		PrivateStorageDirectoryEntity(string name);
		Entity* clone();
    private:
        static string get_private_path();
	};
}

#endif

