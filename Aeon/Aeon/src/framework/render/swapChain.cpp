#include "../error.hpp"
#include "swapChain.hpp"
#include "device/physical.hpp"
#include "device/logical.hpp"
#include "device/queueFamilyIndices.hpp"
#include <vector>
#include <vulkan/vulkan.hpp>

namespace Aeon {

	namespace framework {

		namespace render {

			swapChain::swapChain(device::physical* physicalDevice,
				device::logical* logicalDevice,
				surface* surfaceInstance,
				unsigned int sizeX,
				unsigned int sizeY)
			{
				
				width = sizeX;
				height = sizeY;

				SwapChainSupportDetails swapChainSupport = device::querySwapChainSupport(physicalDevice->physicalDevice, surfaceInstance);

				VkSurfaceFormatKHR surfaceFormat = chooseSwapSurfaceFormat(swapChainSupport.formats);
				VkPresentModeKHR presentMode = chooseSwapPresentMode(swapChainSupport.presentModes);
				VkExtent2D extent = chooseSwapExtent(swapChainSupport.capabilities);
			
				uint32_t imageCount = swapChainSupport.capabilities.minImageCount + 1;
				if (swapChainSupport.capabilities.maxImageCount > 0 && imageCount > swapChainSupport.capabilities.maxImageCount) {
					imageCount = swapChainSupport.capabilities.maxImageCount;
				}

				VkSwapchainCreateInfoKHR createInfo = {};
				createInfo.sType = VK_STRUCTURE_TYPE_SWAPCHAIN_CREATE_INFO_KHR;
				createInfo.surface = surfaceInstance->surfaceInstance;
				createInfo.minImageCount = imageCount;
				createInfo.imageFormat = surfaceFormat.format;
				createInfo.imageColorSpace = surfaceFormat.colorSpace;
				createInfo.imageExtent = extent;
				createInfo.imageArrayLayers = 1;
				createInfo.imageUsage = VK_IMAGE_USAGE_COLOR_ATTACHMENT_BIT;

				device::QueueFamilyIndices indices = physicalDevice->findQueueFamilies(surfaceInstance);
				uint32_t queueFamilyIndices[] = { (uint32_t)indices.graphicsFamily, (uint32_t)indices.presentFamily };

				if (indices.graphicsFamily != indices.presentFamily) {
					createInfo.imageSharingMode = VK_SHARING_MODE_CONCURRENT;
					createInfo.queueFamilyIndexCount = 2;
					createInfo.pQueueFamilyIndices = queueFamilyIndices;
				}
				else {
					createInfo.imageSharingMode = VK_SHARING_MODE_EXCLUSIVE;
					createInfo.queueFamilyIndexCount = 0; // Optional
					createInfo.pQueueFamilyIndices = nullptr; // Optional
				}
			
				createInfo.preTransform = swapChainSupport.capabilities.currentTransform;
				createInfo.compositeAlpha = VK_COMPOSITE_ALPHA_OPAQUE_BIT_KHR;
				createInfo.presentMode = presentMode;
				createInfo.clipped = VK_TRUE;
				createInfo.oldSwapchain = VK_NULL_HANDLE;

				if (vkCreateSwapchainKHR(logicalDevice->logicalDevice, &createInfo, nullptr, &swapChainInstance) != VK_SUCCESS) {
					throw std::runtime_error("failed to create swap chain!");
				}

				logicalDeviceptr = logicalDevice;

				swapChainImageFormat = surfaceFormat.format;
				swapChainExtent = extent;

				vkGetSwapchainImagesKHR(logicalDevice->logicalDevice, swapChainInstance, &imageCount, nullptr);
				swapChainImages.resize(imageCount);
				vkGetSwapchainImagesKHR(logicalDevice->logicalDevice, swapChainInstance, &imageCount, swapChainImages.data());

				populateSwapChainImageViews();

			}

			swapChain::~swapChain(){

				for (uint32_t i = 0; i < swapChainImageViews.size(); i++) {
					vkDestroyImageView(logicalDeviceptr->logicalDevice, swapChainImageViews[i], nullptr);
				}

				vkDestroySwapchainKHR(logicalDeviceptr->logicalDevice, swapChainInstance, nullptr);
			}

			VkSurfaceFormatKHR swapChain::chooseSwapSurfaceFormat(const std::vector<VkSurfaceFormatKHR>& availableFormats) {
				if (availableFormats.size() == 1 && availableFormats[0].format == VK_FORMAT_UNDEFINED) {
					return{ VK_FORMAT_B8G8R8A8_UNORM, VK_COLOR_SPACE_SRGB_NONLINEAR_KHR };
				}

				for (const auto& availableFormat : availableFormats) {
					if (availableFormat.format == VK_FORMAT_B8G8R8A8_UNORM && availableFormat.colorSpace == VK_COLOR_SPACE_SRGB_NONLINEAR_KHR) {
						return availableFormat;
					}
				}

				return availableFormats[0];
			}


			VkPresentModeKHR swapChain::chooseSwapPresentMode(const std::vector<VkPresentModeKHR> availablePresentModes) {
				for (const auto& availablePresentMode : availablePresentModes) {
					if (availablePresentMode == VK_PRESENT_MODE_MAILBOX_KHR) {
						return availablePresentMode;
					}
				}

				return VK_PRESENT_MODE_FIFO_KHR;
			}

			VkExtent2D swapChain::chooseSwapExtent(const VkSurfaceCapabilitiesKHR& capabilities) {
				if (capabilities.currentExtent.width != std::numeric_limits<uint32_t>::max()) {
					return capabilities.currentExtent;
				}
				else {
					VkExtent2D actualExtent = { width, height };

					actualExtent.width = std::max(capabilities.minImageExtent.width, std::min(capabilities.maxImageExtent.width, actualExtent.width));
					actualExtent.height = std::max(capabilities.minImageExtent.height, std::min(capabilities.maxImageExtent.height, actualExtent.height));

					return actualExtent;
				}
			}

			void swapChain::populateSwapChainImageViews() {
				swapChainImageViews.resize(swapChainImages.size());

				for (uint32_t i = 0; i < swapChainImages.size(); i++) {

					VkImageViewCreateInfo createInfo = {};
					createInfo.sType = VK_STRUCTURE_TYPE_IMAGE_VIEW_CREATE_INFO;
					createInfo.image = swapChainImages[i];
					createInfo.viewType = VK_IMAGE_VIEW_TYPE_2D;
					createInfo.format = swapChainImageFormat;
					createInfo.components.r = VK_COMPONENT_SWIZZLE_IDENTITY;
					createInfo.components.g = VK_COMPONENT_SWIZZLE_IDENTITY;
					createInfo.components.b = VK_COMPONENT_SWIZZLE_IDENTITY;
					createInfo.components.a = VK_COMPONENT_SWIZZLE_IDENTITY;
					createInfo.subresourceRange.aspectMask = VK_IMAGE_ASPECT_COLOR_BIT;
					createInfo.subresourceRange.baseMipLevel = 0;
					createInfo.subresourceRange.levelCount = 1;
					createInfo.subresourceRange.baseArrayLayer = 0;
					createInfo.subresourceRange.layerCount = 1;

					if (vkCreateImageView(logicalDeviceptr->logicalDevice, &createInfo, nullptr, &swapChainImageViews[i]) != VK_SUCCESS) {
						throw Aeon::framework::exception("failed to create image views!");
					}
				}
			}
		}

	}
}