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

		Mesh();
		Mesh(const char * name, std::vector<float> vertices, std::vector<float> colors);
		~Mesh();

		unsigned int getSize();
	};
}  }  }