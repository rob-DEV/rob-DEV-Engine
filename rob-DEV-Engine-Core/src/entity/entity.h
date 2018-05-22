#pragma once

#include <string>
#include <glm/glm.hpp>

#include "../common/serializeable.h"
#include "transform.h"

namespace Engine { namespace Core { namespace Entities { 

	class Entity : public ISerializable
	{
	public:
		static unsigned int number_entities;
	public:
		std::string name;
		Transform transform;
	public:
		Entity();
		Entity(const char* name, glm::vec3 postion);
		virtual void Tick(); 
		virtual ~Entity();
		unsigned int getSize() override;
	};

	template<typename T>
	inline void Destroy(T& entity)
	{
		if (entity != NULL)
		{
			delete entity;

			entity = NULL;

			Entity::number_entities--;
		}
	}


}  }  }

