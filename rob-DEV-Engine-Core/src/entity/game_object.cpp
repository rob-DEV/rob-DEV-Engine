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

	uint32_t GameObject::getSize()
	{
		//base size + vertex mesh data
		uint32_t base = Entity::getSize();
		if (mesh != NULL)
			base += mesh->getSize();

		return base;
	}

	char* GameObject::getData()
	{
		uint32_t size = getSize();
		char* dataResult = new char[size];
		
		/*
		*	ORDER
		*	Name
		*	Positon
		*	Rotation

		OPTIONAL	V
		*			Vertex
		*			Indices
		*			rgb colors
		*/

		uint32_t byte_count = 0;
		memcpy(&dataResult[byte_count], name.c_str(), strlen(name.c_str()));
		byte_count += strlen(name.c_str());
		memcpy(&dataResult[byte_count], &transform.position, sizeof(glm::vec3));
		byte_count += sizeof(glm::vec3);
		memcpy(&dataResult[byte_count], &transform.rotation, sizeof(glm::quat));
		byte_count += sizeof(glm::quat);
		
		if (mesh != NULL)
		{
			memcpy(&dataResult[byte_count], &mesh->vertices[0], sizeof(glm::vec3) * mesh->vertices.size());
			byte_count += (sizeof(glm::vec3) * mesh->vertices.size());
			memcpy(&dataResult[byte_count], &mesh->indices[0], sizeof(uint32_t) * mesh->indices.size());
			byte_count += (sizeof(uint32_t) * mesh->indices.size());

			memcpy(&dataResult[byte_count], &mesh->rgb_colors[0], sizeof(uint32_t) * mesh->rgb_colors.size());
			byte_count += (sizeof(uint32_t) * mesh->rgb_colors.size());
		}

		return dataResult;
	}

	void GameObject::AddBehaviourScript(GameObject_Behaviour* behavior)
	{
		behavior->m_GameObject = this;
		m_RuntimeBehaviours.push_back(behavior);
	}

	void GameObject::Init()
	{
		//update all script behaviours
		for (size_t i = 0; i < m_RuntimeBehaviours.size(); i++)
			m_RuntimeBehaviours[i]->Start();
	}

	void GameObject::Tick()
	{
		//update all script behaviours
		for (size_t i = 0; i < m_RuntimeBehaviours.size(); i++)
			m_RuntimeBehaviours[i]->Tick();
	}

}  }  }