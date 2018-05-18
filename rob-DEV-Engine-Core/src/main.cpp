#include <iostream>

#include "time/time.h"
#include "graphics/window.h"
#include "graphics/renderer.h"
#include "entity/entity.h"
#include "entity/game_object.h"
#include "io/obj/obj_importer.h"

using namespace Engine::Core;
using namespace Engine::Core::Graphics;
using namespace Engine::Core::Entities;
using namespace Engine::Core::IO::Importers;

int main()
{
	double time_passed = 0;
	unsigned int frames = 0;

	Window window("MAIN ENGINE", 640, 480);
	glClearColor(0.02f, 0.55f, 1.0f, 1.0f);

	Renderer renderer;
	
	glm::mat4 pr_matrix = glm::perspective(glm::radians(90.0f), 16.0f / 9.0f, 0.1f, 10000.0f);

	glm::mat4 vw_matrix = glm::lookAt(
		glm::vec3(10, 4, -10), // Camera is at (4,3,-3), in World Space
		glm::vec3(0, 0, 0), // and looks at the origin
		glm::vec3(0, 1, 0)  // Head is up (set to 0,-1,0 to look upside-down)
	);

	//vw_matrix = glm::rotate(vw_matrix, 10.0f, glm::vec3(1, 0, 0));

	renderer.Shaders->setUniformMat4("pr_matrix", pr_matrix);
	renderer.Shaders->setUniformMat4("vw_matrix", vw_matrix);
	renderer.Shaders->setUniformMat4("ml_matrix", glm::mat4(1.0f));


	Mesh cube_load = *OBJ_IMPORTER->ImportObj("src/io/obj/cube.obj");
	Mesh monkey_load = *OBJ_IMPORTER->ImportObj("src/io/obj/monkey.obj");
	GameObject cube("GAMEOBJECT_ENTITY", glm::vec3(4, -3, 0), cube_load);
	GameObject cube2("GAMEOBJECT_ENTITY", glm::vec3(3, -3, 8), cube_load);
	GameObject monkey("GAMEOBJECT_ENTITY", glm::vec3(0, 0, 0), monkey_load);

	while (!window.closed())
	{
		window.clear();

		//light test
		renderer.Shaders->setUniform2f("light_pos", glm::vec2((float)(-INPUT->NormalisedMouseX / 10), (float)(INPUT->NormalisedMouseY / 10)));

		renderer.begin();

		renderer.submit(cube);
		renderer.submit(cube2);

		monkey.transform.rotate(glm::vec3(0, 1 * TIME->deltaTime, 0));
		cube.transform.rotate(glm::vec3(2 * TIME->deltaTime, 2 * TIME->deltaTime, 2 * TIME->deltaTime));

		renderer.submit(monkey);

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
			frames = 0;

		}
	}
}