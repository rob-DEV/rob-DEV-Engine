#pragma once

#include <string>
#include <glm/glm.hpp>

#include "transform.h"

namespace Engine { namespace Core { namespace Entities { 

	class Entity
	{
	public:
		static unsigned int number_entities;
	public:
		std::string name;
		Transform transform;
	public:
		Entity();
		Entity(const char* name, glm::vec3 postion);
		virtual ~Entity();
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

