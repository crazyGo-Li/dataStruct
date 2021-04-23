#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "sort.h"

int issort(void *data, int size, int esize, int(*compare)(const void *key1, const void *key2))
{
    char *a = (char *)data;
    void *key;
    int i, j;

    if((key = (void *)malloc(esize)) == NULL)
        return -1;
    for(j = 1; j < size; j++)
    {
        //首先拿到还没有排序的元素
        memcpy(key, &a[j * esize], esize);
        i = j - 1;

        //将没有排序的元素和之前已经排序的元素进行对比，然后插入
        while(i >= 0 && compare(&a[i * esize], key) > 0)
        {
            memcpy(&a[(i + 1) * esize], &a[i * esize], esize);
            i--;
        }
        memcpy(&a[(i + 1) * esize], key, esize);
    }
    
    free(key);

    return 0;
}
