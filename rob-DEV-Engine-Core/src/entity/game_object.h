#pragma once
#include "entity.h"
#include "../graphics/mesh.h"
#include "game_object_behaviour.h"

namespace Engine {  namespace Core {  namespace Entities {
	class GameObject : public Entity
	{
	private:
		std::vector<GameObject_Behaviour*> m_RuntimeBehaviours;
	public:
		Engine::Core::Graphics::Mesh* mesh;
		GameObject();
		GameObject(const char* name, glm::vec3 position, Engine::Core::Graphics::Mesh* mesh);
		~GameObject();

		void AddBehaviourScript(GameObject_Behaviour* behavior);
		
		void Init();
		void Tick();

		uint32_t getSize() override;
		char* getData();
	};
}  }  }
