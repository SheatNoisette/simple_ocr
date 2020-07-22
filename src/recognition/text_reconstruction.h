/*
** text_reconstruction.h for OCR in src/recognition
**
** Made by SheatNoisette
** Login   SheatNoisette
**
** Started on  2019 SheatNoisette
*/

#ifndef TEXT_RECONSTRUCTION_H
#define TEXT_RECONSTRUCTION_H

#include "../commons/linked_list.h"

//---------------------------------------
// Functions

size_t dt_get_average_char_size(l_list *input_pos, size_t number_chars);
size_t dt_get_average_char_spacing(l_list *input_pos, size_t number_chars);
l_list *deduct_text_structure (l_list *input_pos);


#endif