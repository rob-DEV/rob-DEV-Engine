#include "entity.h"


namespace Engine { namespace Core { namespace Entities {

	uint32_t Entity::number_entities = 0;
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

	uint32_t Entity::getSize()
	{
		uint32_t byte_size = 0;
		//name
		byte_size += strlen(name.c_str()) * sizeof(char);

		//transform
		byte_size += sizeof(glm::vec3);
		byte_size += sizeof(glm::quat);

		return byte_size;
	}

	void Entity::Tick()
	{

	}

}  }  }