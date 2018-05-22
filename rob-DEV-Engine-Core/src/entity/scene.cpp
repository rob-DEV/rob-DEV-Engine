#include "../io/common/file_types.h"
#include "scene.h"

namespace Engine { namespace Core { namespace Entities {
	Scene::Scene()
	{
	}


	Scene::~Scene()
	{
	}

	void Scene::push_to_scene_data(GameObject* entity)
	{
		SceneData.push_back(entity);
		GameobjectCount = SceneData.size();
	}

} } }