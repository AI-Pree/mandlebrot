#include <iostream>
#include "headers/glad.h"
#include <GLFW/glfw3.h>
#include <string.h>
void init_glfw() {
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    	
#ifdef __APPLE__
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
#endif
}


//resizing the window frame size and updating it
void frame_buffer_size_callback(GLFWwindow* window, int width, int height){
	glViewport(0,0, width, height);
}

//checking the error generated for the glfw
void error_callback(int, const char* err){
	std::cout << "error: " << err << std::endl;
}

// processing input 
void processInput(GLFWwindow *window){
	if(glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS){
		glfwSetWindowShouldClose(window, true);
	}
}

void fps_counter(double& start, double& framerate,std::string& frame_per_sec){
	double current = glfwGetTime();
	if ((current - start) >= 1){
		frame_per_sec = std::to_string(framerate);
		framerate = 0;
		start = current;
	}
}
