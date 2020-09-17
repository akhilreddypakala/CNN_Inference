# CNN_Inference
Instructions for running the file
1) create a data directory parallel to src directory
2) add input.dat, weight.dat in that directory
3) Please uncomment __DUMP_OUTPUT__  in global_var.h to dump generated outputs
4)In read_parameters.cpp, for reading inputs and weights, absolute path is given since relative path is not working on vivado. please change accordingly
5)Run commands:
6)./compile.sh
7)./cnn
