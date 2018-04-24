#include "mesh.h"

namespace Engine {  namespace Core {  namespace Graphics {

	Mesh::Mesh(const char * name)
	{
		this->name = std::string(name);
	}

	Mesh::Mesh(const char * name, const std::vector<glm::vec3>& vertices, const std::vector<glm::vec3>& colors)
	{
		this->name = std::string(name);
		this->vertices = std::vector<glm::vec3>();
		this->colors = std::vector<glm::vec3>();

		if(&vertices != NULL)
			this->vertices = vertices;
		if (&colors != NULL)
			this->colors = colors;

		

	}
	

	Mesh::~Mesh()
	{
	}

	unsigned int Mesh::getSize()
	{
		return vertices.size() * sizeof(GLfloat);
	}

}  }  }