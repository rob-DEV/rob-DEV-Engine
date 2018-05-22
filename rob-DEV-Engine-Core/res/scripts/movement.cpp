#include "movement.h"

Movement::Movement()
{
}


Movement::~Movement()
{
}

void Movement::Start()
{

}

void Movement::Tick()
{
	//player movement test
	//this will move an object based on user input
	if (INPUT->getKeyDown(GLFW_KEY_W))
		m_GameObject->transform.position.x += 0.1f;
	if (INPUT->getKeyDown(GLFW_KEY_A))
		m_GameObject->transform.position.z += 0.1f;
	if (INPUT->getKeyDown(GLFW_KEY_S))
		m_GameObject->transform.position.x -= 0.1f;
	if (INPUT->getKeyDown(GLFW_KEY_D))
		m_GameObject->transform.position.z -= 0.1f;
}