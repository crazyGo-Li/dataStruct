#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include "sort.h"

int ctsort(int *data, int size, int k)
{
    int *counts, *temp;
    int i, j;

    /* 为保存计数的数组申请内存 */
    if((counts = (int *)malloc(sizeof(int) * k)) == NULL)
        return -1;

    /* 为排序的结果申请内存 */
    if((temp = (int *)malloc(sizeof(int) * size)) == NULL)
    {
        free(counts);
        return -1;
    }

    for(i = 0; i < k; i++)
        counts[i] = 0;

    /* 将每个数出现的次数放置到以此数为下表的数组中 */
    for(j = 0; j < size; j++)
        counts[data[j]] = counts[data[j]] + 1;

    /* 将出现的次数和前一次出现的次数相加 */
    for(i = 1; i < k; i ++)
        counts[i] = counts[i] + counts[i - 1];

    for(j = size; j >= 0; j--)
    {
        temp[counts[data[j]] - 1] = data[j];
        counts[data[j]] = counts[data[j]] - 1;
    }

    memcpy(data, temp, sizeof(int) * size);
    free(counts);
    free(temp);
    return 0;
}
