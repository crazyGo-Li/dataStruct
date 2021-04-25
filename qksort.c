#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include "sort.h"

//先确定比较的方式
static int compare_int(const void *int1, const void *int2)
{
    if(*(const int *)int1 > *(const int *)int2)
    {
        return 1;
    }
    else if(*(const int *)int1 < *(const int *)int2)
    {
        return -1;
    }
    else
    {
        return 0;
    }
}

/* 将一个数组data，设置一个数作为切割点，分为左右两份，其中左侧的数小于切割点，右侧的数大于切割 */
static int partition(void *data, int esize, int i, int k, int(*compare)(const void *key1, const void *key2))
{
    char *a = (char *)data;
    void *pval, *temp;  //pval 作为一个切割点保存切割点的数据，temp作为交换数据的缓冲区保存需要交换的数据
    int r[3];

    if((pval = (void *)malloc(esize)) == NULL)
        return -1;
    if((temp = (void *)malloc(esize)) == NULL)
    {
        free(pval);
        return -1;
    }

    /* 通过随机三个数字，然后取中间的数字的方式获取切割点的数据 */
    r[0] = (rand() % (k - i + 1)) + i;
    r[1] = (rand() % (k - i + 1)) + i;
    r[2] = (rand() % (k - i + 1)) + i;
    issort(r, 3, sizeof(int), compare_int);
    memcpy(pval, &a[r[1] * esize], esize);

    i--;
    k++;

    while(1){
        /* 先找到右侧小于等于切割点的数据 */
        do{
            k--;
        }while(compare(&a[k * esize], pval) > 0);
        
        /* 后找到左侧大于等于切割点的数据 */
        do{
            i++;
        }while(compare(&a[i * esize], pval) < 0);

        /* 当i >= k的时候表示已经遍历结束 */
        if(i >= k)
        {
            break;
        }
        else
        {
            /* 没有遍历结束的时候将已经找到的错误的数据交换，然后重复上述操作 */
            memcpy(temp, &a[i * esize], esize);
            memcpy(&a[i * esize], &a[k * esize], esize);
            memcpy(&a[k * esize], temp, esize);
        }
    }
    free(pval);
    free(temp);

    /* 返回切割的位置，为了下一次的回调提供依据 */
    return k;
}

/* data    表示指向一个数组 */
/* size    表示数组的大小 */
/* esize   表示数组中每个元素的大小 */
/* i       表示数组的起始位置 */
/* k       表示数组的结束位置 */
int qksort(void *data, int size, int esize, int i, int k, int(*compare)(const void *key1, const void *key2))
{
    int j;
    while(i < k)
    {
        /* 牛逼 */
        if((j = partition(data, esize, i, k, compare)) < 0)
        {
            return -1;
        }

        if(qksort(data, size, esize, i, j, compare) < 0)
        {
            return -1;
        }
        i = j + 1;
    }
    return 0;
}
