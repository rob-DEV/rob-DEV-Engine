#pragma once
#include <string>
#include <vector>

#include <GL/glew.h>
#include <glm/glm.hpp>

namespace Engine {  namespace Core {  namespace Graphics {
	class Mesh
	{
	public:

		std::vector<glm::vec3> vertices;
		std::vector<unsigned int> indices;
		std::vector<unsigned int> rgb_colors;

		Mesh();
		Mesh(const Mesh* mesh);
		Mesh(const std::vector<glm::vec3>& vertices, const std::vector<unsigned int>& colors);
		~Mesh();

	};
}  }  }