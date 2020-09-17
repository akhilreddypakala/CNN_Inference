# CNN_Inference
Instructions for running the file
1) create a data directory parallel to src directory
2) add input.dat, weight.dat in that directory
Please uncomment __DUMP_OUTPUT__ to dump generated outputs
In read_parameters.cpp, for reading inputs and weights, absolute path is given since relative path is not working on vivado. please change accordingly
Run commands:
./compile.sh
./cnn
