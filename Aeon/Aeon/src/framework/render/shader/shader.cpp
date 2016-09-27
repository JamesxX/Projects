#include "shaderHeader.hpp"
#include "../../error.hpp"
#include <fstream>

namespace Aeon {

	namespace framework {

		namespace render {

			namespace shader {

				std::vector<char> readFile(const std::string& filename) {
					std::ifstream file(filename, std::ios::ate | std::ios::binary);

					if (!file.is_open()) {
						throw std::runtime_error("failed to open file!");
					}

					size_t fileSize = (size_t)file.tellg();
					std::vector<char> buffer(fileSize);
					file.seekg(0);
					file.read(buffer.data(), fileSize);
					file.close();

					return buffer;
				}

				IShader::IShader(VkDevice* logicalDevice) {

					preloadShader(logicalDevice);

					this->logicalDevice = logicalDevice;
					//createGraphicsPipeline(logicalDevice);
				}

				IShader::~IShader() {
					vkDestroyShaderModule(*logicalDevice, descriptor.vertShaderModule, nullptr);
					vkDestroyShaderModule(*logicalDevice, descriptor.fragShaderModule, nullptr);
				}

				IShaderDescriptor IShader::getShaders() {
					return descriptor;
				}

				void IShader::preloadShader(VkDevice* logicalDevice) {
					// OVERRIDE
				}

				VkPipelineShaderStageCreateInfo* IShader::createGraphicsPipeline(VkDevice* logicalDevice) {
					createShaderModule(logicalDevice, vertShaderCode, &descriptor.vertShaderModule);
					createShaderModule(logicalDevice, fragShaderCode, &descriptor.fragShaderModule);
				
					VkPipelineShaderStageCreateInfo vertShaderStageInfo = *new VkPipelineShaderStageCreateInfo;
					vertShaderStageInfo.sType = VK_STRUCTURE_TYPE_PIPELINE_SHADER_STAGE_CREATE_INFO;
					vertShaderStageInfo.stage = VK_SHADER_STAGE_VERTEX_BIT;
					vertShaderStageInfo.module = descriptor.vertShaderModule;
					vertShaderStageInfo.pName = shaderName;
					vertShaderStageInfo.pNext = nullptr;
					vertShaderStageInfo.flags = 0;

					VkPipelineShaderStageCreateInfo fragShaderStageInfo = *new VkPipelineShaderStageCreateInfo;
					fragShaderStageInfo.sType = VK_STRUCTURE_TYPE_PIPELINE_SHADER_STAGE_CREATE_INFO;
					fragShaderStageInfo.stage = VK_SHADER_STAGE_FRAGMENT_BIT;
					fragShaderStageInfo.module = descriptor.fragShaderModule;
					fragShaderStageInfo.pName = shaderName;
					fragShaderStageInfo.pNext = nullptr;
					fragShaderStageInfo.flags = 0;

					VkPipelineShaderStageCreateInfo shaderStages[2] = { vertShaderStageInfo, fragShaderStageInfo };
					return shaderStages;
				}

				void IShader::createShaderModule(VkDevice* logicalDevice, 
					std::vector<char> shaderCode, 
					VkShaderModule* shaderModule) 
				{
					VkShaderModuleCreateInfo createInfo = {};
					createInfo.sType = VK_STRUCTURE_TYPE_SHADER_MODULE_CREATE_INFO;
					createInfo.codeSize = shaderCode.size();
					createInfo.pCode = (uint32_t*)shaderCode.data();

					if (vkCreateShaderModule(*logicalDevice, &createInfo, nullptr, shaderModule) != VK_SUCCESS) {
						throw Aeon::framework::exception("failed to create shader module!");
					}

				}


			}

		}

	}

}
