#version 330 core

#define MAX_ITER 500
//layout(pixel_center_integer) in vec4 gl_FragCoord;
in vec4 gl_FragCoord;

out vec4 fragColor;
// in vec3 hybrid_color;

//uniform vec4 change_color;

int mandlebrot() {
	float real = (gl_FragCoord.x/800.0 - 0.55)*4.0;
	float imag = (gl_FragCoord.y/680.0 - 0.5)*4.0;
	float initial_real = real;
	float initial_imag = imag;
	
	int iteration = 0;
	
	float displacement = 0.0;	

	while (iteration < MAX_ITER)
    	{
        	float tmp_real = real;
        	real = (real * real - imag * imag) + initial_real;
        	imag = (2.0 * tmp_real * imag) + initial_imag;
         
        	float dist = real * real + imag * imag;
         
        	if (dist > 4.0)
        	break;
 
        	++iteration;
    }
    return iteration;
}

vec4 color_fractals(){
	int depth = mandlebrot();
	if (depth == MAX_ITER) {
		gl_FragDepth = 0.0f;
		return vec4(0.0f, 0.0f, 0.6f, 1.0f);
	}
	
	float depths = float(depth) / MAX_ITER;
	return vec4(0.0f, 0.0f, depths, 1.0f);
	
}




void main(){
	fragColor = color_fractals();
}

