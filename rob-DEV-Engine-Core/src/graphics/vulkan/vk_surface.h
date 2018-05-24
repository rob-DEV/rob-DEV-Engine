#include "vk_include.h"
#include "../window.h"

#if(ENGINE_RENDERER_VULKAN)
namespace Engine { namespace Core { namespace Graphics { namespace Vulkan {

	class VK_Surface 
	{
	private:
		void init();
	public:
		VkSurfaceKHR VkSurfaceHandle;

		VK_Surface();
		VK_Surface(const Window& renderWindow);

		~VK_Surface();
		
	};

} } } }
#endif