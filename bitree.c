#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "bitree.h"

void bitree_init(BiTree *tree, void (*destroy)(void *data))
{
    tree->size = 0;
    tree->destroy = destroy;
    tree->root = NULL;
    return;
}

void bitree_destroy(BiTree *tree)
{
    bitree_rem_left(tree, NULL);
    memset(tree, 0, sizeof(BiTree));
    return;
}

int bitree_ins_left(BiTree *tree, BiTreeNode *node, const void *data)
{
    BiTreeNode *new_node, **position;
    if(node == NULL)
    {
        //node为空的时候表示此次插入为根节点
        if(bitree_size(tree) > 0)
        {
            return -1;
        }
        position = &tree->root;
    }
    else
    {
        //当节点不为空的时候需要对节点的左侧插入，此时左侧不为空表述数据冲突退出
        if(bitree_left(node) != NULL)
            return -1;
        position = &node->left;
    }
    new_node = (BiTreeNode *)malloc(sizeof(BiTreeNode));
    if(new_node == NULL)
    {
        return -1;
    }
    new_node->data = (void *)data;
    new_node->left = NULL;
    new_node->right = NULL;
    *position = new_node;
    tree->size++;
    return 0;
}

int bitree_ins_right(BiTree *tree, BiTreeNode *node, const void *data)
{
    BiTreeNode *new_node, **position;
    if(node == NULL)
    {
        if(bitree_size(tree) > 0)
            return -1;
        position = &tree->root;
    }
    else
    {
        if(bitree_right(node) != NULL)
            return -1;
        position = &node->right;
    }

    new_node = (BiTreeNode *)malloc(sizeof(BiTreeNode));
    if(new_node == NULL)
        return -1;
    new_node->data = (void *)data;
    new_node->left = NULL;
    new_node->right = NULL;
    *position = new_node;
    tree->size++;
    return 0;
}

void bitree_rem_left(BiTree *tree, BiTreeNode *node)
{
    BiTreeNode **position;
    if(bitree_size(tree) == 0)
        return;
    if(node == NULL)
        position = &tree->root;
    else
        position = &node->left;

    //采用递归的方式将各个节点的叶子节点删除
    if(*position != NULL)
    {
        bitree_rem_left(tree, *position);
        bitree_rem_right(tree, *position);
        if(tree->destroy != NULL)
        {
            tree->destroy((*position)->data);
        }
        free(*position);
        *position = NULL;
        tree->size--;
    }
    return;
}

void bitree_rem_right(BiTree *tree, BiTreeNode *node)
{
    BiTreeNode **position;
    if(bitree_size(tree) == 0)
        return;
    if(node == NULL)
        position = &tree->root;
    else
        position = &node->right;

    if(*position != NULL)
    {
        bitree_rem_left(tree, *position);
        bitree_rem_right(tree, *position);
        if(tree->destroy != NULL)
        {
            tree->destroy((*position)->data);
        }
        free(*position);
        tree->size--;
    }
    return;
}

int bitree_merge(BiTree *merge, BiTree *left, BiTree *right, const void *data)
{
    bitree_init(merge, left->destroy);
    if(bitree_ins_left(merge, NULL, data) != 0)
    {
        bitree_destroy(merge);
        return -1;
    }

    bitree_root(merge)->left = bitree_root(left);
    bitree_root(merge)->right = bitree_root(right);
    merge->size = bitree_size(left) + bitree_size(right);
    left->root = NULL;
    left->size = 0;
    right->root = NULL;
    left->size = 0;
    return 0;
}
