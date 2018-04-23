#include "mesh.h"

namespace Engine {  namespace Core {  namespace Graphics {

	Mesh::Mesh(const char * name, const std::vector<GLfloat>& vertices, const std::vector<float>& colors)
	{
		this->name = std::string(name);
		this->vertices = vertices;
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