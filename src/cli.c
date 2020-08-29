/*
** cli for OCR in src
**
** Made by SheatNoisette
**
** Started on  2019 SheatNoisette
*/

#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

/* Check if we try to compile to WASM */
#ifdef wasm 
    #define errx(std, message) printf(message)
#elif __gnu_linux__
    #include <err.h>
#else
    #define errx(std, message) printf(message); exit(std);
#endif

/* Posix API */
#ifdef __gnu_linux__
    #include <unistd.h>
#endif

/* Easy arg support on linux */
#ifdef __gnu_linux__
    #include <getopt.h>
#elif _WIN32
    #include "ports/getopt.h"
#endif

#ifdef SDL
    #include <SDL2/SDL.h>
#endif

#include "cli.h"
#include "ocr.h"
#include "commons/matrix.h"
#include "commons/matrix_tools.h"
#include "commons/linked_list.h"
#include "bitmap/image.h"
#include "bitmap/image_tools.h"
#include "bitmap/bitmap.h"
#include "bitmap/image_drawing.h"
#include "filters/binarization.h"
#include "filters/basic_filters.h"
#include "filters/convolution_matrix.h"
#include "filters/denoise_filter.h"
#include "filters/sharpen_filter.h"
#include "recognition/char_detect.h"
#include "recognition/para_detect.h"
#include "recognition/detect_visualizer.h"
#include "recognition/text_reconstruction.h"
#include "neural/neurone.h"
#include "neural/train_net.h"
#include "neural/train_data.h"
#include "neural/load.h"
#include "neural/load.h"
#include "neural/maths.h"

/* Command line system for OCR */

/*
** Parse input from app arguments
*/

void cli_parse_commands(int argc, char **argv) {


    /* Current params */
    int opt;
    /* File to load */
    char *img_file = NULL;
    /* Turn on visualization */
    unsigned char full_visual = 0;
    /* Otsu binarization */
    unsigned char enable_otsu = 0;
    /* Force SDL loading */
    unsigned char force_sdl = 0;
    /* Force train neural network */
    unsigned char train_nn = 0;
    /* Train output */
    char *train_out_file = NULL;
    /* Dataset path */
    char *dataset_path = NULL;
    /* Convolutional filter needed to be added */
    char *convolution_filters = NULL;
    /* Output from OCE */
    char *ocr_out = NULL;
      
    /* Check number of arguments */
    /* No arguments */
    if (argc == 1) {
        cli_print_help();
        return;
    }

#ifdef __gnu_linux__
    /* Get opt command support */

    while((opt = getopt(argc, argv, ":i:hvosf:t:d:w:")) != -1)  
    {  
        /*  Image input */
        if (opt == 'i') {
            img_file = optarg;
        } else if (opt == 'h') {
        /* Print help */
        cli_print_help();
        /* Turn on full visualisation of the detection of the chars */
        } else if (opt == 'v') {
            full_visual = 1;
        } else if (opt == 'o') {
            enable_otsu = 1;
        } else if (opt == 's') {
            force_sdl = 1;
        } else if (opt == 'f') {
            convolution_filters = optarg;
        } else if (opt == 't') {
            train_nn = 1;
            train_out_file = optarg;
        } else if (opt == 'w') {
            train_out_file = optarg;
        } else if (opt == 'd') {
            dataset_path = optarg;
        } else if (opt == '?') {
            printf("Unknown command\n");
        }
    }
#else
    /* Generic */

#endif
    
    /* Train NN */
    if (train_nn) {
        train_neural_network(train_out_file, dataset_path);
    }
    /* Check if image is valid */
    else if (img_file != NULL) {
        ocr_out = ocr_run(
            img_file, full_visual, enable_otsu, force_sdl, 
            convolution_filters, train_out_file
            );
        /* Get output from OCR */
        printf("\n%s\n", ocr_out);
        /* Free string */
        free(ocr_out);
    } else {
        cli_print_help();
    }
}


/*
** -----------------------------
** Commands
*/

/*
** Print OCR Logo
*/
void cli_print_logo() {

    /* Ugly way to print a logo */
    printf("      ___           ___           ___\n");
    printf("     /\\  \\         /\\  \\         /\\  \\ \n");
    printf("    /::\\  \\       /::\\  \\       /::\\  \\ \n");
    printf("   /:/\\:\\  \\     /:/\\:\\  \\     /:/\\:\\  \\ \n");
    printf("  /:/  \\:\\  \\   /:/  \\:\\  \\   /::\\~\\:\\  \\ \n");
    printf(" /:/__/ \\:\\__\\ /:/__/ \\:\\__\\ /:/\\:\\ \\:\\__\\ \n");
    printf(" \\:\\  \\ /:/  / \\:\\  \\  \\/__/ \\/_|::\\/:/  / \n");
    printf("  \\:\\  /:/  /   \\:\\  \\          |:|::/  / \n");
    printf("   \\:\\/:/  /     \\:\\  \\         |:|\\/__/ \n");
    printf("    \\::/  /       \\:\\__\\        |:|  | \n");
    printf("     \\/__/         \\/__/         \\|__| \n\n");
    printf("Simple optical character recogniton software\n\n");
}

/*
** Print help
*/
void cli_print_help() {

    /* Print logo and help */
    cli_print_logo();

    /* Help */
    printf("COMMANDS:\n");
    printf("-t <File>   Run neural network training and save generated\n");
    printf("            training data in <file> (default: train_data.txt)\n");
    printf("-w <File>   Use custom training data for recognition\n");
    printf("            (Default: train_data.txt)\n");
    printf("-i <File>   Image to cut character from\n");
    printf("-v          Show the caracter cutting\n");
    printf("-d <File>   Specifiy a custom dataset (default: dataset.txt)\n");
    printf("-o          Use Otsu binarization instead of basic threshold\n");
    printf("-f <Filter> Apply a convolutional filter on the image\n");
    printf("            Valid input: a / s / d - A-ll D-enoise S-harpen\n");
    printf("-h          Print this help\n");
}