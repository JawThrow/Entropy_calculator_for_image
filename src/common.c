#include "common.h"


// initialize
static void init_cmd_options(Cmd_options* options)
{
    options->input_fname = NULL;
    options->width  = -1;
    options->height = -1;
    options->nframes = -1;
    options->partition_blk_size = -1;
    options->transform_blk_size = -1;
    options->qstep_size = -1;
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
            else if (option[1] == 'h')
            {
                printf("help!\n");
            }
            else
            {
                printf("%s is uncorrect option. please check list of supported command using -h.\n", option);
            }
        }
    }

    if(!check_cmd(&temp_options))
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

/* initiation function */
// int load_YUV(IcspCodec &icC, char* fname, const int nframe,  const int width, const int height)
// {
// 	icC.YCbCr.nframe = nframe;
// 	icC.YCbCr.width  = width;
// 	icC.YCbCr.height = height;

// 	/*char CIF_path[256] = "..\\CIF(352x288)";	
// 	char CIF_fname[256];*/
	
// 	char CIF_path[256] = "data";
// 	char CIF_fname[256];

// 	sprintf(CIF_fname, "%s\\%s", CIF_path, fname);

// 	FILE* input_fp;
// 	input_fp = fopen(CIF_fname, "rb");
// 	if(input_fp==NULL)
// 	{
// 		cout << "fail to load cif.yuv" << endl;
// 		return -1;
// 	}

// 	icC.YCbCr.Ys  = (unsigned char*) malloc(sizeof(unsigned char)*width*height*nframe);
// 	icC.YCbCr.Cbs = (unsigned char*) malloc(sizeof(unsigned char)*(width/2)*(height/2)*nframe);
// 	icC.YCbCr.Crs = (unsigned char*) malloc(sizeof(unsigned char)*(width/2)*(height/2)*nframe);

// 	if(icC.YCbCr.Ys == NULL || icC.YCbCr.Cbs == NULL || icC.YCbCr.Crs == NULL)
// 	{
// 		cout << "fail to malloc Ys, Cbs, Crs" << endl;
// 		return -1;
// 	}

// 	for(int i=0; i<nframe; i++)
// 	{
// 		fread(&icC.YCbCr.Ys[i*width*height], sizeof(unsigned char)*height*width, 1, input_fp);
// 		fread(&icC.YCbCr.Cbs[i*(width/2)*(height/2)], sizeof(unsigned char)*(width/2)*(height/2), 1, input_fp);
// 		fread(&icC.YCbCr.Crs[i*(width/2)*(height/2)], sizeof(unsigned char)*(width/2)*(height/2), 1, input_fp);
// 	}
// 	fclose(input_fp);

// 	return 0;
// }

int init_entropy_calculator(int argc, char **argv)
{
    Cmd_options temp_cmd;
    if(!parse_command(argc, argv, &temp_cmd))
    {
        exit(-1);
    }

    return SUCCESS;
}