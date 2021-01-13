#include <iostream>
#include "headers/glad.h"
#include <GLFW/glfw3.h>

void init_glfw() {
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    	//glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
}

//resizing the window frame size and updating it
void frame_buffer_size_callback(GLFWwindow* window, int width, int height){
	glViewport(0,0, width, height);
}

//checking the error generated for the glfw
void error_callback(int, const char* err){
	std::cout << "error: " << err << std::endl;
}

