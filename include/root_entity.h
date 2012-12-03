
#ifndef ROOT_ENTITY_H_
#define ROOT_ENTITY_H_

#include "directory_entity.h"

namespace pfs {
	using namespace std;

	class RootEntity : public DirectoryEntity {
	public:
        static shared_ptr<RootEntity> get();
        shared_ptr<Entity> route_path(string full_path);
        vector<shared_ptr<Entity> > get_children();
    private:
		RootEntity(string name);
        vector<shared_ptr<Entity> > children_;
	};
}

#endif

