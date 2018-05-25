#include "vk_renderer.h"

#if(_ENGINE_RENDERER_VULKAN)
namespace Engine { namespace Core { namespace Graphics { namespace Vulkan {

	VKRenderer::VKRenderer(const Window& renderWindow)
	{

		m_VK_Surface.setupNativeWindowHandle(renderWindow, m_VK_GPU.m_VKInstance);
		init();
	}


	VKRenderer::~VKRenderer()
	{

	}

	void VKRenderer::init()
	{

	}

	void VKRenderer::begin()
	{

	}

	void VKRenderer::submit(Engine::Core::Graphics::Mesh* mesh, glm::vec3 position, glm::quat rotation)
	{

	}

	void VKRenderer::submit(Engine::Core::Graphics::Mesh* mesh)
	{
	
	}

	void VKRenderer::submit_triangle_test()
	{
		//used for testing vulkan
	}

	void VKRenderer::submit(Engine::Core::Entities::Entity* renderableEntity)
	{

	}

	void VKRenderer::end()
	{
		
	}

	void VKRenderer::draw()
	{
			
	}

	void VKRenderer::dispose()
	{
		m_VK_Surface.dispose(m_VK_GPU.m_VKInstance);
		m_VK_GPU.dispose();
	}

} } } }
#endif