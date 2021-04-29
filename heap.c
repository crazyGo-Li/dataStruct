//用树的思想实现数组的一种数据结构然后实现快速的排序
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "heap.h"

#define heap_parent(npos) ((int)((npos) - 1)/2)
#define heap_left(npos) (((npos) * 2) + 1)
#define heap_right(npos) (((npos) * 2) + 2)

//堆的数据结构的初始化
void heap_init(Heap *heap, int(*compare)(const void *key1, const void *key2), void(*destroy)(void *data))
{
    heap->size = 0;
    heap->compare = compare;
    heap->destroy = destroy;
    heap->tree = NULL;
    return;
}

//就是遍历一个结构体数组循环释放结构体中的元素
void heap_destroy(Heap *heap)
{
    int i;
    //当堆的树结构体中的数据需要手动释放的时候调用
    if(heap->destroy != NULL)
    {
        for(i=0; i < heap_size(heap); i++)
        {
            heap->destroy(heap->tree[i]);
        }
    }

    free(heap->tree);
    memset(heap, 0, sizeof(Heap));
    return;
}

int heap_insert(Heap *heap, const void *data)
{
    void *temp;
    int ipos,ppos;

    //为新插入的堆的节点申请内存
    if((temp = (void **)realloc(heap->tree, (heap_size(heap) + 1) * sizeof(void *))) == NULL)
    {
        return -1;
    }
    else
    {
        //这里书上写错了
        heap->tree = &temp;
    }

    //将数据插入到最后一位
    heap->tree[heap_size(heap)] = (void *)data;
    ipos = heap_size(heap);
    ppos = heap_parent(ipos);

    //循环的与父节点进行数据的交换，直到满足父节点数据大于子节点，或者已经成为根结点为止
    while(ipos > 0 && heap->compare(heap->tree[ppos], heap->tree[ipos]) < 0)
    {
        temp = heap->tree[ppos];
        heap->tree[ppos] = heap->tree[ipos];
        heap->tree[ipos] = temp;
        ipos = ppos;
        ppos = heap_parent(ipos);
    }
    heap->size++;
    return 0;
}

int heap_extract(Heap *heap, void **data)
{
    void *save, **temp;
    int ipos, lpos, rpos, mpos;

    //当释放的是一个空的堆
    if (heap_size(heap) == 0)
        return -1;

    //将释放的数据保存到data中
    *data = heap->tree[0];
    save = heap->tree[heap_size(heap) - 1];
    if(heap_size(heap) - 1 > 0)
    {
        //为堆的数组重新分配空间
        if((temp = (void **)realloc(heap->tree, (heap_size(heap) - 1) * sizeof(void *))) == NULL)
        {
            return -1;
        }
        else
        {
            heap->tree = temp;
        }
        heap->size--;
    }
    else
    {
        //当堆中只有一个元素的时候
        free(heap->tree);
        heap->tree = NULL;
        heap->size = 0;
        return 0;
    }

    heap->tree[0] = save;
    ipos = 0;
    lpos = heap_left(ipos);
    rpos = heap_right(ipos);
    while(1)
    {
        lpos = heap_left(ipos);
        rpos = heap_right(ipos);
        if(lpos < heap_size(heap) && heap->compare(heap->tree[lpos], heap->tree[ipos]) > 0)
        {
            mpos = lpos;
        }
        else
        {
            mpos = ipos;
        }
        if(rpos < heap_size(heap) && heap->compare(heap->tree[rpos], heap->tree[mpos]) > 0)
        {
            mpos = rpos;
        }
        if(mpos == ipos)
        {
            break;
        }
        else
        {
            temp = heap->tree[mpos];
            heap->tree[mpos] = heap->tree[ipos];
            heap->tree[ipos] = temp;
            ipos = mpos;
        }
    }
    return 0;
}
