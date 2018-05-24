#pragma once
#include <string>
#include <vector>

#include <glm/glm.hpp>

#include "../common/i_serializeable.h"

namespace Engine {  namespace Core {  namespace Graphics {
	class Mesh : public ISerializable
	{
	public:

		std::vector<glm::vec3> vertices;
		std::vector<uint32_t> indices;
		std::vector<uint32_t> rgb_colors;

		Mesh();
		Mesh(const Mesh* mesh);
		Mesh(const std::vector<glm::vec3>& vertices, const std::vector<uint32_t>& colors);
		Mesh(const std::vector<glm::vec3>& vertices, const std::vector<uint32_t>& indices, const std::vector<uint32_t>& colors);
		~Mesh();

		uint32_t getSize() override;
	};
}  }  }