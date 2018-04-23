#pragma once
#include <string>
#include <vector>

#include <GL/glew.h>

namespace Engine {  namespace Core {  namespace Graphics {
	class Mesh
	{
	public:

		std::string name;
		std::vector<GLfloat> vertices;
	    std::vector<GLfloat> colors;

		Mesh(const char * name, const std::vector<float>& vertices, const std::vector<float>& colors);
		~Mesh();

		unsigned int getSize();
	};
}  }  }