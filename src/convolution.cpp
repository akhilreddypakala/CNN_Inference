#include "convolution.h"
#include <fstream>
#include <iostream>
#include "global_var.h"

using namespace std;

void convolution(Base_datatype pixel_ip_after_padding[INPUT_CHANNEL][INPUT_WIDTH + 2*PADDING] [INPUT_HEIGHT+2*PADDING], Base_datatype weights[OUTPUT_CHANNEL][INPUT_CHANNEL][KERNEL_WIDTH*KERNEL_HEIGHT], Base_datatype bias[OUTPUT_CHANNEL], Base_datatype feature_map[OUTPUT_CHANNEL][OUTPUT_WIDTH][OUTPUT_HEIGHT] ){


	for (int i=0;i<OUTPUT_CHANNEL; i++){
		for (int j=0; j<INPUT_CHANNEL; j++){
			one_layer_convolution(pixel_ip_after_padding, weights, feature_map, i, j);
		}
		for (int k =0; k< OUTPUT_HEIGHT;k++){
			for (int q =0;q<OUTPUT_WIDTH;q++){
				feature_map[i][k][q] += bias[i];
				if (feature_map[i][k][q] < 0)
					feature_map[i][k][q] =0;
			}
		} 
	} //OUPUT_CHANNEL
}


void one_layer_convolution (Base_datatype pixel_ip_after_padding[INPUT_CHANNEL][INPUT_WIDTH + 2*PADDING] [INPUT_HEIGHT+2*PADDING], Base_datatype weights[OUTPUT_CHANNEL][INPUT_CHANNEL][KERNEL_WIDTH*KERNEL_HEIGHT], Base_datatype feature_map[OUTPUT_CHANNEL][OUTPUT_WIDTH][OUTPUT_HEIGHT], int op_ch, int ip_ch){

//defintions
	Base_datatype fil_map_row_1 [INPUT_WIDTH][3]; 
	Base_datatype fil_map_row_2 [INPUT_WIDTH][3]; 
	Base_datatype fil_map_row_3 [INPUT_WIDTH][3]; 

// pixel_ip
	Base_datatype pixel_ip_2d[INPUT_WIDTH + 2*PADDING][INPUT_WIDTH + 2*PADDING];

 	for (int i=0; i< INPUT_HEIGHT+2*PADDING; i++){
 		one_layer_convolution_label3:for (int j=0; j< INPUT_WIDTH+2*PADDING; j++){
			pixel_ip_2d[i][j] = pixel_ip_after_padding[ip_ch][i][j];
		}
	}
// Write in first row 
	for (int i=0; i<KERNEL_WIDTH; i++){
			fil_map_row_1[0][i] = weights[op_ch][ip_ch][i];	
	}
	for (int i=0; i<KERNEL_WIDTH; i++){
			fil_map_row_2[0][i] = weights[op_ch][ip_ch][KERNEL_WIDTH+i];	
	}
	for (int i=0; i<KERNEL_WIDTH; i++){
			fil_map_row_3[0][i] = weights[op_ch][ip_ch][2*KERNEL_WIDTH+i];	
	}

//Write in other rows
	for (int i=1; i<INPUT_WIDTH; i++){
		for(int j =0;j<KERNEL_WIDTH;j++){
			fil_map_row_1[i][j] = fil_map_row_1[0][j];		
			fil_map_row_2[i][j] = fil_map_row_2[0][j];		
			fil_map_row_3[i][j] = fil_map_row_3[0][j];		
		}
	}

    // Convolution . First row of filter map is convoluted
		for (int q = 0; q<INPUT_WIDTH+2*PADDING-KERNEL_WIDTH+1; q= q+STRIDE){	
			one_layer_convolution_label2:for (int k = 0; k<INPUT_HEIGHT+2*PADDING-KERNEL_HEIGHT+1; k= k+STRIDE){
				feature_map[op_ch][k][q] += (pixel_ip_2d[k][q]*fil_map_row_1[k][0]) +(pixel_ip_2d[k][q+1]*fil_map_row_1[k][1])+(pixel_ip_2d[k][q+2]*fil_map_row_1[k][2]);
			}
		}

	// Convolution . second row of filter map is convoluted
		one_layer_convolution_label4:for (int q = 0; q<INPUT_WIDTH+2*PADDING-KERNEL_WIDTH+1; q= q+STRIDE){
			one_layer_convolution_label1:for (int k = 1; k<INPUT_HEIGHT+2*PADDING-KERNEL_HEIGHT+2; k= k+STRIDE){
				feature_map[op_ch][k-1][q] += (pixel_ip_2d[k][q]*fil_map_row_2[k-1][0]) +(pixel_ip_2d[k][q+1]*fil_map_row_2[k-1][1])+(pixel_ip_2d[k][q+2]*fil_map_row_2[k-1][2]);
			}
		}

    // Convolution .third row of filter map is convoluted
		for (int q = 0; q<INPUT_WIDTH+2*PADDING-KERNEL_WIDTH+1; q= q+STRIDE){	
			one_layer_convolution_label0:for (int k = 2; k<INPUT_HEIGHT+2*PADDING-KERNEL_HEIGHT+3; k= k+STRIDE){
				feature_map[op_ch][k-2][q] += (pixel_ip_2d[k][q]*fil_map_row_3[k-2][0]) +(pixel_ip_2d[k][q+1]*fil_map_row_3[k-2][1])+(pixel_ip_2d[k][q+2]*fil_map_row_3[k-2][2]);
			}
		}

	// Add Bias and ReLu function	

} // End of function

