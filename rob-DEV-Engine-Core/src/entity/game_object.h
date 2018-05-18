#pragma once
#include "entity.h"
#include "../graphics/mesh.h"

namespace Engine {  namespace Core {  namespace Entities {
	class GameObject : public Entity
	{
	public:
		Engine::Core::Graphics::Mesh* mesh;

		GameObject();
		GameObject(const char* name, glm::vec3 position, Engine::Core::Graphics::Mesh* mesh);
		~GameObject();

	};
}  }  }
