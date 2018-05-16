#include <iostream>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include "time/debug_timer.h"
#include "time/time.h"
#include "graphics/window.h"
#include "graphics/renderer.h"
#include "entity/entity.h"
#include "entity/game_object.h"
#include "io/obj/object_importer.h"

using namespace Engine::Core;
using namespace Engine::Core::Graphics;
using namespace Engine::Core::Entities;
using namespace Engine::Core::IO::Importers;


#define INPUT Input::getInstance()

int main()
{
	Timer timer;
	Time time;
	float time_passed = 0;
	unsigned int frames = 0;

	double lastTime = 0;
	double deltaTime = 0;


	Window window("MAIN ENGINE", 640, 480);
	glClearColor(0.02f, 0.55f, 1.0f, 1.0f);

	Renderer renderer;
	
	glm::mat4 pr_matrix = glm::perspective(glm::radians(90.0f), 16.0f / 9.0f, 0.1f, 10000.0f);

	glm::mat4 vw_matrix = glm::lookAt(
		glm::vec3(20, 4, -0), // Camera is at (4,3,-3), in World Space
		glm::vec3(0, 0, 0), // and looks at the origin
		glm::vec3(0, 1, 0)  // Head is up (set to 0,-1,0 to look upside-down)
	);

	//vw_matrix = glm::rotate(vw_matrix, 10.0f, glm::vec3(1, 0, 0));

	renderer.Shaders->setUniformMat4("pr_matrix", pr_matrix);
	renderer.Shaders->setUniformMat4("vw_matrix", vw_matrix);
	renderer.Shaders->setUniformMat4("ml_matrix", glm::mat4(1.0f));


	Mesh cube_load = *Obj_Importer::getObjImporterInstance()->ImportObj("src/io/obj/cube.obj");
	Mesh monkey_load = *Obj_Importer::getObjImporterInstance()->ImportObj("src/io/obj/monkey.obj");
	GameObject cube("GAMEOBJECT_ENTITY", glm::vec3(0, 0, 0), cube_load);
	GameObject cube2("GAMEOBJECT_ENTITY", glm::vec3(3, -3, 8), cube_load);
	GameObject monkey("GAMEOBJECT_ENTITY", glm::vec3(0, 0, 0), monkey_load);


	glm::mat4 s(1.0f);

	while (!window.closed())
	{
		window.clear();

		renderer.begin();

		
		renderer.submit(cube);
		renderer.submit(cube2);

		monkey.transform.Rotate(glm::vec3(0, 1 * deltaTime, 0));
		
		renderer.submit(monkey);
		

		renderer.end();

		renderer.draw();
		
		window.update();

		
		if (INPUT->getKeyDown(GLFW_KEY_ESCAPE))
			exit(0);


		deltaTime = timer.elasped() - lastTime;
		lastTime = timer.elasped();

		printf("%f\n", deltaTime);

		frames++;
		if (timer.elasped() - time_passed > 1.0f)
		{
			time_passed += 1.0f;
			//printf("%dfps\n", frames);
			frames = 0;

		}
	}
}