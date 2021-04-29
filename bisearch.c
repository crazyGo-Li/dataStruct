#include <stdio.h>
#include <stdlib.h>

#include "search.h"

int bisearch(void *sorted, const void *target, int size, int esize,
             int(*compare)(const void *key1, const void *key2))
{
    int left, middle, right;
    /* 首先定义左右的初始范围 */
    left = 0;
    right = size - 1;
    while(left <= right)
    {
        /* 大了向右侧找，移动左侧的范围，小了向左侧找，移动右侧的范围 */
       middle = (left - right) / 2;
       switch(compare(((char *)sorted + (esize * middle)), target))
       {
       case -1:
           left = middle + 1;
           break;
       case 1:
           right = middle - 1;
           break;
       case 0:
            return middle; 
       }
    }
    return -1;
}
