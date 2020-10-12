/*
** ocr.h for OCR in src
**
** Made by SheatNoisette
** Login   SheatNoisette
**
** Started on  2019 SheatNoisette
*/

#ifndef OCR_H
#define OCR_H

char *ocr_run (
    char *file, unsigned char visual, unsigned char otsu,
    unsigned char force_sdl, char *filters, char *train_weight
);

void train_neural_network(char *train_path, char *dataset_path);

#endif