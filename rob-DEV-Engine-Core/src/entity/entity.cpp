#include "entity.h"


namespace Engine { namespace Core { namespace Entities {

	Entity::Entity()
	{
	}

	Entity::Entity(const char* name, glm::vec3 position)
	{
		this->name = std::string(name);
		this->transform.position = position;
	}

	Entity::~Entity()
	{

	}

}  }  }