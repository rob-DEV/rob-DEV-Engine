#include "mesh.h"

namespace Engine {  namespace Core {  namespace Graphics {

	Mesh::Mesh()
	{
	}

	Mesh::Mesh(const Mesh* mesh)
	{
		vertices = mesh->vertices;
		indices = mesh->indices;
		rgb_colors = mesh->rgb_colors;
	}

	Mesh::Mesh(const std::vector<glm::vec3>& vertices, const std::vector<unsigned int>& rgb_colors)
	{
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
		vertices = std::vector<glm::vec3>();
		indices = std::vector<unsigned int>();
		rgb_colors = std::vector<unsigned int>();
	}

}  }  }