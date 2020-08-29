
/*
** ocr.h for OCR in src
**
** Made by SheatNoisette
** Login   SheatNoisette
**
** Started on 2019 SheatNoisette
*/
#include <time.h>
#include <limits.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#ifdef SDL
    #include <SDL2/SDL.h>
#endif

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

/* Main OCR event - Handle internal OCR event */

/* Number of output neural network */
#define NEURAL_OUTPUT 36

/*
** Push a croped char in matrix format into NN 
*/
char get_char_from_nn(matrix *input, Neurone neural_network) {
    /* Convert input to array of float */
    float *char_input = matrix_to_float_array(input);
    /* GIve it to NN */
    float *prediction_nn = prediction(neural_network, char_input); 
    /* Deduct char from prediction */
    char our_char = printD(prediction_nn, NEURAL_OUTPUT);

    /* Free old Matrix->Float array */
    free(char_input);
    /* Return char */
    return our_char;
}

/*
** Extract a character from a list of postion, crop from a source image, 
** resize it and give it his binary matrix
*/
matrix *crop_image_export_matrix (
    image *source, l_list *char_position, int char_number
) {
    /* Extract image */
    image *temp_image = crop_image_at(source, 
            list_get_value(char_position, char_number),
            list_get_value(char_position, char_number + 1),
            list_get_value(char_position, char_number + 2),
            list_get_value(char_position, char_number + 3)
        );

    /* Do linear interpotation */
    image *temp_resized = image_resize_linear_interp(temp_image, 16, 16);

    /* Convert to matrix already created */
    matrix *char_matrix = image_to_binmatrix(temp_resized);

    /* Free the resized image */
    free_image(temp_resized);
    /* Free the temp croped image */
    free_image(temp_image);

    /* Return the image */
    return char_matrix;
}

/*
** Using the output from text_reconstruction try to rebuild the text
*/
char *get_text_ocr (
    image *input_img, l_list *text_stucture, l_list *char_position, 
    Neurone neural_network
) {
    /* String visualization cursor */
    unsigned long cursor = 0;

    /* Cursor of the current caracter selected detected */
    int current_char = 0;

    /* Get length of the list */
    unsigned long list_size = list_length(text_stucture);

    /* Allocate memory for string (Size of the list + \0) */
    char *out_string = (char *)malloc(list_size * sizeof(char) + 1);

    /* Matrix cropped */
    matrix *matrix_cropped = NULL;
    
    /* Check malloc */
    if (out_string == NULL) {
        printf("[OCR] Failed to allocate memory for text structure");
        return NULL;
    }

    /* Build string visualization */
    for (cursor = 0; cursor < list_size; cursor++) {
        /* Space */
        if (list_get_value(text_stucture, cursor) == 0) {
            *(out_string + cursor) = ' ';
        }
        /* Letter - Get from NN */
        else if (list_get_value(text_stucture, cursor) == 1) {
            
                /* Crop character */
                matrix_cropped = crop_image_export_matrix(
                                                    input_img,
                                                    char_position, 
                                                    current_char * 4);
                /* Give it to NN */
                *(out_string + cursor) = get_char_from_nn(matrix_cropped, 
                                                        neural_network);

                /* Free the matrix */
                free_matrix(matrix_cropped);
                /* Go to next char */
                current_char++;
        } else {
            /* Return */
            *(out_string + cursor) = '\n';
        }
    }

    /* Close string */
    *(out_string + list_size) = '\0';

    /* Return string */
    return out_string;
}

