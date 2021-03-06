#include <stdio.h>
#include <string.h>
#include <math.h>
#include "global_var.h"
#include "read_parameters.h"
#include "convolution.h"
#include <iostream>
#include <fstream>

using namespace std;
//Global definitions of variables 
Base_datatype weights[OUTPUT_CHANNEL][INPUT_CHANNEL][KERNEL_WIDTH*KERNEL_HEIGHT];
Base_datatype bias[OUTPUT_CHANNEL]; 
Base_datatype pixel_ip[INPUT_CHANNEL][INPUT_WIDTH+2*PADDING][INPUT_HEIGHT + 2*PADDING]; //input pixel
Base_datatype feature_map[OUTPUT_CHANNEL][OUTPUT_WIDTH][OUTPUT_HEIGHT];//output feature map

int main () {
	//Initialising feature_map to zero
	for (int i=0; i<OUTPUT_CHANNEL; i++){
		for (int k = 0; k<OUTPUT_HEIGHT; k++){
			for (int q = 0; q<OUTPUT_WIDTH; q++){
				feature_map[i][k][q] = 0;
			}
		}
	}
	
	//Padding the pixel input with zero. Row padding
	for (int i =0; i<INPUT_CHANNEL; i++){
		for(int k =0; k<INPUT_WIDTH; k++){
			pixel_ip[i][0][k] = PADDING_NUMBER;
			pixel_ip[i][INPUT_HEIGHT+PADDING][k] = PADDING_NUMBER;
		}
	}
	//Coloumn padding
	for (int i =0; i<INPUT_CHANNEL; i++){
		for (int j =0; j<INPUT_HEIGHT; j++){
			pixel_ip[i][j][0] = PADDING_NUMBER;
			pixel_ip[i][j][INPUT_HEIGHT+PADDING] = PADDING_NUMBER;
		}
	}
	Read_Parameters(pixel_ip, weights, bias); // Read all the parameters from input and weight files 

    //Convolution of one layer. ReLU function included 
	convolution(pixel_ip, weights, bias, feature_map);	

	#ifdef __DUMP_OUTPUT__
	//Dump output to generated_output.dat file
	ofstream fout;
	fout.open("../data/generated_output.dat");
	for (int i=0; i<OUTPUT_CHANNEL;i++){
		for (int k =0; k<OUTPUT_HEIGHT;k++){
			for (int q =0;q<OUTPUT_WIDTH;q++){
				fout << feature_map[i][k][q] <<endl;		
			}
		}
	}
	#endif
	return 0;
}
