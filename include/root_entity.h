
#ifndef ROOT_ENTITY_H_
#define ROOT_ENTITY_H_

#include "directory_entity.h"
#include "storage_directory_entity.h"

namespace pfs {
	using namespace std;

	class RootEntity : public DirectoryEntity {
	public:
		static RootEntity* get();
		Entity* clone();
        shared_ptr<Entity> route_path(string full_path);
        vector<shared_ptr<Entity> > get_children();
        void add_file(shared_ptr<Entity> child);
        void remove_file(shared_ptr<Entity> child);
    private:
		RootEntity();
        vector<shared_ptr<Entity> > children_;
        static RootEntity* singleton;

        shared_ptr<StorageDirectoryEntity> private_storage_dir_;
        shared_ptr<StorageDirectoryEntity> public_storage_dir_;
	};
}

#endif

