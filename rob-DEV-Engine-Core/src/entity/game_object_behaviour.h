#pragma once
#include "entity.h"

class GameObject_Behaviour 
{
	//the gameobject which has this behaviour attached to it

public:
	Engine::Core::Entities::Entity*  m_GameObject;
	//called when a gameobject is initalized

	inline GameObject_Behaviour() { }
	//inline GameObject_Behaviour(Engine::Core::Entities::Entity*  m_Parent) { this->m_GameObject = m_Parent; }
	inline virtual ~GameObject_Behaviour() {}
	inline virtual void Start() {}

	//caled each frame
	inline virtual void Tick() {}
};