#pragma once
#include "../../src/include/EngineCore.h"

class Movement : public Engine::Core::Entities::GameObject_Behaviour
{
public:
	Movement();
	~Movement();

	void Start() override;
	void Tick() override;
};

