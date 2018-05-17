#include "mesh.h"

namespace Engine {  namespace Core {  namespace Graphics {

	Mesh::Mesh(const char * name)
	{
		this->name = std::string(name);
	}

	Mesh::Mesh(const char * name, const std::vector<glm::vec3>& vertices, const std::vector<unsigned int>& rgb_colors)
	{
		this->name = std::string(name);
		this->vertices = std::vector<glm::vec3>();
		this->rgb_colors = std::vector<unsigned int>();

		if(&vertices != NULL)
			this->vertices = vertices;
		if (&rgb_colors != NULL)
			this->rgb_colors = rgb_colors;

		//RGB Test Assignments
		if (&rgb_colors != NULL)
		{
			for (size_t i = 0; i < this->rgb_colors.size(); i++)
			{
				int r = static_cast <float> (rand()) / static_cast <float> (RAND_MAX) * 255.0f;
				int g = static_cast <float> (rand()) / static_cast <float> (RAND_MAX) * 255.0f;
				int b = static_cast <float> (rand()) / static_cast <float> (RAND_MAX) * 255.0f;
				this->rgb_colors.push_back(255 << 24 | b << 16 | g << 8 | r);
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