#include <iostream>
#include <thread>

#include "time/time.h"
#include "buildsystems/scene_manager.h"

#include "graphics/opengl/opengl_renderer.h"
#include "graphics/direct3d/direct3d_renderer.h"
#include "graphics/vulkan/vk_renderer.h"

#include "entity/entity.h"
#include "entity/game_object.h"
#include "entity/camera.h"
#include "entity/scene.h"

#include "io/file/virtual_file.h"
#include "io/filesystem/virtual_file_system.h"
#include "io/importers/obj/obj_importer.h"

//USERMODE GAMEOBJECT RUNTIME BEHAVIOUR
#include "../res/scripts/rotate.h"
#include "../res/scripts/movement.h"


using namespace Engine::Core;
using namespace Engine::Core::BuildSystems;
using namespace Engine::Core::Graphics;

#if _ENGINE_RENDERER_OPENGL
using namespace Engine::Core::Graphics::OpenGL;
#endif
#if _ENGINE_RENDERER_VULKAN
using namespace Engine::Core::Graphics::Vulkan;
#endif
#if _ENGINE_RENDERER_DIRECT3D
using namespace Engine::Core::Graphics::Direct3D;
#endif

using namespace Engine::Core::Entities;
using namespace Engine::Core::IO;
using namespace Engine::Core::IO::Importers;


void render(Window* window, OpenGLRenderer* renderer, Camera* camera, Scene* loadedLevel)
{
	window->clear();
	//light test
	renderer->Shaders->setUniform2f("light_pos", glm::vec2((float)(-INPUT->NormalisedMouseX / 10), (float)(INPUT->NormalisedMouseY / 10)));
	//camera pos update
	renderer->Shaders->setUniformMat4("vw_matrix", camera->getViewMatrix());

	renderer->begin();
	//limit to 5 entity
	//for (size_t i = 0; i < loadedLevel->SceneData.size(); i++)
	for (size_t i = 0; i < 15; i++)
		renderer->submit(loadedLevel->SceneData[i]);

	renderer->end();
	renderer->draw();

	window->update();
}

static bool* canUpdate = new bool();

void setFPSLimit(float fpsLimit)
{
	// Convert fps to time
	static float timeDelay = 1 / fpsLimit;

	// Measure time elapsed
	static float timeElapsed = 0;

	float currentTime = glfwGetTime();
	static float totalTimeDelay = timeDelay + glfwGetTime();

	if (currentTime > totalTimeDelay)
	{
		totalTimeDelay = timeDelay + glfwGetTime();
		*canUpdate = true;
	}
	else
		*canUpdate = false;
}

void update(Camera* camera, Scene* loadedLevel)
{
	while (true)
	{
		if (*canUpdate == true)
		{
			*canUpdate = false;
			//camera test
			camera->Tick();

			for (size_t i = 0; i < loadedLevel->SceneData.size(); i++)
				loadedLevel->SceneData[i]->Tick();
		}
	}
}

int main()
{
	double time_passed = 0;
	uint32_t frames = 0;


	Window* window = new Window("MAIN ENGINE WINDOW", 1280, 720);
	OpenGLRenderer* renderer = new OpenGLRenderer();

	glm::mat4 pr_matrix = glm::perspective(glm::radians(90.0f), 16.0f / 9.0f, 0.1f, 10000.0f);

	renderer->Shaders->setUniformMat4("pr_matrix", pr_matrix);
	renderer->Shaders->setUniformMat4("ml_matrix", glm::mat4(1.0f));

	Mesh* cube_load = OBJ_IMPORTER->ImportObj("res/obj/cube.obj");
	Mesh* monkey_load = OBJ_IMPORTER->ImportObj("res/obj/monkey.obj");

	VirtualFileSystem* vfs = VirtualFileSystem::Open("res/filesystems/DATA.VFS");

	//loading monkey level instead of test.level
	Scene* loadedLevel = SCENE_MANAGER->loadLevel(vfs->Retrieve("multiple_gameobject.level"));
	Camera* camera = new Camera("Main Camera", glm::vec3(20, 10, -20));

	//assign a new behaviour script to an object in the scene
	for (size_t i = 0; i < 20; i++)
		loadedLevel->SceneData[i]->AddBehaviourScript(new Rotate());

	loadedLevel->SceneData[1]->AddBehaviourScript(new Movement());
	camera->AddBehaviourScript(new Movement());

	//per-game initalization
	for (size_t i = 0; i < loadedLevel->SceneData.size(); i++)
		loadedLevel->SceneData[i]->Init();

	std::thread updateLogicThread(update, camera, loadedLevel);


	while (!window->closed())
	{
		render(window, renderer, camera, loadedLevel);

		setFPSLimit(60);

		frames++;

		if (TIME->elasped() - time_passed > 1.0f)
		{
			time_passed += 1.0f;
			printf("%dfps\n", frames);
			printf("%d Entities\n", Entity::number_entities);
			frames = 0;
		}

		if (INPUT->getKeyDown(GLFW_KEY_ESCAPE))
			break;

		
	}

	updateLogicThread.detach();
	
	window->dispose();
	
	#if _ENGINE_RENDERER_VULKAN
		renderer.dispose();
	#endif
}