#pragma once
#include "../../src/include/EngineCore.h"

class Rotate : public GameObject_Behaviour
{
public:
	Rotate();
	~Rotate();


	void Start() override;
	void Tick() override;

};

