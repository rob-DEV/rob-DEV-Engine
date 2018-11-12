#pragma once
#include <EngineCore.h>

class Gravity : public Engine::Core::Entities::GameObject_Behaviour
{
public:

	Gravity();
	~Gravity();

	float m_Mass = 1.0f;
	float m_Acc = 0.0f;

	void Start() override;
	void Tick() override;
};

