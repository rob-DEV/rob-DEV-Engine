#pragma once

#include <string>
#include <glm/glm.hpp>

#include "../common/i_serializeable.h"
#include "transform.h"

namespace Engine { namespace Core { namespace Entities { 

	class Entity : public ISerializable
	{
	public:
		static uint32_t number_entities;
	public:
		std::string name;
		Transform transform;
	public:
		Entity();
		Entity(const char* name, glm::vec3 postion);
		virtual void Tick(); 
		virtual ~Entity();
		uint32_t getSize() override;
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

