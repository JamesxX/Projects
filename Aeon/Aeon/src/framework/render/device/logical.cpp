#include "../../defines.hpp"
#include "../../error.hpp"
#include "logical.hpp"
#include "physical.hpp"
#include "queueFamilyIndices.hpp"

#include <set>

namespace Aeon {

	namespace framework {

		namespace render {

			namespace device {

				logical::logical(physical* physicalDevice, surface* surfaceInstance) {

					QueueFamilyIndices indices = physicalDevice->findQueueFamilies(surfaceInstance);

					std::vector<VkDeviceQueueCreateInfo> queueCreateInfos;
					std::set<int> uniqueQueueFamilies = { indices.graphicsFamily, indices.presentFamily };

					float queuePriority = 1.0f;
					for (int queueFamily : uniqueQueueFamilies) {
						VkDeviceQueueCreateInfo queueCreateInfo = {};
						queueCreateInfo.sType = VK_STRUCTURE_TYPE_DEVICE_QUEUE_CREATE_INFO;
						queueCreateInfo.queueFamilyIndex = queueFamily;
						queueCreateInfo.queueCount = 1;
						queueCreateInfo.pQueuePriorities = &queuePriority;
						queueCreateInfos.push_back(queueCreateInfo);
					}

					VkPhysicalDeviceFeatures deviceFeatures = {};

					VkDeviceCreateInfo createInfo = {};
					createInfo.sType = VK_STRUCTURE_TYPE_DEVICE_CREATE_INFO;
					createInfo.pQueueCreateInfos = queueCreateInfos.data();
					createInfo.queueCreateInfoCount = (uint32_t)queueCreateInfos.size();
					createInfo.pEnabledFeatures = &deviceFeatures;
					createInfo.enabledExtensionCount = Aeon::framework::deviceExtensions.size();
					createInfo.ppEnabledExtensionNames = Aeon::framework::deviceExtensions.data();

					createInfo.enabledLayerCount = 0;

					if (Aeon::framework::enableValidationLayers) {
						createInfo.enabledLayerCount = Aeon::framework::validationLayers.size();
						createInfo.ppEnabledLayerNames = Aeon::framework::validationLayers.data();
					}

					if (vkCreateDevice(physicalDevice->physicalDevice, &createInfo, nullptr, &logicalDevice) != VK_SUCCESS) {
						throw Aeon::framework::exception("failed to create logical device!");
					}

					vkGetDeviceQueue(logicalDevice, indices.graphicsFamily, 0, &graphicsQueue);
					vkGetDeviceQueue(logicalDevice, indices.presentFamily, 0, &presentQueue);
				}

				logical::~logical() {
					vkDestroyDevice(logicalDevice, nullptr);
				}


			}

		}

	}

}