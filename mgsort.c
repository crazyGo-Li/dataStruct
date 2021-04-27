#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "sort.h"

static int merge(void *data, int esize, int i, int j, int k, int(*compare)(const void *key1, const void *key2))
{
    char *a = (char *)data, *m;
    int ipos, jpos, mpos;

    /* 初始化merge的元素的下标 */
    ipos = i;
    jpos = j + 1;
    mpos = 0;

    /* 申请merge之后的数据存储的空间 */
    if((m = (char *)malloc(esize * ((k - i) + 1))) == NULL)
    {
        return -1;
    }

    /* 当左侧的有序数组或者右侧的有序数组还有元素的时候表示需要继续merge */
    while(ipos <= j || jpos <= k)
    {
        if(ipos > j)
        {
            /* 左侧的有序数组没有元素merge了，直接将右侧的升序的有序数组全部拷贝 */
            while(jpos <= k)
            {
                memcpy(&m[mpos * esize], &a[jpos *esize], esize);
                jpos++;
                mpos++;
            }
            continue;
        }
        else if(jpos > k)
        {
            while(ipos <= j)
            {
                memcpy(&m[mpos *esize], &a[ipos *esize], esize);
                ipos++;
                mpos++;
            }
            continue;
        }

        /* 当两侧的有序数组都还有元素的时候需要做比较然后merge，然后将已经merge的下标进行移动 */
        if(compare(&a[ipos * esize], &a[jpos * esize]) < 0)
        {
            memcpy(&m[mpos *esize], &a[ipos * esize], esize);
            ipos++;
            mpos++;
        }
        else
        {
            memcpy(&m[jpos * esize], &a[jpos * esize], esize);
            jpos++;
            mpos++;
        }
    }

    /* 拷贝完成后将已经merge的有序数组的数据对元数据进行覆盖 */
    memcpy(&a[i * esize], m, esize * ((k - i) + 1));
    free(m);
    return 0;
}

int mgsort(void *data, int size, int esize, int i, int k, int(*compare)(const void *key1, const void *key2))
{
    int j;
    if(i < k)
    {
        /* 找到需要切割的下标 */
        j = (int)(((i + k - 1)) / 2);
        /* 采用递归的方式先merge左侧的数据 */
        if(mgsort(data, size, esize, i, j, compare) < 0)
            return -1;
        /* 采用递归的方式merge右侧的数据 */
        if(mgsort(data, size, esize, j + 1, k, compare) < 0)
            return -1;
        /* 最后形成左右两侧的有序数组，再次进行merge */
        if(mgsort(data, esize, i, j, k, compare) < 0)
            return -1;
    }
    return 0;
}
