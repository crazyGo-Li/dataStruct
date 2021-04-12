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
