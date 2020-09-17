#include "global_var.h"

void convolution(Base_datatype pixel_ip_after_padding[INPUT_CHANNEL][INPUT_WIDTH + 2*PADDING] [INPUT_HEIGHT+2*PADDING], Base_datatype weights[OUTPUT_CHANNEL][INPUT_CHANNEL][KERNEL_WIDTH*KERNEL_HEIGHT], Base_datatype bias[OUTPUT_CHANNEL], Base_datatype feature_map[OUTPUT_CHANNEL][OUTPUT_WIDTH][OUTPUT_HEIGHT]);

void one_layer_convolution (Base_datatype pixel_ip_after_padding[INPUT_CHANNEL][INPUT_WIDTH + 2*PADDING] [INPUT_HEIGHT+2*PADDING], Base_datatype weights[OUTPUT_CHANNEL][INPUT_CHANNEL][KERNEL_WIDTH*KERNEL_HEIGHT], Base_datatype feature_map[OUTPUT_CHANNEL][OUTPUT_WIDTH][OUTPUT_HEIGHT], int op_ch, int ip_ch);

