#include "vk_instance.h"

#if(ENGINE_RENDERER_VULKAN)
namespace Engine { namespace Core { namespace Graphics { namespace Vulkan {

	struct QueueFamilyIndices {
		int graphicsFamily = -1;
		bool isComplete() {
			return graphicsFamily >= 0;
		}
	};

	class VK_GPU 
	{
	public:
		//physical
		VkPhysicalDevice VkPhysicalDeviceHandle = VK_NULL_HANDLE;
		VkDevice VkLogicalDeviceHandle = VK_NULL_HANDLE;
		VkQueue VkGraphicsQueueHandle = VK_NULL_HANDLE;

	private:
		void init();
		bool isSupportedDevice(VkPhysicalDevice device);
		QueueFamilyIndices findQueueFamilies(VkPhysicalDevice device);
	public:
		VKInstance m_VKInstance;
		VK_GPU();
		~VK_GPU();
		
	};

} } } }
#endif