
#ifndef ENCRYPTED_STORAGE_DIRECTORY_ENTITY_H_
#define ENCRYPTED_STORAGE_DIRECTORY_ENTITY_H_

#include "storage_directory_entity.h"
#include "storage.h"

namespace pfs {
	using namespace std;

	class EncryptedStorageDirectoryEntity : public StorageDirectoryEntity {
	public:
		EncryptedStorageDirectoryEntity(string name, string path);
		Entity* clone();
        shared_ptr<Storage> get_storage() {
            return storage_;
        }
	};
}

#endif

