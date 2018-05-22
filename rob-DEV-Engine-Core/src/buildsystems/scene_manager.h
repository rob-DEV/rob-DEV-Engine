#pragma once
#include "../common/singleton_instance.h"
#include "../entity/scene.h"
#include "../io/file/virtual_file.h"

namespace Engine { namespace Core {namespace BuildSystems {
	
	#define SCENE_MANAGER SceneManager::getInstance()

	enum EntityType { _Entity, _GameObject, _Light };

	typedef struct Cooked_Scene_Entity
	{
		EntityType cse_type;
		unsigned int cse_byte_size;
		unsigned int cse_vertex_count;
		unsigned int cse_indice_count;

		Cooked_Scene_Entity(EntityType type, unsigned int byte_size, unsigned int vertex_count, unsigned int indice_count)
		{
			cse_type = type; cse_byte_size = byte_size; cse_vertex_count = vertex_count; cse_indice_count = indice_count;
		}

	} Cooked_Scene_Entity_t;

	class SceneManager : public Singleton_Instance
	{
	public:
		SceneManager();
		~SceneManager();
		static SceneManager* getInstance();

		Entities::Scene* loadLevel(IO::VirtualFile* sceneFile);
		IO::VirtualFile* cookLevelToVirtualFile(Entities::Scene* sceneToCook, const char* outputSceneName);
	};

} } }