/*
** Run OCR
*/
char *ocr_run (
    char *file, unsigned char visual, unsigned char otsu, 
    unsigned char force_sdl, char *filters, char *train_weight
){

    /* Corner of the paragraph */
    int *border_table;

    /* Load image using bitmap loader or SDL */
    image *ocr_image;

    /* Output text */
    char *output_text = NULL;

    /* Neural Network definition */
    Neurone neural_network;

    /* Get y positions */
    l_list *lines_char_y;

    /* Char position */
    l_list *char_pos;

    /* Text structure */
    l_list *text_structure;

    /* If train_weight is NULL, set the default name */
    if (train_weight == NULL)
        train_weight = "train_data.txt";

    /* Create NN from file */
    neural_network = load(train_weight);

    /* Force SDL File loading */
    if (force_sdl) {
        #ifdef SDL
            SDL_Surface *sdl_image = SDL_LoadBMP(file);
            ocr_image = sdl_surface_to_image(sdl_image);
            SDL_FreeSurface(sdl_image);
        #else
            printf("[OCR] SDL Support Disabled, can't use SDL");
            ocr_image = bitmaploader(file);
        #endif
    } else {
        ocr_image = bitmaploader(file);

    }

    /* Apply grayscale */
    printf("[OCR] Applying grayscale...\n");
    i_grayscale_average(ocr_image);

    /* Convolution matrix filter */
    if (filters != NULL) {
        if (strcmp(filters, "a") == 0 || strcmp(filters, "s") == 0) {
            printf("[OCR] Applying sharpen filter on image...\n");
            ocr_image = sharpen_filter(ocr_image);
        }
        if (strcmp(filters, "a") == 0 || strcmp(filters, "d") == 0) {
            printf("[OCR] Applying denoise filter on image...\n");
            ocr_image = denoise_filter(ocr_image);
        }
    }

    /* Use otsu ? */
    printf("[OCR] Applying Binarization...\n");
    if (otsu) {
        i_otsu_method_binarization(ocr_image);
    } else {
        i_binarization_threshold(ocr_image, 127);
    }

    /* Get paragraph border */
    printf("[OCR] Segment image...\n");
    border_table = r_get_paragraph_border(ocr_image);

    /* Get y positions */
    lines_char_y = r_find_char_y(ocr_image, 0, ocr_image->width);
    
    /* Get char position */
    char_pos = r_find_char_image(ocr_image, lines_char_y);

    /* Visualization of the char positions */
    if (visual) {
        #ifdef SDL
            visu_draw_border_box(ocr_image, border_table, 0, 255, 0);
            visu_draw_y_char_pos(ocr_image, lines_char_y, border_table,255,0,0);
            visu_draw_border_letter(ocr_image, char_pos, 0, 255, 255);

            /* Save bitmap */
            SDL_Surface *converted_image = image_to_sdl_surface(ocr_image);
            /* Export */
            SDL_SaveBMP(converted_image, "exported/ocr_visual.bmp");

            /* Free surface */
            SDL_FreeSurface(converted_image);
        #else
            printf("[OCR] Can't use visualizer, SDL support disabled");
        #endif
    }

    printf("[OCR] Chars detected : %li\n", list_length(char_pos) / 4);
    
    /* Determine text structure */
    printf("[OCR] Getting text structure ...\n");
    text_structure = deduct_text_structure(char_pos);

    /* Get characters recongnised */
    output_text = get_text_ocr (
                    ocr_image, text_structure, char_pos, 
                    neural_network
                );

    /* ----------------- */
    /*  Free everything */
    list_free(lines_char_y);
    list_free(char_pos);
    list_free(text_structure);
    free(border_table);
    free_image(ocr_image);
    /* Free NN */
    freez(neural_network);

    /* Return string */
    return output_text;
}

/*
** Train neural network
*/
void train_neural_network(char *train_path, char *dataset_path) {

    /* Neural Network parameters */
    int nbInput;
    int nbHidden;
    int nbOutput;
    float rate;
    float down;
    int iterations;
    float errors; /* Error rate */
    float* input; /* Input neuron */
    float* neurone; /* Current neurons */

    /*  Training data */
    Data data;

    /* Neural network */
    Neurone neuron;

    /* Iterators */
    int i;
    int j;

    /* Set default values if the pointer is null */
    if (train_path == NULL) {
        train_path = "train_data.txt";
    }
    if (dataset_path == NULL) {
        dataset_path = "dataset.txt";
    }

    printf("[Neural] Training Neural Network using %s dataset...\n", 
            dataset_path);

    srand(time(0));

    nbInput = 256;
    nbHidden = 36;
    nbOutput = 36; /*  26 letters + 10 numbers */

    rate = 0.01f; /*  learning rate */
    down = 0.99f;
    iterations = 1000; /*  number of training session */

    /*  Training data */
    data = build(dataset_path, nbInput, nbOutput);

    /*  Train NN */
    neuron = neuronal(nbInput, nbHidden, nbOutput);

    for(i = 0; i < iterations; i++)
    {
        randShuffle(data);
        errors = 0.0f;
        for (j = 0; j < data.nbRows; j++)
        {
            input = data.input[j];
            neurone = data.neurone[j];
            errors += train_Neural(neuron, input, neurone, rate);
        }
        rate *= down;
    }

    /*  Save of the neural network */
    printf("[Neural] Saving training data to %s...\n", train_path);
        save(neuron, train_path);
    printf("[Neural] Training done!\n");
    freez(neuron);
}