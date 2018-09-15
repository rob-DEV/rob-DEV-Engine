#include "camera.h"


namespace Engine { namespace Core { namespace Entities {

	Camera::Camera() : GameObject()
	{

	}
	
	Camera::Camera(const char* name, glm::vec3 position) : GameObject(name, position, new Graphics::Mesh())
	{
		glm::lookAt(this->transform.position, glm::vec3(0, 0, 0), glm::vec3(0, 1, 0));

		//redundant
		this->mesh = NULL;
		
	}

	Camera::~Camera()
	{
	}

	uint32_t Camera::getSize()
	{
		//base size + vertex mesh data
		uint32_t base = Entity::getSize();

		return base;
	}

	void Camera::AddBehaviourScript(GameObject_Behaviour* behavior)
	{
		behavior->m_GameObject = this;
		m_RuntimeBehaviours.push_back(behavior);
	}

	void Camera::Init()
	{
		//update all script behaviours
		for (size_t i = 0; i < m_RuntimeBehaviours.size(); i++)
			m_RuntimeBehaviours[i]->Start();
	}

	void Camera::Tick()
	{
		//update all script behaviours
		for (size_t i = 0; i < m_RuntimeBehaviours.size(); i++)
			m_RuntimeBehaviours[i]->Tick();

		m_ViewMatrix = glm::lookAt(this->transform.position, glm::vec3(0, 0, 0), glm::vec3(0, 1, 0));
	}

}  }  }