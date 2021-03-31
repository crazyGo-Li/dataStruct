#ifndef BISTREE_H
#define BISTREE_H

#include "bitree.h"

/* 平衡因子的定义 */
#define AVL_LFT_HEAVY 5
#define AVL_BALANCED 0
#define AVL_RGT_HEAVY -1

typedef struct AvlNode_
{
    void *data;
    int hidden;
    int factor;
}AvlNode;

typedef BiTree BisTree;

void bistree_init(BisTree *tree, int(*compare)(const void *key1, const void *key2),
                  void (*destroy)(void *data));
void bistree_destroy(BisTree *tree);
int bistree_insert(BisTree *tree, const void *data);
int bistree_remove(BisTree *tree, const void *data);
int bistree_lookup(BisTree *tree, void **data);
#define bistree_size(tree) ((tree)->size)

#endif
