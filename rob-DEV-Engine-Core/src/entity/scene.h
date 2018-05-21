#pragma once
#include <vector>
#include "game_object.h"
#include "../io/file/virtual_file.h"

namespace Engine { namespace Core { namespace Entities {

	class Scene
	{
	public:
		std::string m_SceneName;
		//EVERY SCENE IS JUST AN ARRAGEMENT OF GAMEOBJECTS
		std::vector<GameObject*> m_SceneData;
		Scene(const char* sceneName);
		~Scene();

		void push_to_scene_data(GameObject* entity);
		IO::VirtualFile* bake_scene_data_to_file(const char* sceneFileName);

	};

} } }
