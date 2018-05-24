#pragma once
#include <vulkan.h>
#include <vector>

namespace Engine { namespace Core { namespace Graphics { namespace Vulkan {

	class VKInstance
	{
	public:
		VkInstance Instance_Handle = VK_NULL_HANDLE;
		VkResult InstanceResult;
	private:
		std::vector<const char*> m_VKRequiredExtensions;
		std::vector<VkExtensionProperties> m_VKSupportedExtensionsInfo;
		std::vector<VkLayerProperties> m_VKAvailableValidationLayers;

		//tells vulkan what layers it should use (using standard validation atm)
		std::vector<const char*> m_ValidationLayers = { "VK_LAYER_LUNARG_standard_validation" };

		#if(DEBUG)
		//using VKAPI standard validation layers
		const bool m_EnableValidationLayers = true;
		#else
		const bool m_EnableValidationLayers = false;
		#endif
		VkDebugReportCallbackEXT m_DebuggingCallBack;

		//renderer error handle debug callback
		static VKAPI_ATTR VkBool32 VKAPI_CALL vkDebugCallback(VkDebugReportFlagsEXT flags, VkDebugReportObjectTypeEXT objType, uint64_t obj, uint32_t location, int32_t code, const char* layerPrefix, const char* msg, void* userData);

		void init();
		bool checkValidationLayersSupport();
		void setupRequiredExtensions();
		void createVulkanInstance();
		void setupDebugErrorCallback();
	public:
		VKInstance();
		~VKInstance();
		void destroy();
	};

} } } }
