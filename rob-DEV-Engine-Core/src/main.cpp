#include <iostream>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include "utils/timer.h"
#include "graphics/window.h"
#include "graphics/renderer.h"
#include "entity/entity.h"
#include "entity/game_object.h"
#include "io/obj/object_importer.h"

using namespace Engine::Core;
using namespace Engine::Core::Graphics;
using namespace Engine::Core::Entities;
using namespace Engine::Core::IO::Importers;


#define INPUT Input::getInputInstance()

int main()
{
	Timer timer;
	float time = 0;
	unsigned int frames = 0;

	Window window("MAIN ENGINE", 640, 480);
	glClearColor(0.02f, 0.55f, 1.0f, 1.0f);

	Renderer renderer;
	
	glm::mat4 pr_matrix = glm::perspective(glm::radians(90.0f), 16.0f / 9.0f, 0.1f, 10000.0f);

	glm::mat4 vw_matrix = glm::lookAt(
		glm::vec3(10, 4, -7), // Camera is at (4,3,-3), in World Space
		glm::vec3(0, 0, 0), // and looks at the origin
		glm::vec3(0, 1, 0)  // Head is up (set to 0,-1,0 to look upside-down)
	);

	//vw_matrix = glm::rotate(vw_matrix, 10.0f, glm::vec3(1, 0, 0));

	renderer.Shaders->setUniformMat4("pr_matrix", pr_matrix);
	renderer.Shaders->setUniformMat4("vw_matrix", vw_matrix);
	renderer.Shaders->setUniformMat4("ml_matrix", glm::mat4(1.0f));


	Mesh manualMesh("MANUAL_TEST");
	manualMesh.vertices.push_back(glm::vec3(1, 1, -1));
	manualMesh.vertices.push_back(glm::vec3(1, -1, -1));
	manualMesh.vertices.push_back(glm::vec3(-1, -1, -1));
	manualMesh.vertices.push_back(glm::vec3(-1, 1, -1));

	manualMesh.vertices.push_back(glm::vec3(-1, -1, 1));
	manualMesh.vertices.push_back(glm::vec3(-1, 1, 1));
	manualMesh.vertices.push_back(glm::vec3(1, -1, 1));
	manualMesh.vertices.push_back(glm::vec3(1, 1, 1));


	Mesh testLoad = *Obj_Importer::getObjImporterInstance()->ImportObj("src/io/obj/monkey.obj");
	Mesh testLoad2 = *Obj_Importer::getObjImporterInstance()->ImportObj("src/io/obj/cube.obj");
	GameObject testGameObject("GAMEOBJECT_ENTITY", glm::vec3(0, 0, 0), testLoad);
	GameObject testGameObject2("GAMEOBJECT_ENTITY", glm::vec3(1, -5, 1), testLoad2);

	while (!window.closed())
	{
		window.clear();

		renderer.begin();

		renderer.submit(testGameObject);
		renderer.submit(testGameObject2);

		renderer.end();

		renderer.draw();
		
		window.update();

		
		if (INPUT->getKeyDown(GLFW_KEY_ESCAPE))
			exit(0);


		frames++;
		if (timer.elasped() - time > 1.0f)
		{
			time += 1.0f;
			printf("%dfps\n", frames);
			frames = 0;

		}
	}
}