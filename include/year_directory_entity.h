
#ifndef YEAR_DIRECTORY_ENTITY_H_
#define YEAR_DIRECTORY_ENTITY_H_

#include "directory_entity.h"

namespace pfs {
	using namespace std;

	class YearDirectoryEntity : public DirectoryEntity {
	public:
		YearDirectoryEntity(int year);
    private:
        int year_;
	};
}

#endif

