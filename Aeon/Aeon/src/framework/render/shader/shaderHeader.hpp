#pragma once
#include <vulkan/vulkan.hpp>
#include <vector>

namespace Aeon {

	namespace framework {

		namespace render {

			namespace shader {

				std::vector<char> readFile(const std::string& filename);

				struct IShaderDescriptor {
					VkShaderModule vertShaderModule;
					VkShaderModule fragShaderModule;
				};

				class IShader {
				public:
					IShader(VkDevice* logicalDevice);
					~IShader();

					IShaderDescriptor getShaders();
					VkPipelineShaderStageCreateInfo* createGraphicsPipeline(VkDevice* logicalDevice);

				public:
					const char* shaderName;
					std::vector<char> vertShaderCode;
					std::vector<char> fragShaderCode;

				public:

					void preloadShader(VkDevice* logicalDevice);
					IShaderDescriptor descriptor;

					VkDevice* logicalDevice;

					void createShaderModule(VkDevice* logicalDevice, 
						std::vector<char> shaderCode, 
						VkShaderModule* shaderModule);
				};

			}

		}

	}

}
