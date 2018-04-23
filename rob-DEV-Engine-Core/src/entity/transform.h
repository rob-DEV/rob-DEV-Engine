#pragma once

#include <glm/glm.hpp>

namespace Engine {  namespace Core {  namespace Entities {
	class Transform
	{
	public:
		glm::vec3 position;
		Transform();
		Transform(glm::vec3 position);
		~Transform();
	};

	inline Transform::Transform()
	{
		this->position = glm::vec3(0, 0, 0);
	}

	inline Transform::Transform(glm::vec3 position)
	{
		this->position = position;
	}


	inline Transform::~Transform()
	{
	}
}  }  }
