#ifndef DLIST_H
#define DLIST_H

#include <stdlib.h>
#include <string.h>
#include <errno.h>

#define DEBUG_MSG printf("%s(%d): %s \n", __func__, __LINE__, strerror(errno))

/* double link element */
typedef struct DListElm_
{
    void *data;
    struct DListElm_ *prev;
    struct DListElm_ *next;
}DListElm;

typedef struct DList_
{
    int size;
    int (*match)(const void *key1, const void *key2);
    void (*destroy)(void *data);
    DListElm *head;
    DListElm *tail;
}DList;

void dlist_init(DList *list, void (*destroy)(void*data));
void dlist_destroy(DList *list);
int dlist_ins_next(DList *list, DListElm *element, const void *data);
int dlist_ins_prev(DList *list, DListElm *element, const void *data);
int dlist_remove(DList *list, DListElm *element, void **data);

#define dlist_size(list) ((list)->size)
#define dlist_head(list) ((list)->head)
#define dlist_tail(list) ((list)->tail)
#define dlist_is_head(element) ((element)->prev == NULL ? 1:0)
#define dlist_is_tail(element) ((element)->next == NULL ? 1:0)
#define dlist_data(element) ((element)->data)
#define dlist_next(element) ((element)->next)
#define dlist_prev(element) ((element)->prev)



#endif
