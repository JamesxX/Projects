#pragma once
#include <vulkan/vulkan.hpp>
#include "../device/logical.hpp"
#include "../swapChain.hpp"
#include "../shader/testShader/testShader.hpp"

namespace Aeon {

	namespace framework {

		namespace render {

			namespace pipeline {

				class genericPipeline {
				public:
					genericPipeline(render::device::logical* logicalDevice, swapChain* swapChainInstance);
					~genericPipeline();

				private:
					VkPipelineLayout pipelineLayout;
					VkPipeline graphicsPipeline;
					VkRenderPass RenderPass;

					render::device::logical* logicalDevice;
				};

			}

		}

	}

}