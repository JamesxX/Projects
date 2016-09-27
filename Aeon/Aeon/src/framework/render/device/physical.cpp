#include "../../defines.hpp"
#include "../../error.hpp"
#include <vulkan/vulkan.hpp>
#include "physical.hpp"
#include "instance.hpp"
#include "queueFamilyIndices.hpp"
#include "../surface.hpp"

#include <map>
#include <set>

namespace Aeon {

	namespace framework {

		namespace render {

			namespace device {

				SwapChainSupportDetails querySwapChainSupport(VkPhysicalDevice device, surface* surfaceInstance) {
					SwapChainSupportDetails details;

					vkGetPhysicalDeviceSurfaceCapabilitiesKHR(device, surfaceInstance->surfaceInstance, &details.capabilities);

					uint32_t formatCount;
					vkGetPhysicalDeviceSurfaceFormatsKHR(device, surfaceInstance->surfaceInstance, &formatCount, nullptr);

					if (formatCount != 0) {
						details.formats.resize(formatCount);
						vkGetPhysicalDeviceSurfaceFormatsKHR(device, surfaceInstance->surfaceInstance, &formatCount, details.formats.data());
					}

					uint32_t presentModeCount;
					vkGetPhysicalDeviceSurfacePresentModesKHR(device, surfaceInstance->surfaceInstance, &presentModeCount, nullptr);

					if (presentModeCount != 0) {
						details.presentModes.resize(presentModeCount);
						vkGetPhysicalDeviceSurfacePresentModesKHR(device, surfaceInstance->surfaceInstance, &presentModeCount, details.presentModes.data());
					}

					return details;
				}

				physical::physical(instance* vulkanInstance) {
					uint32_t deviceCount = 0;
					vkEnumeratePhysicalDevices(vulkanInstance->getInstance(), &deviceCount, nullptr);

					if (deviceCount == 0) {
						throw Aeon::framework::exception("failed to find GPUs with Vulkan support!");
					}

					std::vector<VkPhysicalDevice> devices(deviceCount);
					vkEnumeratePhysicalDevices(vulkanInstance->getInstance(), &deviceCount, devices.data());

					std::map<int, VkPhysicalDevice> candidates;

					for (const auto& device : devices) {
						int score = rateDeviceSuitability(device);
						candidates[score] = device;
					}

					// Check if the best candidate is suitable at all
					if (candidates.begin()->first > 0) {
						physicalDevice = candidates.begin()->second;
					}
					else {
						throw std::runtime_error("failed to find a suitable GPU!");
					}

				}

				bool physical::isDeviceSuitable(surface* surfaceInstance) {
					QueueFamilyIndices indices = findQueueFamilies(surfaceInstance);

					bool extensionsSupported = checkDeviceExtensionSupport();

					bool swapChainAdequate = false;
					if (extensionsSupported) {
						SwapChainSupportDetails swapChainSupport = querySwapChainSupport(physicalDevice, surfaceInstance);
						swapChainAdequate = !swapChainSupport.formats.empty() && !swapChainSupport.presentModes.empty();
					}

					return indices.isComplete() && extensionsSupported && swapChainAdequate;
				}

				bool physical::checkDeviceExtensionSupport() {
					uint32_t extensionCount;
					vkEnumerateDeviceExtensionProperties(physicalDevice, nullptr, &extensionCount, nullptr);

					std::vector<VkExtensionProperties> availableExtensions(extensionCount);
					vkEnumerateDeviceExtensionProperties(physicalDevice, nullptr, &extensionCount, availableExtensions.data());

					std::set<std::string> requiredExtensions(Aeon::framework::deviceExtensions.begin(), deviceExtensions.end());

					for (const auto& extension : availableExtensions) {
						requiredExtensions.erase(extension.extensionName);
					}

					return requiredExtensions.empty();
				}

				int physical::rateDeviceSuitability(VkPhysicalDevice device) {
					
					VkPhysicalDeviceProperties deviceProperties;
					VkPhysicalDeviceFeatures deviceFeatures;
					vkGetPhysicalDeviceProperties(device, &deviceProperties);
					vkGetPhysicalDeviceFeatures(device, &deviceFeatures);

					int score = 0;

					// Discrete GPUs have a significant performance advantage
					if (deviceProperties.deviceType == VK_PHYSICAL_DEVICE_TYPE_DISCRETE_GPU) {
						score += 1000;
					}

					// Maximum possible size of textures affects graphics quality
					score += deviceProperties.limits.maxImageDimension2D;

					// Application can't function without geometry shaders
					if (!deviceFeatures.geometryShader) {
						return 0;
					}

					return score;
				}

				QueueFamilyIndices physical::findQueueFamilies(surface* surfaceInstance) {

					QueueFamilyIndices indices;

					uint32_t queueFamilyCount = 0;
					vkGetPhysicalDeviceQueueFamilyProperties(physicalDevice, &queueFamilyCount, nullptr);

					std::vector<VkQueueFamilyProperties> queueFamilies(queueFamilyCount);
					vkGetPhysicalDeviceQueueFamilyProperties(physicalDevice, &queueFamilyCount, queueFamilies.data());

					int i = 0;
					for (const auto& queueFamily : queueFamilies) {
						if (queueFamily.queueCount > 0 && queueFamily.queueFlags & VK_QUEUE_GRAPHICS_BIT) {
							indices.graphicsFamily = i;
						}

						VkBool32 presentSupport = false;
						vkGetPhysicalDeviceSurfaceSupportKHR(physicalDevice, i, surfaceInstance->surfaceInstance, &presentSupport);

						if (queueFamily.queueCount > 0 && presentSupport) {
							indices.presentFamily = i;
						}

						if (indices.isComplete()) {
							break;
						}

						i++;
					}

					return indices;
				}

			}

		}

	}

}