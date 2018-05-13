#include "game_object.h"

namespace Engine {  namespace Core {  namespace Entities {

	GameObject::GameObject() : Entity()
	{
	}

	GameObject::GameObject(const char* name, glm::vec3 position, const Engine::Core::Graphics::Mesh &mesh) : Entity(name, position)
	{
		this->mesh = &mesh;
		this->transform.position = position;
	}

	GameObject::~GameObject()
	{
	}

}  }  }