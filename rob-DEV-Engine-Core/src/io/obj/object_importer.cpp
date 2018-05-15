#include "object_importer.h"
#include <iostream>

#include <glm/glm.hpp>

#include <ctime>
#include <map>

namespace Engine { namespace Core { namespace IO { namespace Importers {
	static Obj_Importer* m_ObjImporter = NULL;

	Obj_Importer* Obj_Importer::getObjImporterInstance()
	{
		if (m_ObjImporter == NULL)
			m_ObjImporter = new Obj_Importer();

		return m_ObjImporter;
	}

	Obj_Importer::Obj_Importer()
	{
	}


	Obj_Importer::~Obj_Importer()
	{
	}

	struct PackedVertex {
		glm::vec3 position;
		bool operator<(const PackedVertex that) const {
			return memcmp((void*)this, (void*)&that, sizeof(PackedVertex))>0;
		};
	};

	bool is_near(float v1, float v2) {
		return fabs(v1 - v2) < 0.01f;
	}



	bool getSimilarVertexIndex_fast(
		PackedVertex & packed,
		std::map<PackedVertex, unsigned int> & VertexToOutIndex,
		unsigned int & result
	) {
		std::map<PackedVertex, unsigned int>::iterator it = VertexToOutIndex.find(packed);
		if (it == VertexToOutIndex.end()) {
			return false;
		}
		else {
			result = it->second;
			return true;
		}
	}
	bool getSimilarVertexIndex(
		glm::vec3 & in_vertex,
		std::vector<glm::vec3> & out_vertices,
		unsigned short & result
	) {
		// Lame linear search
		for (unsigned int i = 0; i<out_vertices.size(); i++) {
			if (
				is_near(in_vertex.x, out_vertices[i].x) &&
				is_near(in_vertex.y, out_vertices[i].y) &&
				is_near(in_vertex.z, out_vertices[i].z)
				) {
				result = i;
				return true;
			}
		}
		// No other vertex could be used instead.
		// Looks like we'll have to add it to the VBO.
		return false;
	}

	void indexVBO(
		std::vector<glm::vec3> & in_vertices,

		std::vector<unsigned int> & out_indices,
		std::vector<glm::vec3> & out_vertices
	) {
		// For each input vertex
		for (unsigned int i = 0; i<in_vertices.size(); i++) {

			// Try to find a similar vertex in out_XXXX
			unsigned short index;
			bool found = getSimilarVertexIndex(in_vertices[i], out_vertices, index);

			if (found) { // A similar vertex is already in the VBO, use it instead !
				out_indices.push_back(index);
			}
			else { // If not, it needs to be added in the output data.
				out_vertices.push_back(in_vertices[i]);
				//out_uvs.push_back(in_uvs[i]);
				//out_normals.push_back(in_normals[i]);
				out_indices.push_back((unsigned short)out_vertices.size() - 1);
			}
		}
	}

	Engine::Core::Graphics::Mesh* Obj_Importer::ImportObj(const char* filepath)
	{
		std::vector<unsigned int> vertexIndices, uvIndices, normalIndices;
		std::vector<glm::vec3> temp_vertices;
		std::vector<glm::vec2> temp_uvs;
		std::vector<glm::vec3> temp_normals;

		std::vector<glm::vec3> temp_out_verts_pre_index;

		FILE * file = fopen(filepath, "r");
		if (file == NULL) {
			printf("Impossible to open the file ! Are you in the right path ? See Tutorial 1 for details\n");
			getchar();
			return false;
		}

		while (1)
		{
			char lineHeader[128];
			// read the first word of the line
			int res = fscanf(file, "%s", lineHeader);
			if (res == EOF)
				break; // EOF = End Of File. Quit the loop.

					   // else : parse lineHeader

			if (strcmp(lineHeader, "v") == 0) {
				glm::vec3 vertex;
				fscanf(file, "%f %f %f\n", &vertex.x, &vertex.y, &vertex.z);
				temp_vertices.push_back(vertex);
			}
			/*else if (strcmp(lineHeader, "vt") == 0) {
			glm::vec2 uv;
			fscanf(file, "%f %f\n", &uv.x, &uv.y);
			uv.y = -uv.y; // Invert V coordinate since we will only use DDS texture, which are inverted. Remove if you want to use TGA or BMP loaders.
			temp_uvs.push_back(uv);
			}
			else if (strcmp(lineHeader, "vn") == 0) {
			glm::vec3 normal;
			fscanf(file, "%f %f %f\n", &normal.x, &normal.y, &normal.z);
			temp_normals.push_back(normal);
			}*/
			else if (strcmp(lineHeader, "f") == 0) {
				std::string vertex1, vertex2, vertex3;
				unsigned int vertexIndex[3], uvIndex[3], normalIndex[3];
				int matches = fscanf(file, "%d/%d/%d %d/%d/%d %d/%d/%d\n", &vertexIndex[0], &uvIndex[0], &normalIndex[0], &vertexIndex[1], &uvIndex[1], &normalIndex[1], &vertexIndex[2], &uvIndex[2], &normalIndex[2]);
				if (matches != 9) {
					printf("File can't be read by our simple parser :-( Try exporting with other options\n");
					fclose(file);
					return false;
				}
				vertexIndices.push_back(vertexIndex[0]);
				vertexIndices.push_back(vertexIndex[1]);
				vertexIndices.push_back(vertexIndex[2]);
				uvIndices.push_back(uvIndex[0]);
				uvIndices.push_back(uvIndex[1]);
				uvIndices.push_back(uvIndex[2]);
				normalIndices.push_back(normalIndex[0]);
				normalIndices.push_back(normalIndex[1]);
				normalIndices.push_back(normalIndex[2]);
			}
			else {
				// Probably a comment, eat up the rest of the line
				char stupidBuffer[1000];
				fgets(stupidBuffer, 1000, file);
			}

		}

		// For each vertex of each triangle
		for (unsigned int i = 0; i<vertexIndices.size(); i++) {

			// Get the indices of its attributes
			unsigned int vertexIndex = vertexIndices[i];

			// Get the attributes thanks to the index
			glm::vec3 vertex = temp_vertices[vertexIndex - 1];

			// Put the attributes in buffers
			//vertices_out.push_back(vertex);
			temp_out_verts_pre_index.push_back(vertex);
		}

		std::vector<unsigned int> rand_import_colors;
		vertexIndices.size();
		//generate random indice colours
		for (size_t i = 0; i < vertexIndices.size(); i++)
		{
			int r = static_cast <float> (rand()) / static_cast <float> (RAND_MAX) * 255.0f;
			int g = static_cast <float> (rand()) / static_cast <float> (RAND_MAX) * 255.0f;
			int b = static_cast <float> (rand()) / static_cast <float> (RAND_MAX) * 255.0f;

			unsigned int color = 255 << 24 | b << 16 | g << 8 | r;
			rand_import_colors.push_back(color);

		}
		//generate the mesh object (heaped atm)
		Graphics::Mesh* mesh = new Graphics::Mesh("IMPORTED_MODEL");
		mesh->rgb_colors = rand_import_colors;
		indexVBO(temp_out_verts_pre_index, mesh->indices, mesh->vertices);

		fclose(file);
		return mesh;
	}
} } } }