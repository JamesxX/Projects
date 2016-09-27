#pragma once
#include <vulkan/vulkan.hpp>
#include "window.hpp"
#include "device/instance.hpp"

namespace Aeon {

	namespace framework {

		namespace render {

			class surface {
			public:
				surface(device::instance* vkinstance, window* windowinstance);
				~surface();

				VkSurfaceKHR surfaceInstance;
				device::instance* vkinstanceptr;
			};

		}

	}

}