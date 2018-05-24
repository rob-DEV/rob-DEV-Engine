#include "vk_surface.h"

#if(ENGINE_RENDERER_VULKAN)
namespace Engine { namespace Core { namespace Graphics { namespace Vulkan {

	VK_Surface::VK_Surface()
	{
		
	}

	VK_Surface::VK_Surface(const Window& renderWindow)
	{
		VkWin32SurfaceCreateInfoKHR createInfo;
		createInfo.sType = VK_STRUCTURE_TYPE_WIN32_SURFACE_CREATE_INFO_KHR;
		createInfo.hwnd = glfwGetWin32Window(renderWindow.getGLFWNativeWindow());
		createInfo.hinstance = GetModuleHandle(nullptr);
	}

	VK_Surface::~VK_Surface()
	{

	}

	void VK_Surface::init()
	{
		

	}

} } } }

#endif