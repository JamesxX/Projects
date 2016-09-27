#pragma once

#define GLFW_INCLUDE_VULKAN
#include <GLFW/glfw3.h>

#include <string>

namespace Aeon {

	namespace framework {

		namespace render {

			class window {

			public:

				typedef GLFWwindow windowType;

				window(unsigned int sizeX, unsigned int sizeY, const char title[]);
				window(unsigned int sizeX, unsigned int sizeY, std::string title);
				~window();

				windowType* getInstance();

			private:

				windowType* instance = nullptr;
				unsigned int sizeX = 0;
				unsigned int sizeY = 0;

			};


		};

	};

};
