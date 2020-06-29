#include <stdio.h>
#include "chtbl.h"
#include "list.h"

int chtbl_init(CHTbl *htbl, int buckets, int (*h)(const void *key),
               int (*match)(const void *key1, const void *key2),
               void (*destroy)(void *data))
{
    int i;
    if((htbl->table = (List *)malloc(buckets * sizeof(List))) == NULL)
    {
        DEBUG_MSG;
        return -1;
    }
    htbl->buckets = buckets;
    for(i = 0; i < htbl->buckets; i++)
    {
        list_init(&htbl->table[i], destroy);
    }
    htbl->h = h;
    htbl->match = match;
    htbl->destroy = destroy;
    htbl->size = 0;

    return 0;
}

