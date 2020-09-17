rm -rf *.o 
g++ -g -o cnn global_var.h convolution.h read_parameters.h main.cpp convolution.cpp  read_parameters.cpp  
 #g++ -g -o cnn global_var.h  read_parameters.h main.cpp  read_parameters.cpp  
