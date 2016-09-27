#include "../../defines.hpp"
#include "../../error.hpp"

#include "instance.hpp"
#include <glfw/glfw3.h>
#include <iostream>

namespace Aeon {

	namespace framework {

		namespace render {

			namespace device {

				instance::instance() {

					if (Aeon::framework::enableValidationLayers && !checkValidationLayerSupport()) {
						throw Aeon::framework::exception("validation layers requested, but not available!");
					}

					// Setup appinfo
					appInfo.sType = VK_STRUCTURE_TYPE_APPLICATION_INFO;
					appInfo.pApplicationName = "Hello Triangle";
					appInfo.applicationVersion = VK_MAKE_VERSION(1, 0, 0);
					appInfo.pEngineName = ENGINE_NAME;
					appInfo.engineVersion = VK_MAKE_VERSION(1, 0, 0);
					appInfo.apiVersion = VK_API_VERSION_1_0;

					//Setup create info
					createInfo.sType = VK_STRUCTURE_TYPE_INSTANCE_CREATE_INFO;
					createInfo.pApplicationInfo = &appInfo;

					auto extensions = getRequiredExtensions();
					createInfo.enabledExtensionCount = extensions.size();
					createInfo.ppEnabledExtensionNames = extensions.data();

					if (Aeon::framework::enableValidationLayers) {
						createInfo.enabledLayerCount = Aeon::framework::validationLayers.size();
						createInfo.ppEnabledLayerNames = Aeon::framework::validationLayers.data();
					}
					else {
						createInfo.enabledLayerCount = 0;
					}

					// Create VKInstance;
					if (vkCreateInstance(&createInfo, nullptr, &pdata) != VK_SUCCESS) {
						throw Aeon::framework::exception("failed to create instance!");
					}

					// Setup debug callback

					if (Aeon::framework::enableValidationLayers) {
						VkDebugReportCallbackCreateInfoEXT dbgcreateInfo = {};
						dbgcreateInfo.sType = VK_STRUCTURE_TYPE_DEBUG_REPORT_CALLBACK_CREATE_INFO_EXT;
						dbgcreateInfo.flags = VK_DEBUG_REPORT_ERROR_BIT_EXT | VK_DEBUG_REPORT_WARNING_BIT_EXT;
						dbgcreateInfo.pfnCallback = debugCallback;

						if (CreateDebugReportCallbackEXT(pdata, &dbgcreateInfo, nullptr, &callback) != VK_SUCCESS) {
							throw Aeon::framework::exception("failed to set up debug callback!");
						}
					}
				}

				instance::~instance() {
					DestroyDebugReportCallbackEXT(pdata, callback, nullptr);
					vkDestroyInstance(pdata, nullptr);
				};

				VkInstance instance::getInstance() {
					return pdata;
				}

				std::vector<VkExtensionProperties> instance::getExtensionSupport() {
					uint32_t extensionCount = 0;
					vkEnumerateInstanceExtensionProperties(nullptr, &extensionCount, nullptr);

					std::vector<VkExtensionProperties> extensions(extensionCount);
					vkEnumerateInstanceExtensionProperties(nullptr, &extensionCount, extensions.data());

					return extensions;
				}

				bool instance::checkValidationLayerSupport() {
					uint32_t layerCount;
					vkEnumerateInstanceLayerProperties(&layerCount, nullptr);

					std::vector<VkLayerProperties> availableLayers(layerCount);
					vkEnumerateInstanceLayerProperties(&layerCount, availableLayers.data());

					for (const char* layerName : Aeon::framework::validationLayers) {
						bool layerFound = false;

						for (const auto& layerProperties : availableLayers) {
							if (strcmp(layerName, layerProperties.layerName) == 0) {
								layerFound = true;
								break;
							}
						}

						if (!layerFound) {
							return false;
						}
					}

					return true;
				}

				std::vector<const char*> instance::getRequiredExtensions() {
					std::vector<const char*> extensions;

					unsigned int glfwExtensionCount = 0;
					const char** glfwExtensions;
					glfwExtensions = glfwGetRequiredInstanceExtensions(&glfwExtensionCount);

					for (unsigned int i = 0; i < glfwExtensionCount; i++) {
						extensions.push_back(glfwExtensions[i]);
					}

					if (Aeon::framework::enableValidationLayers) {
						extensions.push_back(VK_EXT_DEBUG_REPORT_EXTENSION_NAME);
					}

					return extensions;
				}

				VKAPI_ATTR VkBool32 VKAPI_CALL instance::debugCallback(
					VkDebugReportFlagsEXT flags,
					VkDebugReportObjectTypeEXT objType,
					uint64_t obj,
					size_t location,
					int32_t code,
					const char* layerPrefix,
					const char* msg,
					void* userData) {

					std::cerr << "validation layer: " << msg << std::endl;

					return VK_FALSE;
				}

				VkResult instance::CreateDebugReportCallbackEXT(VkInstance inst, const VkDebugReportCallbackCreateInfoEXT* pCreateInfo,
					const VkAllocationCallbacks* pAllocator, 
					VkDebugReportCallbackEXT* pCallback) 
				{
					auto func = (PFN_vkCreateDebugReportCallbackEXT)vkGetInstanceProcAddr(inst, "vkCreateDebugReportCallbackEXT");
					if (func != nullptr) {
						return func(inst, pCreateInfo, pAllocator, pCallback);
					}
					else {
						return VK_ERROR_EXTENSION_NOT_PRESENT;
					}
				}

				void instance::DestroyDebugReportCallbackEXT( VkInstance inst, VkDebugReportCallbackEXT callback, const VkAllocationCallbacks* pAllocator) {
					auto func = (PFN_vkDestroyDebugReportCallbackEXT)vkGetInstanceProcAddr(inst, "vkDestroyDebugReportCallbackEXT");
					if (func != nullptr) {
						func(inst, callback, pAllocator);
					}
				}

			}

		}

	}

}