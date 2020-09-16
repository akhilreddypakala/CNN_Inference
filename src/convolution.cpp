#include "convolution.h"
#include <fstream>
#include <iostream>
#include "global_var.h"

using namespace std;

void convolution(Base_datatype pixel_ip_after_padding[INPUT_CHANNEL][INPUT_WIDTH + 2*PADDING] [INPUT_HEIGHT+2*PADDING], Base_datatype weights[OUTPUT_CHANNEL][INPUT_CHANNEL*KERNEL_WIDTH*KERNEL_HEIGHT], Base_datatype bias[OUTPUT_CHANNEL], Base_datatype feature_map[OUTPUT_CHANNEL][OUTPUT_WIDTH][OUTPUT_HEIGHT] ){


	Base_datatype res_wei[INPUT_CHANNEL][KERNEL_HEIGHT][KERNEL_WIDTH];
	
	int count = 0;
	for (int i=0;i<OUTPUT_CHANNEL; i++){
		count =0;
		for (int j=0; j<INPUT_CHANNEL; j++){

			for (int k=0; k<KERNEL_HEIGHT; k++){
				for (int q =0; q<KERNEL_WIDTH; q++){
					res_wei[j][k][q] = weights[i][count];
					count+=1;
				}
			} 
    // Convolution
			for (int k = 0; k<INPUT_HEIGHT+2*PADDING-KERNEL_HEIGHT+1; k= k+STRIDE){
				for (int q = 0; q<INPUT_WIDTH+2*PADDING-KERNEL_WIDTH+1; q= q+STRIDE){
					feature_map[i][k][q] +=  dot_product(res_wei, pixel_ip_after_padding ,q, k, i,j);
				}
			}
	// Add Bias and ReLu function	
			for (int k = 0; k<INPUT_HEIGHT+2*PADDING-KERNEL_HEIGHT+1; k= k+STRIDE){
				for (int q = 0; q<INPUT_WIDTH+2*PADDING-KERNEL_WIDTH+1; q= q+STRIDE){
					feature_map[i][k][q] += bias[i];
					if (feature_map[i][k][q] < 0)
						feature_map[i][k][q] = 0;
				}
			}
		} // Input Channel

	} //OUPUT_CHANNEL
}


Base_datatype dot_product (Base_datatype res_wei[INPUT_CHANNEL][KERNEL_HEIGHT][KERNEL_WIDTH], Base_datatype pixel_ip_after_padding[INPUT_CHANNEL][INPUT_WIDTH+2*PADDING] [INPUT_HEIGHT + 2*PADDING], int col_number, int row_number, int op_ch, int inp_ch){
#pragma HLS PIPELINE

	Base_datatype one_conv_op=0;
	Base_datatype inp_1[9];
	Base_datatype inp_2[9];
	Base_datatype op[9];

	for (int i=0; i<3; i++){
		for (int j=0; j<3; j++){
			inp_1[i*(3)+j] = pixel_ip_after_padding [inp_ch][i+row_number][j+col_number];
			inp_2[i*(3)+j] = res_wei[inp_ch][i][j];
		}

	}

		for (int i = 0; i< 9; i++){
#pragma HLS UNROLL factor=9
				op[i] = inp_1[i] * inp_2[i];
				one_conv_op += op[i];
		}

//	for (int i = 0; i< 3; i++){
//		for (int j= 0; j< 3;j++){
//			one_conv_op += pixel_ip_after_padding[inp_ch][i+row_number][j+col_number] * res_wei[inp_ch][i][j];
//		}
//	}

//	return one_conv_op;
		return one_conv_op;
}
