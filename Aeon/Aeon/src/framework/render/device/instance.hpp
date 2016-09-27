#pragma once
#include <vulkan/vulkan.hpp>

namespace Aeon {

	namespace framework {

		namespace render {

			namespace device {

				class instance {

				public:
					instance();
					~instance();

					VkInstance getInstance();
					std::vector<VkExtensionProperties> getExtensionSupport();
					bool checkValidationLayerSupport();
					std::vector<const char*> instance::getRequiredExtensions();

					static VKAPI_ATTR VkBool32 VKAPI_CALL debugCallback(
						VkDebugReportFlagsEXT flags,
						VkDebugReportObjectTypeEXT objType,
						uint64_t obj,
						size_t location,
						int32_t code,
						const char* layerPrefix,
						const char* msg,
						void* userData);

				private:

					VkApplicationInfo appInfo = {};
					VkInstanceCreateInfo createInfo = {};
					VkInstance pdata;

					VkDebugReportCallbackEXT callback;

					VkResult CreateDebugReportCallbackEXT(
						VkInstance inst,
						const VkDebugReportCallbackCreateInfoEXT* pCreateInfo, 
						const VkAllocationCallbacks* pAllocator, 
						VkDebugReportCallbackEXT* pCallback);

					void DestroyDebugReportCallbackEXT(
						VkInstance inst,
						VkDebugReportCallbackEXT callback, 
						const VkAllocationCallbacks* pAllocator);
				};


			}

		}

	}

}