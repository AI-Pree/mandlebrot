#include <iostream>
#include "headers/glad.h"
#include <GLFW/glfw3.h>
#include "headers/context.h"

/*
float vertices[] = 
{	
//	  x	  y	  z
	-1.0f,	-1.0f,	-0.0f,
       	 1.0f,	 1.0f,  -0.0f,
 	-1.0f, 	 1.0f,  -0.0f,
	 1.0f,	-1.0f,	-0.0f	
};
*/
unsigned int indices[] = 
{
	0, 1, 2,
	0, 3, 1
	
};

//forming a trianlge from the vertex data

float triangle_vertices[] = {
//	x	y	z
	
	 0.0f, 	  0.5f,	 0.0f,
	-0.5f, 	 -0.5f,  0.0f,
	 0.5f, 	 -0.5f,  0.0f
};



int main(int argc, char ** argv) {
	double frametate = 0.0;
	
	//creating a vertex buffer
	unsigned int VBO;
	glGenBuffers(1, &VBO);
	
	//target for binding the buffer
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(triangle_vertices), triangle_vertices, GL_STATIC_DRAW);
	
	
	
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
	std::string frame_per_sec = "0";

	// all of my rendering activites goes here
	while(!glfwWindowShouldClose(window)){
		// checking the fps
		fps_counter(previous_time, frametate, frame_per_sec);
		
		// counting frames per sec
		frametate++;
		std::cout << "FPS: " << frame_per_sec << std::endl;
		
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
