#include "scene_manager.h"

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
		return NULL;
	}

	IO::VirtualFile* SceneManager::cookLevelToVirtualFile(Entities::Scene* sceneToCook)
	{
		//THIS IS BY NO MEANS A GOOD WAY TO DO THIS
		//get the byte size for the whole level
		//package each as a cooked entity

		unsigned int scene_data_size = 0;

		//uint id and uint gameObject count
		scene_data_size += 8;

		for (size_t i = 0; i < sceneToCook->SceneData.size(); i++)
		{
			scene_data_size += sceneToCook->SceneData[i]->getSize();
		}

		IO::VF_Data_Param_t sceneVF_Header;
		sceneVF_Header.data_byte_size = scene_data_size;
		sceneVF_Header.byte_data = new char[scene_data_size + 1];
		sceneVF_Header.byte_data[scene_data_size + 1] = NULL;

		//allocate the data
		unsigned int bytes_written = 0;
		for (size_t i = 0; i < sceneToCook->SceneData.size(); i++)
		{
			//this is 110% safe!!
			memcpy(&sceneVF_Header.byte_data[bytes_written], sceneToCook->SceneData[i]->getData(), sceneToCook->SceneData[i]->getSize());
			bytes_written += sceneToCook->SceneData[i]->getSize();
		}

		return new IO::VirtualFile("test.level", IO::FileType::SCENE,sceneVF_Header);
	}

} } }