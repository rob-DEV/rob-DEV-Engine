#pragma once
#include <vector>
#include "game_object.h"
#include "../io/file/virtual_file.h"

namespace Engine { namespace Core { namespace Entities {

	class Scene
	{
	public:
		unsigned int SceneID = 0;
		unsigned int GameobjectCount;
		//EVERY SCENE IS JUST AN ARRAGEMENT OF GAMEOBJECTS
		std::vector<GameObject*> SceneData;
		Scene();
		~Scene();

		void push_to_scene_data(GameObject* entity);
		IO::VirtualFile* bake_scene_data_to_file(const char* sceneFileName);

	};

} } }
