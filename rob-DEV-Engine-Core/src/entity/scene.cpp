#include "../io/common/file_types.h"
#include "scene.h"

namespace Engine { namespace Core { namespace Entities {
	Scene::Scene(const char* sceneName)
	{
		m_SceneName = sceneName;
	}


	Scene::~Scene()
	{
	}

	void Scene::push_to_scene_data(GameObject* entity)
	{
		m_SceneData.push_back(entity);
	}

	IO::VirtualFile* Scene::bake_scene_data_to_file(const char* sceneFileName)
	{
		//OUTPUT TO A V-FILE
		IO::VF_Data_Param_t sceneFileData;
		sceneFileData.data_byte_size = 0;
		sceneFileData.data_byte_size += (strlen(m_SceneName.c_str()) * sizeof(char));

		for (size_t i = 0; i < m_SceneData.size(); i++)
		{
			//EVERY entity has a name and postion
			sceneFileData.data_byte_size += (strlen(m_SceneData[i]->name.c_str()) * sizeof(char));
			sceneFileData.data_byte_size += (sizeof(glm::vec3) + sizeof(glm::quat));

			if (m_SceneData[i]->mesh != NULL)
			{
				//SERIALIZE THE GAMEOBJECT NAME AND POSTION TO BYTE DATA
				sceneFileData.data_byte_size += (sizeof(glm::vec3) * m_SceneData[i]->mesh->vertices.size());
				sceneFileData.data_byte_size += (sizeof(unsigned int) * m_SceneData[i]->mesh->rgb_colors.size());
			}

		}

		sceneFileData.byte_data = new char[sceneFileData.data_byte_size + 1];
		sceneFileData.byte_data[sceneFileData.data_byte_size + 1] = NULL;

		unsigned int byte_count = 0;
		for (size_t i = 0; i < m_SceneData.size(); i++)
		{
			//EVERY entity has a name and postion
			memcpy(&sceneFileData.byte_data[byte_count], &m_SceneData[i]->name.c_str()[0] , strlen(m_SceneData[i]->name.c_str()) * sizeof(char));
			byte_count += strlen(m_SceneData[i]->name.c_str()) * sizeof(char);
			memcpy(&sceneFileData.byte_data[byte_count], &m_SceneData[i]->transform.position, sizeof(glm::vec3));
			byte_count += sizeof(glm::vec3);
			memcpy(&sceneFileData.byte_data[byte_count], &m_SceneData[i]->transform.rotation, sizeof(glm::quat));
			byte_count += sizeof(glm::quat);

			if (m_SceneData[i]->mesh != NULL)
			{
				//SERIALIZE THE GAMEOBJECT NAME AND POSTION TO BYTE DATA
				memcpy(&sceneFileData.byte_data[byte_count], &m_SceneData[i]->mesh->vertices[0], (sizeof(glm::vec3) * m_SceneData[i]->mesh->vertices.size()));
				byte_count += (sizeof(glm::vec3) * m_SceneData[i]->mesh->vertices.size());
				memcpy(&sceneFileData.byte_data[byte_count], &m_SceneData[i]->mesh->rgb_colors[0], (sizeof(unsigned int) * m_SceneData[i]->mesh->rgb_colors.size()));
				byte_count += (sizeof(unsigned int) * m_SceneData[i]->mesh->rgb_colors.size());
			}

		}

		return new IO::VirtualFile(sceneFileName, IO::FileType::SCENE, sceneFileData);
	}

} } }