#include <vulkan.h>
#include "vk_instance.h"

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
		VkPhysicalDevice PhysicalDevice = VK_NULL_HANDLE;
		VkDevice LogicalDevice = VK_NULL_HANDLE;
		VkQueue GraphicsQueue = VK_NULL_HANDLE;

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