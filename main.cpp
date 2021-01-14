#include <iostream>
#include "headers/glad.h"
#include <GLFW/glfw3.h>
#include "headers/context.h"

//enable nvidia graphics
#ifdef __cpluscplus
extern "C" (
	_declspec(dllexport) DWORD NvOptimusEnablement = 0x00000001;
)
#endif

int main(int argc, char ** argv) {
	double frametate = 0.0;

	//initialisng the glfw
	init_glfw();
	
	// creating a window object	
	GLFWwindow* window = glfwCreateWindow(800, 600, "Mandlebrot", NULL, NULL);
	
	if (window == NULL) {
		std::cout <<  "failed to create a window" << std::endl;
		glfwTerminate();
		return -1;
	}

	glfwMakeContextCurrent(window);	
	
	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		std::cout << "Failed to initialize GLAD" << std::endl;
		return -1;
	}
	
	double previous_time = glfwGetTime();
	double  frame_per_sec = 0.0;
	std::cout << "Name of the renderer: " << glGetString(GL_VENDOR) << std::endl;

	// all of my rendering activites goes here
	while(!glfwWindowShouldClose(window)){
		// checking the fps
		fps_counter(previous_time, frametate, frame_per_sec);
		
		// counting frames per sec
		frametate++;
//		std::cout << "FPS: " << frame_per_sec << std::endl;
		
		//registering error callback
		glfwSetErrorCallback(error_callback);
		
		//processing input
		processInput(window);
			
		// rendering
		glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);

		// check and call events and swap the buffer
		glfwSwapBuffers(window);
		glfwPollEvents();
	}

 

	//resizing the window size
	glfwSetFramebufferSizeCallback(window, frame_buffer_size_callback);
	//glViewport(0, 0, 800, 600);

	glfwTerminate();
	return 0;
}
