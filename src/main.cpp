#include <iostream>
#include <glm/vec2.hpp>
#include <GLFW/glfw3.h>

int main()
{
	
	glm::vec2 vector2_test(5, 6);
	std::cout << "vector2_test x"<< vector2_test.x;

	if (!glfwInit())
	{
		// Initialization failed
		std::cout << "\nInitialization failed";
	}

	int monitors;
	glfwGetMonitors(&monitors);
	std::cout << "\nmonitors : " << monitors;

	glfwTerminate();
	return 0;
}