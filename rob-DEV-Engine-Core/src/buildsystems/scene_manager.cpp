#include "scene_manager.h"
#include "../io/common/io.h"

namespace Engine { namespace Core { namespace BuildSystems {

	static SceneManager* m_Instance = NULL;

	SceneManager* SceneManager::getInstance()
	{
		if (m_Instance == NULL)
			m_Instance = new SceneManager();

		return m_Instance;
	}

	SceneManager::SceneManager()
	{
	}


	SceneManager::~SceneManager()
	{
	}

	Entities::Scene* SceneManager::loadLevel(IO::VirtualFile* sceneFile)
	{

		char* scene_file_data_ptr = sceneFile->m_FileData;
		Entities::Scene* result = new Entities::Scene();

		//TODO: read in the data and convert it to a scene ptr
		//very convoluted
		unsigned int scene_data_byte_count = 0;
		while (scene_data_byte_count < sceneFile->m_FileHeader.vf_size)
		{
			Cooked_Scene_Entity_t tmp_entity_data = *(Cooked_Scene_Entity_t*)(scene_file_data_ptr);
			scene_file_data_ptr += sizeof(Cooked_Scene_Entity_t);
			scene_data_byte_count += sizeof(Cooked_Scene_Entity_t);

			//ptr is now at gameobject entity name
			//need to calculate the length of the name as it is not null terminated 
			//data should have length of 4
			//get vertex byte size, color byte size, indice byte size, transform and sub from entity size 
			unsigned int entity_name_size = tmp_entity_data.cse_byte_size - ((sizeof(glm::vec3) * tmp_entity_data.cse_vertex_count) + (2 * (sizeof(unsigned int) * tmp_entity_data.cse_indice_count) + sizeof(glm::quat) + sizeof(glm::vec3)));

			char tmp_name[128];
			for (size_t i = 0; i < (entity_name_size); i++)
			{
				tmp_name[i] = *(char*)(scene_file_data_ptr);
				scene_file_data_ptr++;
				scene_data_byte_count++;
			}
			const char* tmp_name_const = tmp_name;

			//transform
			glm::vec3 position = *(glm::vec3*)(scene_file_data_ptr);
			scene_file_data_ptr += sizeof(glm::vec3);
			scene_data_byte_count += sizeof(glm::vec3);

			glm::quat rotation = *(glm::quat*)(scene_file_data_ptr);
			scene_file_data_ptr += sizeof(glm::quat);
			scene_data_byte_count += sizeof(glm::quat);

			//vertices indices colours
			std::vector<glm::vec3> vertices;
			std::vector<unsigned int> indices;
			std::vector<unsigned int> colors;

			for (size_t i = 0; i < tmp_entity_data.cse_vertex_count; i++)
			{
				vertices.push_back(((glm::vec3)*(glm::vec3*)(scene_file_data_ptr)));
				scene_file_data_ptr += sizeof(glm::vec3);
				scene_data_byte_count += sizeof(glm::vec3);
			}

			for (size_t i = 0; i < tmp_entity_data.cse_indice_count; i++)
			{
				indices.push_back(((unsigned int)*(unsigned int*)(scene_file_data_ptr)));
				scene_file_data_ptr += sizeof(unsigned int);
				scene_data_byte_count += sizeof(unsigned int);
			}

			for (size_t i = 0; i < tmp_entity_data.cse_indice_count; i++)
			{
				colors.push_back(((unsigned int)*(unsigned int*)(scene_file_data_ptr)));
				scene_file_data_ptr += sizeof(unsigned int);
				scene_data_byte_count += sizeof(unsigned int);
			}

			Entities::GameObject* gameObject = new Entities::GameObject(tmp_name_const, position, new Graphics::Mesh(vertices, indices, colors));
			result->SceneData.push_back(gameObject);
		}

		return result;
	}

	IO::VirtualFile* SceneManager::cookLevelToVirtualFile(Entities::Scene* sceneToCook, const char* outputSceneName)
	{
		//THIS IS BY NO MEANS A GOOD WAY TO DO THIS
		//get the byte size for the whole level
		//package each as a cooked entity

		unsigned int scene_data_size = 0;
		scene_data_size += (sceneToCook->EnitityCount * sizeof(Cooked_Scene_Entity_t));

		for (size_t i = 0; i < sceneToCook->SceneData.size(); i++)
			scene_data_size += sceneToCook->SceneData[i]->getSize();


		IO::VF_Data_Param_t sceneVF_Header;
		sceneVF_Header.data_byte_size = scene_data_size;
		sceneVF_Header.byte_data = new char[scene_data_size + 1];
		sceneVF_Header.byte_data[scene_data_size + 1] = NULL;

		//allocate the data
		unsigned int bytes_written = 0;
		for (size_t i = 0; i < sceneToCook->SceneData.size(); i++)
		{
			//bake the scene metadata for each entity in the scene
			Cooked_Scene_Entity_t tmp_entity_metadata(EntityType::_Entity, 0, 0, 0);
			tmp_entity_metadata.cse_byte_size = sceneToCook->SceneData[i]->getSize();

			//add mesh info if applicable
			if (sceneToCook->SceneData[i]->mesh != NULL)
			{
				tmp_entity_metadata.cse_type = EntityType::_GameObject;
				tmp_entity_metadata.cse_vertex_count = sceneToCook->SceneData[i]->mesh->vertices.size();
				tmp_entity_metadata.cse_indice_count = sceneToCook->SceneData[i]->mesh->indices.size();
			}
			memcpy(&sceneVF_Header.byte_data[bytes_written], &tmp_entity_metadata, sizeof(Cooked_Scene_Entity_t));
			bytes_written += sizeof(Cooked_Scene_Entity_t);
			memcpy(&sceneVF_Header.byte_data[bytes_written], sceneToCook->SceneData[i]->getData(), tmp_entity_metadata.cse_byte_size);
			bytes_written += tmp_entity_metadata.cse_byte_size;
		}

		return new IO::VirtualFile(outputSceneName, IO::FileType::SCENE, sceneVF_Header);
	}

} } }