#include "read_parameters.h"
#include <fstream>
#include <iostream>
#include <sstream>
#include "global_var.h"
using namespace std;

void Read_Parameters(Base_datatype pixel_ip[INPUT_CHANNEL][INPUT_WIDTH+2*PADDING][INPUT_HEIGHT+2*PADDING], Base_datatype weights[OUTPUT_CHANNEL] [INPUT_CHANNEL * KERNEL_WIDTH * KERNEL_HEIGHT], Base_datatype bias[OUTPUT_CHANNEL])
{
   // Read inputs from input.dat file
	float test_input;
 	ifstream f_inp;
	f_inp.open("/home/akhil/rice/EMBD_ML/CNN_Inference/data/input.dat");

 	for (int i=0; i< INPUT_CHANNEL; i++){

		for (int j=0; j< INPUT_HEIGHT; j++){
			for (int k=0; k< INPUT_WIDTH; k++){
				f_inp >> test_input >> ws;
				pixel_ip[i][j+1][k+1] = test_input;
				//cout << "pixel_ip=" << pixel_ip[i][j+1][k+1] << endl;
			}
		}
	}  
 	f_inp.close();
 	//cout << "pixel_ip = " << pixel_ip[1][1][1] <<endl;

  // Read weights from weight.dat file
	float test_weight;
 	ifstream f_wei;
	f_wei.open("/home/akhil/rice/EMBD_ML/CNN_Inference/data/weight.dat");
 	for (int i=0; i<OUTPUT_CHANNEL; i++){
		for (int k =0; k<INPUT_CHANNEL; k++){
			for (int j=0; j<KERNEL_WIDTH*KERNEL_HEIGHT; j++){
					f_wei >> test_weight >> ws;
					weights[i][k*(KERNEL_WIDTH*KERNEL_HEIGHT) + j] = test_weight;
			}
		}
	} 
// Read bias from weight file	
	for (int i=0; i< OUTPUT_CHANNEL; i++){
		f_wei >> test_weight >>ws;
		bias[i] = test_weight;
	} 
 	f_wei.close();
 	//cout << "weight = " << bias[63] <<endl;
} 
