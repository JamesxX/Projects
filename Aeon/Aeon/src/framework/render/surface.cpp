#include "../defines.hpp"
#include "../error.hpp"
#include "surface.hpp"
#include "window.hpp"
#include "device/instance.hpp"
#include <GLFW\glfw3.h>

namespace Aeon {

	namespace framework {

		namespace render {

			surface::surface(device::instance* vkinstance, window* windowinstance) {

				vkinstanceptr = vkinstance;

				VkResult WindSurfResult = glfwCreateWindowSurface(vkinstance->getInstance(), windowinstance->getInstance(), nullptr, &surfaceInstance);

				if (WindSurfResult != VK_SUCCESS) {
					throw Aeon::framework::exception("failed to create window surface!");
				}
			}

			surface::~surface() {
				vkDestroySurfaceKHR(vkinstanceptr->getInstance(), surfaceInstance, nullptr);
			}

		}

	}

}