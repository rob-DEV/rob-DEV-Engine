#pragma once
#include <EngineCore.h>

class Movement : public Engine::Core::Entities::GameObject_Behaviour
{
public:
	Movement();
	~Movement();

	float m_Speed = 2.0f;
	void Start() override;
	void Tick() override;
};

