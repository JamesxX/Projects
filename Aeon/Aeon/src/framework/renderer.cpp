#include "renderer.hpp"
#include "render/window.hpp"
#include "render/surface.hpp"
#include "render/swapChain.hpp"
#include "render/device/instance.hpp"
#include "render/device/physical.hpp"
#include "render/device/logical.hpp"
#include "render/pipeline/pipeline.hpp"

namespace Aeon {

	namespace framework {

		renderer::renderer(unsigned int sizeX, unsigned int sizeY, const char title[]) {
			
			Window = new render::window(sizeX, sizeY, title);
			Instance = new render::device::instance();
			PhysicalDevice = new render::device::physical(Instance);

			Surface = new render::surface(Instance, Window);

			LogicalDevice = new render::device::logical(PhysicalDevice, Surface);
			SwapChain = new render::swapChain(PhysicalDevice, LogicalDevice, Surface, sizeX, sizeY);

			Pipeline = new render::pipeline::genericPipeline(LogicalDevice, SwapChain);

		}

		renderer::~renderer() {
			delete Pipeline;

			delete SwapChain;
			delete LogicalDevice;

			delete Surface;

			delete PhysicalDevice;
			delete Instance;
			delete Window;
		}

	}
}