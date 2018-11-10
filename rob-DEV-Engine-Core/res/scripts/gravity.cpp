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
	float delta = (float)((float)_PHYSICS_G * (float)std::pow(TIME->deltaTime, 2));
	this->m_GameObject->transform.position.y -= delta;
}