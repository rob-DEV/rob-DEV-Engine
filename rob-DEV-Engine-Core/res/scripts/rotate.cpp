#include "rotate.h"

Rotate::Rotate()
{
}

Rotate::~Rotate()
{
}


void Rotate::Start()
{

}

void Rotate::Tick()
{
	m_GameObject->transform.rotate(glm::vec3(0, 10 * TIME->deltaTime, 0));
}