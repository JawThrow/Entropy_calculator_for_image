#include "common.h"


// initialize
static int parse_command(int argc, char **argv)
{
    // parse command and extract cfg options
        // -i: input
        // -w: width
        // -h: height
        // -p: size of partition block(4, 8, 16, 32 ..., default is 16)
        // -t: transform block size(4, 8, 16 ..., default is 8)
        // -q: size of qstep(4, 8, 16 ..., default is 16)        
    // set proper initial values
    int n_cmd = argc;
    for (int i = 1; i < n_cmd; i++)
    {
        char *option = argv[i];
        if(option[0] == '-')
        {
            if (option[1] == 'i')
            {
                printf("input option!\n");
            }           
            else if (option[1] == 'w')
            {
                printf("width\n");
            }
            else if (option[1] == 'h')
            {
                printf("height\n");
            }
            else if (option[1] == 'p')
            {
                printf("partition block size\n");
            }
            else if (option[1] == 't')
            {
                printf("transform block size\n");
            }
            else if (option[1] == 'q')
            {
                printf("quantization qstep size\n");
            }
            else
            {
                printf("%s is uncorrect option. please check list of supported command using ---help.\n", option);
            }
            
        }
    }
    return SUCCESS;
}

static int alloc_image_mem(int width, int height, int nframes, int ntype)
{

    return SUCCESS;
}

int init_entropy_calculator(int argc, char **argv)
{
    if(!parse_command(argc, argv))
    {
        exit(-1);
    }

    return SUCCESS;
}