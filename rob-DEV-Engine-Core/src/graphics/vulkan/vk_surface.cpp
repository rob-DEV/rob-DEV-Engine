#include "vk_surface.h"
#include <iostream>

#if(_ENGINE_RENDERER_VULKAN)
namespace Engine { namespace Core { namespace Graphics { namespace Vulkan {

	VKSurface::VKSurface()
	{

	}

	VKSurface::~VKSurface()
	{

	}

	void VKSurface::setupNativeWindowHandle(const Window& renderWindow, const VKInstance& vkInstance)
	{
		VkWin32SurfaceCreateInfoKHR createInfo;
		createInfo.sType = VK_STRUCTURE_TYPE_WIN32_SURFACE_CREATE_INFO_KHR;
		createInfo.hwnd = glfwGetWin32Window(renderWindow.getGLFWNativeWindow());
		createInfo.hinstance = GetModuleHandle(NULL);

		if (glfwCreateWindowSurface(vkInstance.VkInstanceHandle, renderWindow.getGLFWNativeWindow(), NULL, &VkSurfaceHandle) != VK_SUCCESS)
			std::cout << "Vulkan Error: Failed to create window surface\n";
	}

	void VKSurface::dispose(const VKInstance& vkInstance)
	{
		vkDestroySurfaceKHR(vkInstance.VkInstanceHandle, VkSurfaceHandle, NULL);
	}


} } } }

#endif