//Input Parameters
#define INPUT_CHANNEL 64 
#define INPUT_WIDTH 112
#define INPUT_HEIGHT 112

//Output Parameters
#define OUTPUT_CHANNEL 128
#define OUTPUT_WIDTH 112
#define OUTPUT_HEIGHT 112

//Filter Parameters
#define KERNEL_WIDTH 3
#define KERNEL_HEIGHT 3

//Other Parameters
#define STRIDE 1
#define PADDING 1
#define PADDING_NUMBER 0

//Fixed point define
#define __FXP32__

//Floating point define
//#define __FTP32__

#ifdef __FXP32__
typedef float Base_datatype;
#endif // Fixed point

#ifdef __FTP32__
#include <ap_fixed.h>
typedef ap_fixed<32,3> Base_datatype;
#endif //Floating point
