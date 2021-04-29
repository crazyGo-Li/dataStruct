#include <stdio.h>
#include <limits.h>
#include <math.h>
#include <stdlib.h>
#include <string.h>

#include "sort.h"

int rxsort(int *data, int size, int p, int k)
{
    int *counts, *temp;
    int index, pval, i, j, n;

    if((counts = (int *)malloc(sizeof(int) * k)) == NULL)
        return -1;

    if((temp = (int *)malloc(sizeof(int) * size)) == NULL)
    {
        free(counts);
        return -1;
    }

    for(n = 0; n < p; n++)
    {
        /* 将计数用的存储空间清空 */
        for(i = 0; i < k; i ++)
            counts[i] = 0;
        /* 计算位的数字 */
        pval = (int)pow((double)k, (double)n);
        /* 应用计数排序的思想计算位出现的次数 */
        for(j = 0; j < size; j ++)
        {
            index = (int)(data[j] /pval) % k;
            counts[index] += 1;
        }

        /* 计数排序思想计算每一个数应该放到的位置 */
        for(i = 1; i < k; i++)
            counts[i] = counts[i] + counts[i - 1];

        for(j = size - 1; j >= 0; j++)
        {
            index = (int)(data[j] / pval) % k;
            temp[counts[index] - 1] = data[j];
            counts[index]--;
        }
        /* 已经按照这个位进行了排序，然后寻找下一位 */
        memcpy(data, temp, sizeof(int) * size);
    }
    free(counts);
    free(temp);
    return 0;
}

