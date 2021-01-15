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

//adding vertex shader code source

const char *vertexShaderSource = "#version 330 core\n"
	"layout (location = 0) in vec3 aPos;\n"
	"void main()\n"
	"{\n"
	"	gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);\n"
	"}\0";

const char *fragmentShaderSource = "#version 330 core\n"
	"out vec4 FragColor;\n"
	"void main() {\n"
	"	FragColor = vec4(1.0f, 0.5f, 0.2f, 1.0f);\n"
	"}\0";

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

//forming a trianlge from the vertex data

float vertices[] = 
{
//	x	y	z	
	 0.5f, 	  0.5f,	 0.0f,
	-0.5f, 	 -0.5f,  0.0f,
	 0.5f, 	 -0.5f,  0.0f,
	
	 // second triangle

	-0.5f,	  0.5f,	 0.0f,
	-0.5f,	 -0.5f,  0.0f,
	 0.5f,	 -0.5f,  0.0f
};

unsigned int indices[] = 
{
	0, 1, 2,
	1, 3, 0
};

int main(int argc, char ** argv) {
	double frametate = 0.0;	
	
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
	
	//creating the vertex array object
	unsigned int VAO;
	glGenVertexArrays(1, &VAO);
	
	//bind the vertex array
	glBindVertexArray(VAO);
	
	//creating a element object buffer
	unsigned int EBO;
       	glGenBuffers(1, &EBO);

	//bind the buffer for the elemen object buffer
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

	//creating a vertex buffer
	unsigned int VBO;
	glGenBuffers(1, &VBO);
	
	//target for binding the buffer
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	//creating a vertex shader
	unsigned int vertexShader = glCreateShader(GL_VERTEX_SHADER);
	
	// check if the vertex shaader was created	
	if (!vertexShader){
		std::cout << "vector shader wasnt created" << std::endl;
	}
		
	glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);
	glCompileShader(vertexShader);

	// check if the shader compiled successfully
	int success;
	char infolog[512];
	
	glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);
	
	if(!success) {
		glGetShaderInfoLog(vertexShader, 512, NULL, infolog);
		std::cout << "Vertex shader didnt compiled successfully.\n" << infolog << std::endl;	
	}

	//creating a fragment shader
	unsigned int fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
	
	//check if the fragment shader was created succesfully
	if (!fragmentShader){
		std::cout << "Fragment shader wasnt created" << std::endl;
	}

	glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL);
	glCompileShader(fragmentShader);

	//checking if the fragment shader compiled successully
	glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &success);
	
	if (!success)
	{
		glGetShaderInfoLog(fragmentShader, 512, NULL, infolog);
		std::cout << "Fragment shader didnt compile succesfully\n" << infolog << std::endl;
	}
		
	// creating the shader program that links all the shaders in the pipeline
	unsigned int shaderProgram = glCreateProgram();

	// attaching shaders to the shader program
	glAttachShader(shaderProgram, vertexShader);
	glAttachShader(shaderProgram, fragmentShader);
	glLinkProgram(shaderProgram);
		
	// check if the shaders were linked properly in the shaderprogram
	glGetProgramiv(shaderProgram, GL_LINK_STATUS, &success);

	if(!success){
		glGetProgramInfoLog(shaderProgram, 512, NULL, infolog);
		std::cout << "Error while linking the shader in the shader program\n" << infolog << std::endl;
	}	

	//linking vertex attribute the shaderprogram
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*) 0);
	glEnableVertexAttribArray(0);	
	
	//configuring the VBO and VAO
	glBindBuffer(GL_ARRAY_BUFFER, 0);

	glBindVertexArray(0);

	double previous_time = glfwGetTime();
	double  frame_per_sec = 0.0;
	std::cout << "Name of the renderer: " << glGetString(GL_VENDOR) << std::endl;


	//drawing in the polygon mode
	//glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

	while(!glfwWindowShouldClose(window)){
		// checking the fps
		fps_counter(previous_time, frametate, frame_per_sec);
		
		// counting frames per sec
		frametate++;
	//	std::cout << "FPS: " << frame_per_sec << std::endl;
		
		//registering error callback
		glfwSetErrorCallback(error_callback);
		
		//processing input
		processInput(window);
			
		// rendering
		glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);
	
		//drawing the object
		glUseProgram(shaderProgram);
		glBindVertexArray(VAO); // needed only when there is multiple VAO 
		
		//draw the triangle from the VAO
		glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);		
		glBindVertexArray(0);

		// check and call events and swap the buffer
		glfwSwapBuffers(window);
		glfwPollEvents();
	}
 
	//resizing the window size
	glfwSetFramebufferSizeCallback(window, frame_buffer_size_callback);
	//glViewport(0, 0, 800, 600);
	
	//deleting the shader objects are linking it to the program
	glDeleteShader(vertexShader);
	glDeleteShader(fragmentShader);
		
	//clearing everything
	glDeleteVertexArrays(1, &VAO);
	glDeleteBuffers(1, &VBO);
	glDeleteBuffers(1, &EBO);
	glDeleteProgram(shaderProgram);

	glfwTerminate();
	return 0;
}
