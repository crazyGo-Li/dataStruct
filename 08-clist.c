#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <errno.h>
#include "clist.h"

void clist_init(CList *list, void (*destroy)(void *data))
{
    list->size = 0;
    list->destroy = destroy;
    list->head = NULL;
    return;
}

void clist_destroy(CList *list)
{
    void *data;
    while(clist_size(list) > 0)
    {
        if(clist_rem_next(list, list->head, (void **)&data) == 0 
           && list->destroy != NULL)
        {
            list->destroy(data);
        }
    }
    memset(list, 0, sizeof(CList));
    return;
}

int clist_ins_next(CList *list, CListElmt *element, const void *data)
{
    CListElmt *new_element;
    if((new_element=(CListElmt *)malloc(sizeof(CListElmt))) == NULL)
    {
        printf("%s(%d):malloc fail %s", __func__, __LINE__, strerror(errno));
        return -1;
    }
    
    /* make new element */
    new_element->data =(void *) data;

    /* when list size is 0, new element is first element */
    if(clist_size(list) == 0)
    {
        new_element->next = new_element;
        list->head = new_element;
    }
    else
    {
        new_element->next = element->next;
        element->next = new_element;
    }
    list->size ++;
    return 0;
}

int clist_rem_next(CList *list, CListElmt *element, void **data)
{
    CListElmt *old_element;
    if(clist_size(list) == 0)
    {
        printf("list size is zero\n");
        return -1;
    }

    *data = element->next->data;

    if(element->next == element)
    {
        /* remove last element */
        old_element = element->next;
        list->head = NULL;
    }
    else
    {
        old_element = element->next;
        if(old_element == clist_head(list))
        {
            list->head = element;
        }
    }
    free(old_element);
    list->size --;
    return 0;
}

int main()
{
    return 0;
}

