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

	unsigned int GameObject::getSize()
	{
		//base size + vertex mesh data
		unsigned int base = Entity::getSize();
		if (mesh != NULL)
			base += mesh->getSize();

		return base;
	}

	char* GameObject::getData()
	{
		unsigned int size = getSize();
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

		unsigned int byte_count = 0;
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
			memcpy(&dataResult[byte_count], &mesh->indices[0], sizeof(unsigned int) * mesh->indices.size());
			byte_count += (sizeof(unsigned int) * mesh->indices.size());

			memcpy(&dataResult[byte_count], &mesh->rgb_colors[0], sizeof(unsigned int) * mesh->rgb_colors.size());
			byte_count += (sizeof(unsigned int) * mesh->rgb_colors.size());
		}

		return dataResult;
	}

}  }  }