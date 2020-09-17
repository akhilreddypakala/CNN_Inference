#include "convolution.h"
#include <fstream>
#include <iostream>
#include "global_var.h"

using namespace std;

void convolution(Base_datatype pixel_ip_after_padding[INPUT_CHANNEL][INPUT_WIDTH + 2*PADDING] [INPUT_HEIGHT+2*PADDING], Base_datatype weights[OUTPUT_CHANNEL][INPUT_CHANNEL*KERNEL_WIDTH*KERNEL_HEIGHT], Base_datatype bias[OUTPUT_CHANNEL], Base_datatype feature_map[OUTPUT_CHANNEL][OUTPUT_WIDTH][OUTPUT_HEIGHT] ){


	Base_datatype res_wei[OUTPUT_CHANNEL][INPUT_CHANNEL][KERNEL_HEIGHT][KERNEL_WIDTH];
	
	int count = 0;
	for (int i=0;i<OUTPUT_CHANNEL; i++){
		count =0;
		for (int j=0; j<INPUT_CHANNEL; j++){
			for (int k=0; k<KERNEL_HEIGHT; k++){
				for (int q =0; q<KERNEL_WIDTH; q++){
					res_wei[i][j][k][q] = weights[i][count];
					count+=1;
				}
			}
		}
	} 
    // Convolution
	for (int i=0;i<OUTPUT_CHANNEL; i++){
		for (int j=0; j<INPUT_CHANNEL; j++){
			for (int k = 0; k<INPUT_HEIGHT+2*PADDING-KERNEL_HEIGHT+1; k= k+STRIDE){
				for (int q = 0; q<INPUT_WIDTH+2*PADDING-KERNEL_WIDTH+1; q= q+STRIDE){
					if (i == 127 && j == 63 && k == 111 && q==111){
						cout << feature_map[127][111][111]<<endl;
					}
					feature_map[i][k][q] +=  dot_product(res_wei, pixel_ip_after_padding ,q, k, i,j);
					if (i == 127 && j == 63 && k == 111 && q==111){
						cout << feature_map[127][111][111]<<endl;
					}
				}
			}
		}
	}
	//cout << feature_map[127][111][111]<<endl;
	// Add Bias and ReLu function	
	for (int i=0;i<OUTPUT_CHANNEL; i++){
			for (int k = 0; k<INPUT_HEIGHT+2*PADDING-KERNEL_HEIGHT+1; k= k+STRIDE){
				for (int q = 0; q<INPUT_WIDTH+2*PADDING-KERNEL_WIDTH+1; q= q+STRIDE){
					feature_map[i][k][q] += bias[i];
				}
			}
		 // Input Channel

	} //OUPUT_CHANNEL

}


Base_datatype dot_product (Base_datatype res_wei[OUTPUT_CHANNEL][INPUT_CHANNEL][KERNEL_HEIGHT][KERNEL_WIDTH], Base_datatype pixel_ip_after_padding[INPUT_CHANNEL][INPUT_WIDTH+2*PADDING] [INPUT_HEIGHT + 2*PADDING], int col_number, int row_number, int op_ch, int inp_ch){

	Base_datatype one_conv_op=0;

	for (int i = 0; i< 3; i++){
		for (int j= 0; j< 3;j++){
			one_conv_op += pixel_ip_after_padding[inp_ch][i+row_number][j+col_number] * res_wei[op_ch][inp_ch][i][j];
			if(op_ch == 127 && inp_ch == 63 && row_number == 111 && col_number == 111){
				cout << pixel_ip_after_padding[inp_ch][i+row_number][j+col_number] << "," << res_wei[op_ch][inp_ch][i][j] << "," << one_conv_op <<endl;
			}
		}
	}

//	return one_conv_op;
		return one_conv_op;
}
