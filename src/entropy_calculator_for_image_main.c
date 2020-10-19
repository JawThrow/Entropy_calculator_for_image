#include "common.h"



int main(int argc, char* argv[])
{
    Entropy_calc ecalc;
    if(init_entropy_calculator(argc, argv, &ecalc) == FAILURE)
    {
        // Initialization done
        // command loading done
        // image loading done
        // configuration done
        // partitioning
        exit(-1);
    }
    
    // image processing        
        // transform
        // quantization

    // something statistical    
    return 0;
}