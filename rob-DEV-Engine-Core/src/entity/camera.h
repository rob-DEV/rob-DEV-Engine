#pragma once

#include <string>
#include <glm/glm.hpp>

#include "../common/i_serializeable.h"
#include "transform.h"
#include "game_object.h"

namespace Engine { namespace Core { namespace Entities { 

	class Camera : GameObject
	{
	private:
		std::vector<GameObject_Behaviour*> m_RuntimeBehaviours;
		glm::mat4 m_ViewMatrix;
	public:
		Camera();
		Camera(const char* name, glm::vec3 position);
		~Camera();

		void AddBehaviourScript(GameObject_Behaviour* behavior);

		void Init();
		void Tick() override;
		
		inline const glm::mat4& getViewMatrix() const { return m_ViewMatrix; }

		uint32_t getSize() override;
	};

}  }  }

