#pragma once
#include <vulkan/vulkan.hpp>
#include "physical.hpp"

namespace Aeon {

	namespace framework {

		namespace render {

			namespace device {

				class logical {
				public:
					logical(physical* physicalDevice, surface* surfaceInstance);
					~logical();



				public:
					VkDevice logicalDevice;

					VkQueue graphicsQueue;
					VkQueue presentQueue;
				};


			}

		}

	}

}