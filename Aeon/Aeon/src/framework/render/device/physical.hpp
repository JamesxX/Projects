#pragma once
#include <vulkan/vulkan.hpp>
#include "queueFamilyIndices.hpp"
#include "instance.hpp"
#include "../surface.hpp"
#include <memory>
#include <vector>

namespace Aeon {

	namespace framework {

		namespace render {

			struct SwapChainSupportDetails {
				VkSurfaceCapabilitiesKHR capabilities;
				std::vector<VkSurfaceFormatKHR> formats;
				std::vector<VkPresentModeKHR> presentModes;
			};

			namespace device {

				SwapChainSupportDetails querySwapChainSupport(VkPhysicalDevice device, surface* surfaceInstance);

				class physical {
				public:

					physical(instance* vulkanInstance);
					//~physical();

					bool isDeviceSuitable(surface* surfaceInstance);
					bool checkDeviceExtensionSupport();

					int rateDeviceSuitability(VkPhysicalDevice device);
					QueueFamilyIndices findQueueFamilies(surface* surfaceInstance);

					VkPhysicalDevice physicalDevice = VK_NULL_HANDLE;

				};


			}

		}

	}

}