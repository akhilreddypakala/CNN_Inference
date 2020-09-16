#include <stdio.h>
#include <string.h>
#include <math.h>
#include "global_var.h"
#include "read_parameters.h"
#include "convolution.h"
#include <iostream>
using namespace std;



Base_datatype weights[OUTPUT_CHANNEL][INPUT_CHANNEL*KERNEL_WIDTH*KERNEL_HEIGHT];
Base_datatype bias[OUTPUT_CHANNEL]; 
Base_datatype pixel_ip[INPUT_CHANNEL][INPUT_WIDTH+2*PADDING][INPUT_HEIGHT + 2*PADDING];
Base_datatype feature_map[OUTPUT_CHANNEL][OUTPUT_WIDTH][OUTPUT_HEIGHT];

int main () {

	for (int i=0; i<OUTPUT_CHANNEL; i++){
		for (int k = 0; k<INPUT_HEIGHT+2*PADDING-KERNEL_HEIGHT+1; k= k+STRIDE){
			for (int q = 0; q<INPUT_WIDTH+2*PADDING-KERNEL_WIDTH+1; q= q+STRIDE){
				feature_map[i][k][q] = 0;
			}
		}
	}
	
	//Padding the pixel input
	for (int i =0; i<INPUT_CHANNEL; i++){
		for(int k =0; k<INPUT_WIDTH; k++){
			pixel_ip[i][0][k] = PADDING_NUMBER;
			pixel_ip[i][INPUT_HEIGHT+PADDING][k] = PADDING_NUMBER;
		}
	}

	for (int i =0; i<INPUT_CHANNEL; i++){
		for (int j =0; j<INPUT_HEIGHT; j++){
			pixel_ip[i][j][0] = PADDING_NUMBER;
			pixel_ip[i][j][INPUT_HEIGHT+PADDING] = PADDING_NUMBER;
		}
	}
	Read_Parameters(pixel_ip, weights, bias); // Read all the parameters

	cout << "pixel last input = " << bias[63] << endl;
    //Convolution of one layer. ReLU function included 
	convolution(pixel_ip, weights, bias, feature_map);	

	cout << feature_map[127][111][111] <<endl;

return 0;

}
