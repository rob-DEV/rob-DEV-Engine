#include <iostream>

#include "time/time.h"

#include "graphics/window.h"
#include "graphics/renderer.h"

#include "entity/entity.h"
#include "entity/game_object.h"
#include "entity/scene.h"

#include "io/file/virtual_file.h"
#include "io/filesystem/virtual_file_system.h"
#include "io/importers/obj/obj_importer.h"

using namespace Engine::Core;
using namespace Engine::Core::Graphics;
using namespace Engine::Core::Entities;
using namespace Engine::Core::IO;
using namespace Engine::Core::IO::Importers;

int main()
{
	double time_passed = 0;
	unsigned int frames = 0;

	Window window("MAIN ENGINE", 640, 480);
	glClearColor(0.02f, 0.55f, 1.0f, 1.0f);

	Renderer renderer;
	Renderer renderer2;
	
	glm::mat4 pr_matrix = glm::perspective(glm::radians(90.0f), 16.0f / 9.0f, 0.1f, 10000.0f);

	glm::mat4 vw_matrix = glm::lookAt(
		glm::vec3(10, 4, -10), // Camera is at (4,3,-3), in World Space
		glm::vec3(0, 0, 0), // and looks at the origin
		glm::vec3(0, 1, 0)  // Head is up (set to 0,-1,0 to look upside-down)
	);

	renderer.Shaders->setUniformMat4("pr_matrix", pr_matrix);
	renderer.Shaders->setUniformMat4("vw_matrix", vw_matrix);
	renderer.Shaders->setUniformMat4("ml_matrix", glm::mat4(1.0f));

	Mesh* cube_load = OBJ_IMPORTER->ImportObj("res/obj/cube.obj");
	Mesh* monkey_load = OBJ_IMPORTER->ImportObj("res/obj/monkey.obj");

	VirtualFileSystem* vfs = VirtualFileSystem::Open("res/filesystems/DATA.VFS");

	//NEW SCENE OBJECT
	Scene* testingScene = new Scene("TEST_LEVEL");

	

	#if(DEBUG)
	//much slower therefore less models
	for (size_t i = 0; i < 1; i++)
	{
		for (size_t j = 0; j < 1; j++)
		{
			testingScene->push_to_scene_data(new GameObject("GAMEOBJECT_ENTITY", glm::vec3((float)(i * 3), -3, -(float)(j * 8)), cube_load));
		}
	}
	
	#else

	for (size_t i = 0; i < 2000; i++)
	{
		for (size_t j = 0; j < 10; j++)
		{
			testingScene->push_to_scene_data(new GameObject("GAMEOBJECT_ENTITY", glm::vec3(-(float)(i * 3), -3, -(float)(j * 8)), cube_load));
		}
	}
	#endif


	//VirtualFile* sceneFile = testingScene->bake_scene_data_to_file("TestLevel.level");

	//vfs->AddFile(sceneFile, true);

	VirtualFile* sceneFile = vfs->Retrieve("TestLevel.level");

	while (!window.closed())
	{
		window.clear();

		//light test
		renderer.Shaders->setUniform2f("light_pos", glm::vec2((float)(-INPUT->NormalisedMouseX / 10), (float)(INPUT->NormalisedMouseY / 10)));

		renderer.begin();

		for (size_t i = 0; i < testingScene->m_SceneData.size(); i++)
			renderer.submit(testingScene->m_SceneData[i]);

		renderer.end();
		renderer.draw();
		
		window.update();

		if (INPUT->getKeyDown(GLFW_KEY_ESCAPE))
			exit(0);

		frames++;

		if (TIME->elasped() - time_passed > 1.0f)
		{
			time_passed += 1.0f;
			printf("%dfps\n", frames);
			printf("%d Entities\n", Entity::number_entities);
			frames = 0;

		}
	}
}