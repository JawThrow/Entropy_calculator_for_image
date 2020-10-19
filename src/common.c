#include "common.h"


// initialize
static void init_cmd_options(Cmd_options* options)
{
    options->input_fname        = NULL;
    options->width              = -1;
    options->height             = -1;
    options->nframes            = -1;
    options->partition_blk_size = -1;
    options->transform_blk_size = -1;
    options->qstep_size         = -1;
}

static void set_cmd_options_for_test(Cmd_options* options)
{
    options->input_fname        = "../data/news_cif(352X288)_300f.yuv";
    options->width              = 352;
    options->height             = 288;
    options->nframes            = 1;
    options->partition_blk_size = 16;
    options->transform_blk_size = 16;
    options->qstep_size         = 32;
}

static int check_cmd(Cmd_options* options)
{
    int status = SUCCESS;
    if (options->input_fname == NULL /*|| and so on zz*/)
    {
        printf("-i: uncorrect input file name...\n");
        status = FAILURE;        
    }

    if (options->height == 0)
    {
        printf("-h: uncorrect height...\n");
        status = FAILURE;
    }

    if (options->width == 0)
    {
        printf("-w: uncorrect width...\n");
        status = FAILURE;
    }

    if (options->nframes == 0)
    {
        printf("-n: uncorrect nframes...\n");
        status = FAILURE;
    }
    else if (options->nframes < 0)
    {
        options->nframes = 1;
    }
    
    if (options->partition_blk_size == 0)
    {
        printf("-p: uncorrect partition block size...\n");
        status = FAILURE;
    }
    else if(options->partition_blk_size < 0)
    {
        options->partition_blk_size = 16;
    }

    if (options->transform_blk_size == 0)
    {
        printf("-p: uncorrect transform block size...\n");
        status = FAILURE;
    }
    else if(options->transform_blk_size < 0)
    {
        options->transform_blk_size = 8;
    }

    if (options->quantization_size == 0)
    {
        printf("-p: uncorrect quantization block size...\n");
        status = FAILURE;
    }
    else if(options->quantization_size < 0)
    {
        options->quantization_size = options->transform_blk_size;
    }
    
    if (options->qstep_size == 0)
    {
        printf("-p: uncorrect qstep size...\n");
        status = FAILURE;
    }
    else if(options->qstep_size < 0)
    {
        options->quantization_size = 16;
    }

    return status;
}

// parse command and extract cfg options
    // -i: input
    // -w: width
    // -h: height
    // -n: the number of frames(default is 1)
    // -p: size of partition block(4, 8, 16, 32 ..., default is 16)
    // -t: transform block size(4, 8, 16 ..., default is 8)
    // -q: size of qstep(4, 8, 16 ..., default is 16)        
static int parse_command(int argc, char **argv, Cmd_options* options)
{   
    // set proper initial values
    Cmd_options temp_options;   
    init_cmd_options(&temp_options);

    int debug_flag = 0;
    int n_cmd = argc;
    for (int i = 1; i < n_cmd; i++)
    {
        char *option = argv[i];
        if(option[0] == '-')
        {
            if (option[1] == 'i')
            {
                temp_options.input_fname = argv[i+1];
            }
            else if (option[1] == 'w')
            {
                temp_options.width = atoi(argv[i+1]);
            }
            else if (option[1] == 'h')
            {
                temp_options.height = atoi(argv[i+1]);
            }
            else if (option[1] == 'n')
            {
                temp_options.nframes = atoi(argv[i+1]);
            }            
            else if (option[1] == 'p')
            {
                temp_options.partition_blk_size = atoi(argv[i+1]);
            }
            else if (option[1] == 't')
            {
                temp_options.transform_blk_size = atoi(argv[i+1]);
            }
            else if (option[1] == 'q')
            {
                temp_options.qstep_size = atoi(argv[i+1]);
            }
            else if (option[1] == 'H')
            {
                printf("help!\n");
            }
            else if (option[1] == 'd')
            {
                printf("debug processing!\n");                
                debug_flag = 1;
            }
            else
            {
                printf("%s is uncorrect option. please check list of supported command using -H.\n", option);
            }
        }
    }

    if (debug_flag)
    {
        set_cmd_options_for_test(&temp_options);
    }
    else if (!check_cmd(&temp_options))
    {
        return FAILURE;
    }

    *options = temp_options;

    return SUCCESS;
}

static int alloc_image_mem(int width, int height, int nframes, int ntype)
{

    return SUCCESS;
}

static void set_entropy_calc_from_cmd(Cmd_options* options, Entropy_calc* ecalc)
{
    ecalc->height                = options->height;
    ecalc->width                 = options->width;
    ecalc->nframes               = options->nframes;
    ecalc->partition_blk_size    = options->partition_blk_size;
    ecalc->transform_blk_size    = options->transform_blk_size;
    ecalc->quantization_blk_size = options->transform_blk_size;
    ecalc->qstep_size            = options->qstep_size;
}
static int load_YUV(Cmd_options* options, Entropy_calc* ecalc)
{
    char* yuv_fname = options->input_fname;    
    FILE* input_fp = fopen(yuv_fname, "rb");
    if(input_fp == NULL)    
    {
        printf("fail to load yuv!\n");
        return FAILURE;
    }

    int width   = options->width;
    int height  = options->height;
    int nframes = options->nframes;
    unsigned char* luma = (unsigned char*) malloc(sizeof(unsigned char)*width*height*nframes);
    unsigned char* cb   = (unsigned char*) malloc(sizeof(unsigned char)*(width/2)*(height/2)*nframes);
    unsigned char* cr   = (unsigned char*) malloc(sizeof(unsigned char)*(width/2)*(height/2)*nframes);

	if(luma == NULL || cb == NULL || cr == NULL)
	{
		printf("fail to alloc memory for input yuv\n");
		return FAILURE;
	}

	for(int i = 0; i < nframes; i++)
	{
		fread(&luma[i*width*height],       sizeof(unsigned char)*height*width,         1, input_fp);
		fread(&cb[i*(width/2)*(height/2)], sizeof(unsigned char)*(width/2)*(height/2), 1, input_fp);
		fread(&cr[i*(width/2)*(height/2)], sizeof(unsigned char)*(width/2)*(height/2), 1, input_fp);
	}

    fclose(input_fp);
    return SUCCESS;
}

int init_entropy_calculator(int argc, char **argv, Entropy_calc* ecalc)
{
    Cmd_options temp_cmd;    
    if(!parse_command(argc, argv, &temp_cmd))
    {
        exit(-1);
    }
    
    Entropy_calc temp_ecalc;
    set_entropy_calc_from_cmd(&temp_cmd, &temp_ecalc);
    if(!load_YUV(&temp_cmd, &temp_ecalc))
    {
        exit(-1);
    }
    
    return SUCCESS;
}