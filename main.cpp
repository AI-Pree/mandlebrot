#include <iostream>
#include "headers/glad.h"
#include <GLFW/glfw3.h>
#include "headers/context.h"

int main() {
	//initialisng the glfw
	init_glfw();
	
	//registering error callback
	glfwSetErrorCallback(error_callback);

	// creating a window object	
	GLFWwindow* window = glfwCreateWindow(800, 600, "Mandlebrot", NULL, NULL);
	
	if (window == NULL) {
		std::cout <<  "failed to create a window" << std::endl;
		glfwTerminate();
		return -1;
	}
	
	glfwMakeContextCurrent(window);	
	
	while(!glfwWindowShouldClose(window)){
		glfwSwapBuffers(window);
		glfwPollEvents();
	}


	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
    		std::cout << "Failed to initialize GLAD" << std::endl;
		return -1;
	} 

	glfwSetFramebufferSizeCallback(window, frame_buffer_size_callback);
	//glViewport(0, 0, 800, 600);

	glfwTerminate();
	return 0;

}
