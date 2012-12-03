
#ifndef ROOT_ENTITY_H_
#define ROOT_ENTITY_H_

#include "directory_entity.h"

namespace pfs {
	using namespace std;

	class RootEntity : public DirectoryEntity {
	public:
		RootEntity();
		Entity* clone();
        shared_ptr<Entity> route_path(string full_path);
        vector<shared_ptr<Entity> > get_children();
    private:
        vector<shared_ptr<Entity> > children_;
	};
}

#endif

