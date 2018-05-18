#include "entity.h"


namespace Engine { namespace Core { namespace Entities {

	unsigned int Entity::number_entities = 0;
	Entity::Entity()
	{
		number_entities++;
	}

	Entity::Entity(const char* name, glm::vec3 position)
	{
		this->name = std::string(name);
		this->transform.position = position;
		number_entities++;
	}

	Entity::~Entity()
	{

	}

}  }  }