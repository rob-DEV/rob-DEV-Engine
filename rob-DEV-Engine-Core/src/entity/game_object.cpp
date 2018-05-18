#include "game_object.h"

namespace Engine {  namespace Core {  namespace Entities {

	GameObject::GameObject() : Entity()
	{
		
	}

	GameObject::GameObject(const char* name, glm::vec3 position, Engine::Core::Graphics::Mesh* mesh) : Entity(name, position)
	{
		this->mesh = new Engine::Core::Graphics::Mesh(mesh);
		this->transform.position = position;
	}

	GameObject::~GameObject()
	{
		delete mesh;
		mesh = NULL;
	}

}  }  }