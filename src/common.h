#ifndef __COMMON__
#define __COMMON__
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define TRUE 1
#define FALSE 0

#define SUCCESS TRUE
#define FAILURE FALSE

// file structure?
typedef struct __ENTROPY_CALC__
{
    int width;
    int height;
    int nframes;
    
    unsigned char *img_luma;
    unsigned char *img_cb;
    unsigned char *img_cr;

    int partition_size;
    unsigned char **org_blk_luma;
    unsigned char **org_blk_cb;
    unsigned char **org_blk_cr;

    int transform_size;
    double* t_coeff_luma;
    double* t_coeff_cb;
    double* t_coeff_cr;

    int quantization_size;
    int qstep_size;
    int *q_index_luma;
    int *q_index_cb;
    int *q_index_cr;

} Entropy_calc;

typedef struct __CMD_OPTIONS__
{
    char *input_fname;
    int width;
    int height;
    int nframes;

    int partition_blk_size;
    int transform_blk_size;
    int quantization_size;
    int qstep_size;

    // and so on zz

}Cmd_options;

// image structure
    // width
    // height
    // mb size
    // original
    // transformed blk
    // transform coefficients distribution
    // quantized blk
    // quantized index distribution

// transform structure
    // transform size

// quantization structure
    // quantization size

// initialize
int init_entropy_calculator(int argc, char **argv);
int load_image();
int load_video();
#endif
