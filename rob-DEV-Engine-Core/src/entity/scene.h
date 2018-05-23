#pragma once
#include <vector>
#include "game_object.h"
#include "../io/file/virtual_file.h"

namespace Engine { namespace Core { namespace Entities {

	class Scene
	{
	public:
		uint32_t EnitityCount;
		//EVERY SCENE IS JUST AN ARRAGEMENT OF GAMEOBJECTS
		std::vector<GameObject*> SceneData;
		Scene();
		~Scene();

		void push_to_scene_data(GameObject* entity);

	};

} } }
