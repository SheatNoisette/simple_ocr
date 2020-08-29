/*
** linked_list.h for OCR in src/commons
**
** Made by SheatNoisette
** Login   SheatNoisette
**
** Started on  2019 SheatNoisette
*/

/* Simple linked list implementation */

#ifndef LINKED_LIST_H
#define LINKED_LIST_H

/* Imports */
#include <stddef.h>

/* ---------------------------------- */
/*  Structures */

/* l_list is an alias of list_node */
typedef struct list_node l_list;

struct list_node {
    int data;
    l_list *next_element;
};


/* ---------------------------------- */
/*  Prototypes */

l_list *list_create();
void list_add(l_list **input_list, int element);
unsigned long list_length(l_list *list);
int list_get_value(l_list *list, int pos);
void list_set_value(l_list *list, int pos, int value);
void list_free(l_list *list);
void list_print(l_list *list);

#endif