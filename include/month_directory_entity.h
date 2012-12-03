
#ifndef MONTH_DIRECTORY_ENTITY_H_
#define MONTH_DIRECTORY_ENTITY_H_

#include "directory_entity.h"

namespace pfs {
	using namespace std;

	class MonthDirectoryEntity : public DirectoryEntity {
	public:
		MonthDirectoryEntity(int year, string month);
		Entity* clone();
		vector<shared_ptr<Entity> > get_children();
    private:
        int year_;
        string month_;
	};
}

#endif

