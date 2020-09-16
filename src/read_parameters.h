#include "global_var.h"


void Read_Parameters(Base_datatype pixel_ip[INPUT_CHANNEL][INPUT_WIDTH+2*PADDING][INPUT_HEIGHT+2*PADDING], Base_datatype weights[OUTPUT_CHANNEL][INPUT_CHANNEL * KERNEL_WIDTH * KERNEL_HEIGHT], Base_datatype bias[OUTPUT_CHANNEL]);
