#ifndef CHTBL_H
#define CHTBL_H

#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include "list.h"

#define DEBUG_MSG printf("%s(%d): %s\n", __func__, __LINE__, strerror(errno))

typedef struct CHTbl_
{
    int buckets;
    int (*h)(const void *key);
    int (*match)(const void *key1, const void *key2);
    void (*destroy)(void *data);
    int size;
    List *table;
}CHTbl;

int chtbl_init(CHTbl *htbl, int buckets, int (*h)(const void *key),
               int (*match)(const void *key1, const void *key2),
               void (*destroy)(void *data));

void chtbl_destroy(CHTbl *htbl);
int chtbl_insert(CHTbl *htbl, const void *data);
int chtbl_remove(CHTbl *htbl, void **data);
int chtbl_lookup(const CHTbl *chtbl, void **data);
#define chtbl_size(htbl) ((htbl)->size)


#endif
