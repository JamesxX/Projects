#pragma once

#include "render/window.hpp"
#include "render/surface.hpp"
#include "render/swapChain.hpp"
#include "render/device/instance.hpp"
#include "render/device/physical.hpp"
#include "render/device/logical.hpp"
#include "render/pipeline/pipeline.hpp"

namespace Aeon {

	namespace framework {

		class renderer {

		public:

			renderer(unsigned int sizeX, unsigned int sizeY, const char title[]);
			~renderer();

		public:
			render::device::instance* Instance;
			render::device::physical* PhysicalDevice;
			render::device::logical* LogicalDevice;

			render::window* Window;
			render::surface* Surface;
			render::swapChain* SwapChain;
			render::pipeline::genericPipeline* Pipeline;
		};
	}
}