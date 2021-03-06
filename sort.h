#ifndef __SORT_H__
#define __SORT_H__

int issort(void *data, int size, int esize, int (*compare)(const void *key1, const void *key2));
int qksort(void *data, int size, int esize, int i , int k, int (*compare)(const void *key1, const void *key2));
int ctsort(int *data, int size, int k);

#endif
