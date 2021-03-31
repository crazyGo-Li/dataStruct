#include <stdio.h>
#include <string.h>
#include "bistree.h"

/* 树实现的核心思想就是递归 */

static void destroy_right(BisTree *tree, BiTreeNode *node);

static void rotate_left(BiTreeNode **node)
{
    BiTreeNode *left, *grandchild;
    
    left = bitree_left(*node);
        
    if(((AvlNode *)bitree_data(left))->factor == AVL_LFT_HEAVY)
    {
        /* 执行LL旋转 */
        //1 将node节点指向左孩子节点的叶子节点
        bitree_left(*node) = bitree_right(left);
        //2 左孩子节点的叶子节点替换为node
        bitree_right(left) = *node;
        // 设置平衡因子
        ((AvlNode *)bitree_data(*node))->factor = AVL_BALANCED;
        ((AvlNode *)bitree_data(left))->factor = AVL_BALANCED;
        //3 node和左子节点进行替换
        *node = left;
    }
    else
    {
        //执行LR旋转
        //找到grandchild
        grandchild = bitree_right(left);
        //单独将left进行提取
        bitree_right(left) = bitree_left(grandchild);
        //grandchild的left指向left
        bitree_left(grandchild) = left;
        //node的left指向grandchild的right
        bitree_left(*node) = bitree_right(grandchild);
        //node替换为grandchild
        bitree_right(grandchild) = *node;

        //重建平衡因子
        switch(((AvlNode *)(bitree_data(grandchild)))->factor)
        {
        case AVL_LFT_HEAVY:
            ((AvlNode *)bitree_data(*node))->factor = AVL_LFT_HEAVY;
            ((AvlNode *)bitree_data(left))->factor = AVL_BALANCED;
            break;
        case AVL_BALANCED:
            ((AvlNode *)bitree_data(*node))->factor = AVL_BALANCED;
            ((AvlNode *)bitree_data(grandchild))->factor = AVL_BALANCED;
            break;
        case AVL_RGT_HEAVY:
            ((AvlNode *)bitree_data(*node))->factor = AVL_BALANCED;
            ((AvlNode *)bitree_data(grandchild))->factor = AVL_RGT_HEAVY;
            break;
        }
        ((AvlNode *)bitree_data(grandchild))->factor = AVL_BALANCED;
        *node = grandchild;
    }
    return;
}

static void rotate_right(BiTreeNode **node)
{
    BiTreeNode *right, *grandchild;
    right  = bitree_right(*node);
    
    if(((AvlNode *)bitree_data(right))->factor == AVL_RGT_HEAVY)
    {
        // perform an rr rotation
        bitree_right(*node)= bitree_left(right);
        bitree_left(*node) = *node;
        ((AvlNode *)bitree_data(*node))->factor = AVL_BALANCED;
        ((AvlNode *)bitree_data(*node))->factor = AVL_BALANCED;
        *node = right;
    }
    else
    {
        //perform an RL rotation
        grandchild = bitree_right(grandchild);
        bitree_left(right) = bitree_right(grandchild);
        bitree_right(grandchild) = right;
        bitree_right(*node) = bitree_left(grandchild);
        bitree_left(grandchild) = *node;

        switch (((AvlNode *)(bitree_data(*node)))->factor)
        {
        case AVL_LFT_HEAVY:
            ((AvlNode *)bitree_data(*node))->factor = AVL_BALANCED;
            ((AvlNode *)bitree_data(right))->factor = AVL_RGT_HEAVY;
            break;
        case AVL_BALANCED:
            ((AvlNode *)bitree_data(*node))->factor = AVL_BALANCED;
            ((AvlNode *)bitree_data(right))->factor = AVL_BALANCED;
            break;
        case AVL_RGT_HEAVY:
            ((AvlNode *)bitree_data(*node))->factor = AVL_LFT_HEAVY;
            ((AvlNode *)bitree_data(right))->factor = AVL_BALANCED;
            break;
        }
        ((AvlNode *)bitree_data(grandchild))->factor = AVL_BALANCED;
        *node = grandchild;
    }
    return;
}

static void destroy_left(BisTree *tree, BiTreeNode *node)
{
    BiTreeNode **position;

    if(bitree_size(tree) == 0)
    {
        return;
    }

    if(node == NULL)
    {
        position = &tree->root;
    }
    else
    {
        position = &node->left;
    }

    if(*position != NULL)
    {
        destroy_left(tree, *position);
        destroy_right(tree, *position);
        if(tree->destroy != NULL)
        {
            tree->destroy(((AvlNode *)(*position)->data)->data);
        }
        free((*position)->data);
        free(*position);
        *position = NULL;
        tree->size--;
    }
    return;
}

static void destroy_rigth(BisTree *tree, BiTreeNode *node)
{
    BiTreeNode **position;

    if(bitree_size(tree) == 0)
        return;

    if(node == NULL)
        position= &tree->root;
    else
        position = &node->right;

    if(*position != NULL)
    {
        destroy_left(tree, *position);
        destroy_right(tree, *position);
        if(tree->destroy != NULL)
        {
            tree->destroy(((AvlNode *)(*position)->data)->data);
        }
        free((*position)->data);
        free(*position);
        tree->size--;
    }
    return;
}

static int insert(BisTree *tree, BiTreeNode **node, const void *data, int *balanced)
{
    AvlNode *avl_data;
    int cmpval, retval;
    if(bitree_is_eob(*node))
    {
        if((avl_data = (AvlNode *)malloc(sizeof(AvlNode))) == NULL)
            return -1;
        avl_data->factor = AVL_BALANCED;
        avl_data->hidden = 0;
        avl_data->data = (void *)data;
        return bitree_ins_left(tree, *node, avl_data);
    }
}
