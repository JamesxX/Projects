#include "../defines.hpp"
#include <GLFW/glfw3.h>

#include "window.hpp"
#include <string>

namespace Aeon {

	namespace framework {

		namespace render {

			window::window(unsigned int sizeX, unsigned int sizeY, const char title[]) {
				glfwInit();
				glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API);
				glfwWindowHint(GLFW_RESIZABLE, GLFW_FALSE);
				this->instance = glfwCreateWindow(sizeX, sizeY, title, nullptr, nullptr);

				this->sizeX = sizeX;
				this->sizeY = sizeY;
			}

			window::window(unsigned int sizeX, unsigned int sizeY, std::string title) :
				window( sizeX, sizeY, title.c_str() ) {
				
			}

			window::~window() {
				glfwDestroyWindow(getInstance());
				glfwTerminate();
			}

			window::windowType* window::getInstance() {
				return this->instance;
			}

		};

	};

};
