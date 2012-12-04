
#ifndef DATES_DIRECTORY_ENTITY_H_
#define DATES_DIRECTORY_ENTITY_H_

#include "directory_entity.h"

namespace pfs {
	using namespace std;

	class DatesDirectoryEntity : public DirectoryEntity {
	public:
		DatesDirectoryEntity(string path);
		Entity* clone();
		vector<shared_ptr<Entity> > get_children();
	};
}

#endif

