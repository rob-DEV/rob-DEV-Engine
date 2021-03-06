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

	Mesh::Mesh(const std::vector<glm::vec3>& vertices, const std::vector<uint32_t>& rgb_colors)
	{
		this->vertices = std::vector<glm::vec3>();
		this->rgb_colors = std::vector<uint32_t>();

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
	
	Mesh::Mesh(const std::vector<glm::vec3>& vertices, const std::vector<uint32_t>& indices, const std::vector<uint32_t>& rgb_colors)
	{
		this->vertices = std::vector<glm::vec3>();
		this->rgb_colors = std::vector<uint32_t>();

		if (&vertices != NULL)
			this->vertices = vertices;
		if (&indices != NULL)
			this->indices = indices;
		if (&rgb_colors != NULL)
			this->rgb_colors = rgb_colors;
	}

	Mesh::~Mesh()
	{
		vertices = std::vector<glm::vec3>();
		indices = std::vector<uint32_t>();
		rgb_colors = std::vector<uint32_t>();
	}

	uint32_t Mesh::getSize()
	{
		uint32_t vertex_byte_size = sizeof(glm::vec3) * vertices.size();
		uint32_t indices_byte_size = sizeof(uint32_t) * indices.size();
		uint32_t colors_byte_size = sizeof(uint32_t) * rgb_colors.size();

		return vertex_byte_size + indices_byte_size + colors_byte_size;
	}

}  }  }