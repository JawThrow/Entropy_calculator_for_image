#include "common.h"



int main(int argc, char* argv[])
{
    Entropy_calc ecalc;
    if(init_entropy_calculator(argc, argv) == FAILURE)
    {
        // Initialization
        // command loading
        // image loading
        // configuration
        // partitioning
        exit(-1);
    }
    
    // image processing        
        // transform
        // quantization

    // something statistical    
    return 0;
}