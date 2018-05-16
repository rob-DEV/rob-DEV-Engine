#pragma once

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/quaternion.hpp>
#include <glm/gtx/quaternion.hpp>

namespace Engine {  namespace Core {  namespace Entities {
	class Transform
	{
	public:
		glm::vec3 position;
		glm::quat rotation;

		Transform();
		Transform(glm::vec3 position);
		Transform(glm::vec3 position, glm::vec3 eulerAngles);

		void Rotate(glm::vec3 eulerAngles);

		~Transform();
	};

	inline Transform::Transform()
	{
		this->position = glm::vec3(0, 0, 0);
		this->rotation = glm::quat(position);
	}

	inline Transform::Transform(glm::vec3 position)
	{
		this->position = position;
		this->rotation = glm::quat(position);
	}

	inline Transform::Transform(glm::vec3 position, glm::vec3 eulerAngles)
	{
		this->position = position;
		this->rotation = glm::quat(eulerAngles);
	}

	inline void Transform::Rotate(glm::vec3 eulerAngles)
	{
		this->rotation = glm::quat(eulerAngles) * this->rotation;
	}



	inline Transform::~Transform()
	{
	}
}  }  }
