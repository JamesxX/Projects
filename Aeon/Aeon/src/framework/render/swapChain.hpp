#pragma once
#include <vector>
#include <vulkan/vulkan.hpp>
#include "device/physical.hpp"
#include "device/logical.hpp"

namespace Aeon {

	namespace framework {

		namespace render {

			class swapChain {

			public:
				swapChain(device::physical* physicalDevice,
					device::logical* logicalDevice,
					surface* surfaceInstance,
					unsigned int sizeX,
					unsigned int sizeY);
				~swapChain();

				VkSurfaceFormatKHR chooseSwapSurfaceFormat(const std::vector<VkSurfaceFormatKHR>& availableFormats);
				VkPresentModeKHR chooseSwapPresentMode(const std::vector<VkPresentModeKHR> availablePresentModes);
				VkExtent2D chooseSwapExtent(const VkSurfaceCapabilitiesKHR& capabilities);

				void populateSwapChainImageViews();

				unsigned int width;
				unsigned int height;

				VkSwapchainKHR swapChainInstance;
				device::logical* logicalDeviceptr;

				std::vector<VkImage> swapChainImages;
				VkFormat swapChainImageFormat;
				VkExtent2D swapChainExtent;

				std::vector<VkImageView> swapChainImageViews;
			};

		}

	}
}