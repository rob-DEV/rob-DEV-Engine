#include "gravity.h"

Gravity::Gravity()
{

}

Gravity::~Gravity()
{

}

void Gravity::Start()
{

}

void Gravity::Tick()
{
	//gravity tick
	//s = ut + 1/2at^2
	//modify vector pos y by that value
	m_Acc += _PHYSICS_G * TIME->deltaTime;

	if (m_Acc >= (float)_PHYSICS_G)
		m_Acc = (float)_PHYSICS_G;

	float delta = (float)(((float)_PHYSICS_G * m_Acc)* (float)std::pow(TIME->deltaTime, 2));

	std::cout << m_Acc << "\n";

	this->m_GameObject->transform.position.y -= delta;
}