rm -rf *.o
rm -rf ../data/generated_output.dat 
g++ -g -o cnn global_var.h convolution.h read_parameters.h main.cpp convolution.cpp  read_parameters.cpp  
