#include "glad.h"
#include <GLFW/glfw3.h>
#include <string.h>
#include <iosfwd>

//initialising the glfw instance
void init_glfw(); 

//resizing the window frame size and updating it
void frame_buffer_size_callback(GLFWwindow* window, int width, int height);

//checking the error generated for the glfw
void error_callback(int, const char* err);

//for processing input
void processInput(GLFWwindow *window);

//getting the fps
void fps_counter(double& start, double& framrate, double& frame_per_sec);
