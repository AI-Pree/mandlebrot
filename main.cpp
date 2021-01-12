#include <iostream>
#include <vector>


typedef std::vector<float> vf;


constexpr int total_recursion = 1000000; 


int recursion_index = 0;

float eq_mandlebrot = 0;


// n is the index of recurison
void mandlebrot_function(int n) {
	
	recursion_index ++;
	
	if (recursion_index < total_recursion){
		return;
	}

	mandlebrot_function(recursion_index);
}



int main(void){

	mandlebrot_function(recursion_index);

	return 0;
}
