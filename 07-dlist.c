#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "dlist.h"

void dlist_init(DList *list, void (*destroy)(void *data))
{
    list->size = 0;
    list->head = NULL;
    list->tail = NULL;
    list->destroy = destroy;
    return;
}

void dlist_destroy(DList *list)
{
    void *data;
    while(dlist_size(list) > 0)
    {
        if(dlist_remove(list, dlist_tail(list), (void **)&data) == 0
           && list->destroy != NULL)
        {
            list->destroy(data);
        }
    }
    memset(list, 0, sizeof(DList));
    return;
}

int dlist_ins_next(DList *list, DListElm *element, const void *data)
{
    DListElm *new_element;

    /* can not insert null to list */
    if(element == NULL && dlist_size(list) != 0)
    {
        return -1;
    }

    /* allocate storage for new element */
    new_element = (DListElm *)malloc(sizeof(DListElm));
    if(NULL == new_element)
    {
        return -1;
    }

    /* insert new element to list */
    new_element->data = (void *)data;
    if(dlist_size(list) == 0)
    {
        list->head = new_element;
        list->head->prev = NULL;
        list->head->next = NULL;
        list->tail = new_element;
    }
    else
    {
        new_element->next = element->next;
        new_element->prev = element;
        if(element->next == NULL)
        {
            list->tail = new_element;
        }
        else
        {
            element->next->prev = new_element;
        }
        element->next = new_element;
    }
    list->size++;
    return 0;
}
