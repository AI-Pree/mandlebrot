#version 330 core
layout (location = 0) in vec3 aPos;   // the postion variable has the attribute of 0
// layout (location = 1) in vec3 aColor; // the color variables has the attribute of 1

// out vec3 hybrid_color; // output the color of the fragment shader

void main() {
	gl_Position = vec4(aPos.xyz, 1.0);
//	hybrid_color = aColor; //set the hybrid color to the input color that we got from the vertex data
}
