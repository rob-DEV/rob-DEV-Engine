#pragma once
#include "vk_include.h"

#if(_ENGINE_RENDERER_VULKAN)
#include <vector>
namespace Engine { namespace Core { namespace Graphics { namespace Vulkan {

	class VKInstance
	{
	public:
		VkInstance VkInstanceHandle = VK_NULL_HANDLE;
		VkResult VkInstanceResult;

		std::vector<VkLayerProperties> VkAvailableValidationLayers;
		//tells vulkan what layers it should use (using standard validation atm)
		const std::vector<const char*> ValidationLayers = { "VK_LAYER_LUNARG_standard_validation" };

		#if(DEBUG)
		//using VKAPI standard validation layers
		const bool isValidationLayersEnable = true;
		#else
		const bool isValidationLayersEnable = false;
		#endif

	private:
		std::vector<const char*> m_VKRequiredExtensions;
		std::vector<VkExtensionProperties> VkSupportedExtensionsInfo;

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

#endif
