#pragma once
#include <string>
#include <vector>

#include <GL/glew.h>
#include <glm/glm.hpp>

namespace Engine {  namespace Core {  namespace Graphics {
	class Mesh
	{
	public:

		std::string name;
		std::vector<glm::vec3> vertices;
		std::vector<unsigned int> verticeIndices;
	    std::vector<glm::vec3> colors;

		Mesh(const char * name);
		Mesh(const char * name, const std::vector<glm::vec3>& vertices, const std::vector<glm::vec3>& colors);
		~Mesh();

		unsigned int getSize();
	};
}  }  }