#include <vulkan.h>
#include "vk_instance.h"

namespace Engine { namespace Core { namespace Graphics { namespace Vulkan {

	struct QueueFamilyIndices {
		int graphicsFamily = -1;
		bool isComplete() {
			return graphicsFamily >= 0;
		}
	};

	class VKLogicalDevice 
	{
	private:
		
		//VkLogicalDevice m_LogicalDevice = VK_NULL_HANDLE;
		void init();
		bool isSupportedDevice(VkPhysicalDevice device);
		QueueFamilyIndices findQueueFamilies(VkPhysicalDevice device);
	public:
		VKInstance m_VKInstance;
		VKLogicalDevice();
		~VKLogicalDevice();
		
	};

} } } }