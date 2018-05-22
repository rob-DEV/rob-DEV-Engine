#pragma once
#include "../../src/include/EngineCore.h"

class Movement : public GameObject_Behaviour
{
public:
	Movement();
	~Movement();

	void Start() override;
	void Tick() override;
};

