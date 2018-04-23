#pragma once

#include <string>
#include <glm/glm.hpp>

#include "transform.h"

namespace Engine { namespace Core { namespace Entities { 
class Entity
{
public:
	std::string name;
	Transform transform;
public:
	Entity();
	Entity(const char* name, glm::vec3 postion);
	~Entity();
};

}  }  }

