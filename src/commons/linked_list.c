/*
** linked_list.c for OCR in src/commons
**
** Made by SheatNoisette
** Login   SheatNoisette
**
** Started on  2019 SheatNoisette
** Based on LSE list implementation
*/

#include "linked_list.h"

#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>

// Simple linked list implementation

/*
** Create a linked list
*/

l_list *list_create()
{
    // Create a empty list, this will be overitten when adding a
    // Element
    return NULL;
}

/*
** Add element to the list
*/

void list_add(l_list **input_list, int element)
{
    l_list *tmp = malloc(sizeof(l_list));

    // Check if the memory was allocated
    if (tmp == NULL)
    {
        printf("[Linked List] Can't allocate element");
        return;
    }

    tmp->data = element;
    tmp->next_element = *input_list;
    *input_list = tmp;
}

/*
** Length of the list
*/

size_t list_length(l_list *list)
{
    size_t length = 0;

    // Iterate when there is a pointer
    while (list)
    {
        list = list->next_element;
        length++;
    }

    return length;
}

/*
** Get value from the list
*/

int list_get_value(l_list *list, int pos)
{
    // Size of the list
    int length = (int)list_length(list);

    // Check if the list really exists
    if (list == NULL)
    {
        return -1;
    }

    // Current position
    size_t current_pos = 0;

    // Calculate real position - hotfix
    size_t realpos = length - pos - 1;

    // Check OoB
    if (pos > length)
    {
        return -1;
    }

    // Iterate trought the list
    while (current_pos < realpos && list)
    {
        list = list->next_element;
        current_pos++;
    }

    return list->data;
}

/*
** Set value from the list
*/

void list_set_value(l_list *list, int pos, int value)
{
    // Size of the list
    int length = (int)list_length(list);

    // Check if the list really exists
    if (list == NULL)
    {
        return;
    }

    // Current position
    size_t current_pos = 0;

    // Calculate real position - hotfix
    size_t realpos = length - pos - 1;

    // Check OoB
    if (pos > length)
    {
        return;
    }

    // Iterate trought the list
    while (current_pos < realpos && list)
    {
        list = list->next_element;
        current_pos++;
    }

    list->data = value;
}

/*
** Free the list
*/

void list_free(l_list *list)
{
    // Head of the list
    l_list *head = list;

    // Selected node - start from the head
    l_list *current_node = list;

    // Free everything
    while ((current_node = head) != NULL)
    {
        head = head->next_element;
        free(current_node);
    }
}

/*
** Print values from list
*/

void list_print(l_list *list)
{
    // Get length
    size_t length = list_length(list);

    // Check list size
    if (length == 0)
        return;

    // Current position
    size_t current = 0;

    while (current < length)
    {
        printf("%i ", list_get_value(list, current));
        current++;
    }
    printf("\n");
}