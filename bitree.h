#ifndef __BITREE_H__
#define __BITREE_H__

#include <stdlib.h>

//二叉树的节点结构
typedef struct BiTreeNode_
{
    void *data;
    struct BiTreeNode_ *left;
    struct BiTreeNode_ *right;
}BiTreeNode;

//整个二叉树的结构
typedef  struct BiTree_
{
    int size;
    int (*cpmpare) (const void *key1, const void *key2);
    void(*destroy) (void *data);
    BiTreeNode *root;
}BiTree;

//二叉树的初始化
void bitree_init(BiTree *tree, void (*destroy)(void *data));
//销毁二叉树
void bitree_destroy(BiTree *tree);
//左叶子节点插入
int bitree_ins_left(BiTree *tree, BiTreeNode *node, const void *data);
int bitree_ins_right(BiTree *tree, BiTreeNode *node, const void *data);
void bitree_rem_left(BiTree *tree, BiTreeNode *node);
void bitree_rem_right(BiTree *tree, BiTreeNode *node);
int bitree_merge(BiTree *merge, BiTree *left, BiTree *right, const void *data);

#define bitree_size(tree) ((tree)->size)
#define bitree_root(tree) ((tree)->root)
#define bitree_is_eob(node) ((node)==NULL)
#define bitree_is_leaf(node)((node)->left == NULL && (node)->right == NULL)
#define bitree_data(node) ((node)->data)
#define bitree_left(node) ((node)->left)
#define bitree_right(node) ((node)->right)


#endif
