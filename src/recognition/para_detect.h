/*
** para_detect.h for OCR in src/recognition
**
** Made by SheatNoisette
** Login   SheatNoisette
**
** Started on  2019 SheatNoisette
*/
//Paragraph detection

#ifndef PARA_DETECT_H
#define PARA_DETECT_H

#include "../bitmap/image.h"
#include "../commons/linked_list.h"

//----------------------------
//Functions

int *r_get_paragraph_border(image *img);

#endif