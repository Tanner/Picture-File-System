
#include "entity.h"
#include "root_entity.h"

using namespace pfs;
using namespace std;

unique_ptr<Entity> Entity::entity_for_path(string path) {
	if (path == "/") {
		return unique_ptr<Entity>(new RootEntity(path));
	}

	return unique_ptr<Entity>(new DirectoryEntity(path));
}

Entity::Entity(string& path) : path_(path) {

}
