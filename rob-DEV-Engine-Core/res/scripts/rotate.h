//TEST GAMEOBJECT BEHAVIOUR FOR SCENE ENTITY
#pragma once
#include "../../src/include/EngineCore.h"

class Rotate : public Engine::Core::Entities::GameObject_Behaviour
{
public:
	Rotate();
	~Rotate();


	void Start() override;
	void Tick() override;

};

