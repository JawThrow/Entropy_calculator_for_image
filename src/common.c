#include "common.h"


// initialize
static int parse_command(int argc, char **argv)
{
    // parse command and extract cfg options
        // -i: input
        // -w: width
        // -h: height
        // -n: the number of frames(default is 1)
        // -p: size of partition block(4, 8, 16, 32 ..., default is 16)
        // -t: transform block size(4, 8, 16 ..., default is 8)
        // -q: size of qstep(4, 8, 16 ..., default is 16)        
    // set proper initial values
    int n_cmd = argc;
    char* input_fname = NULL;
    int width  = 0;
    int height = 0;
    int partition_blk_size = 0;
    int transform_blk_size = 0;
    int qstep_size = 0;
    for (int i = 1; i < n_cmd; i++)
    {
        char *option = argv[i];
        if(option[0] == '-')
        {
            if (option[1] == 'i')
            {
                input_fname = argv[i+1];
                printf("input : %s \n", input_fname);
            }           
            else if (option[1] == 'w')
            {
                width = atoi(argv[i+1]);
                printf("width : %d \n", width);
            }
            else if (option[1] == 'h')
            {
                height = atoi(argv[i+1]);
                printf("height : %d \n", height);
            }
            else if (option[1] == 'p')
            {
                partition_blk_size = atoi(argv[i+1]);
                printf("partition block size: %d \n", partition_blk_size);
            }
            else if (option[1] == 't')
            {
                transform_blk_size = atoi(argv[i+1]);
                printf("transform block size : %d \n", transform_blk_size);
            }
            else if (option[1] == 'q')
            {
                qstep_size = atoi(argv[i+1]);
                printf("quantization qstep size : %d \n", qstep_size);
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