#include <iostream>
#include "Grid_Storage.hpp"

int main(int argc, char **argv){
    if(argc != 5){
        fprintf(stderr, "Please use 5 inputs.\n");
        return 1;
    }
    double extent = atof(argv[1]);
    int objcount = atoi(argv2[2]); 
    int cells_per_dim = atoi(argv[3]);
    int dimcount = atoi(argv[4]);
    
    GridStorage g(extent, objcount, cells_per_dim, dimcount);
    g.basic3dTest(); 
    return 0;
}
