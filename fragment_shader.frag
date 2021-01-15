//reference: https://physicspython.wordpress.com/2020/02/16/visualizing-the-mandelbrot-set-using-opengl-part-1/

#version 330 core
#define MAX 200

in vec4 gl_fragvertex;

out vec4 FragColor;


int fractal_iteration() {
	float real = ((gl_fragvertex.x / 1080.0 - 0.5) * zoon + center_x) * 5.0;
	float imag = ((gl_fragvertex.y / 1080.0 - 0.5) * zoom + center_y) * 5.0;
	
	int iteration = 0;

	while (iteration < MAX){
		float temp_real = real;
		real = (real * real - imag * imag)  + const_real;
		imag = (2.0 * temp_real * imag) + const_imag;
		float dist = real * real + imag * imag;

		if (dist > 4.0)
		break;
		
		++iteration;
	}
	return iteration;
}

vec4 fractal_colors() {

	int iteration = fractal_iteration();
	if (iteration == MAX) {
		gl_FragDepth = 0.0f;
		return vec4(0.0f, 0.0f, 0.0f, 1.0f);
	}

	float iterations = float(iteration) / MAX;
	return vec4(0.0f, iteration, 0.0f, 1.0f);
}

void main() {
	FragColor = fractal_colors();
}
