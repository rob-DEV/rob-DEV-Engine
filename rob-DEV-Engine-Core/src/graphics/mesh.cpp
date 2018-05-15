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

		//RGB Test Assignments
		if (&colors != NULL)
		{
			for (size_t i = 0; i < colors.size(); i++)
			{
				int r = colors[i].x * 255.0f;
				int g = colors[i].y * 255.0f;
				int b = colors[i].z * 255.0f;
				rgb_colors.push_back(255 << 24 | b << 16 | g << 8 | r);
			}
			
		}

		

	}
	

	Mesh::~Mesh()
	{
	}

	unsigned int Mesh::getSize()
	{
		return vertices.size() * sizeof(GLfloat);
	}

}  }  }