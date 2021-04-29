#ifndef __SEARCH_H__
#define __SEARCH_H__

int bisearch(void *sorted, const void *target, int size, int esize, 
             int(*compare)(const void *key1, const void *key2));

#endif
