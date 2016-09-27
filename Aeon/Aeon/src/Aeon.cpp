#include "framework/defines.hpp"
#include <GLFW/glfw3.h>

#include <glm/vec4.hpp>
#include <glm/mat4x4.hpp>

#include <iostream>

#include "framework/renderer.hpp"



int main() {

	try {

		Aeon::framework::renderer renderer(800, 600, "Hello World");

		while (!glfwWindowShouldClose(renderer.Window->getInstance())) {
			glfwPollEvents();
		}

	}
	catch (std::exception &err) {
		std::cout << err.what() << std::endl;

		{ char i; std::cin >> i; }
	}
	
	return 0;
}