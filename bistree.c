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
    //如果node为空的时候直接插入到node中
    if(bitree_is_eob(*node))
    {
        if((avl_data = (AvlNode *)malloc(sizeof(AvlNode))) == NULL)
            return -1;
        avl_data->factor = AVL_BALANCED;
        avl_data->hidden = 0;
        avl_data->data = (void *)data;
        return bitree_ins_left(tree, *node, avl_data);
    }
    else
    {
        //不为空的时候判断是插入左节点还是又节点
        cmpval = tree->cpmpare(data, ((AvlNode *)bitree_data(*node))->data);
        //插入左节点的时候
        if(cmpval < 0)
        {
            //如果node的左叶子节点为空的时候直接插入到node的左子节点
            if(bitree_is_eob(bitree_left(*node)))
            {
                if((avl_data = (AvlNode *)malloc(sizeof(AvlNode))) == NULL)
                {
                    return -1;
                }
                avl_data->factor = AVL_BALANCED;
                avl_data->hidden = 0;
                avl_data->data = (void *)data;
            }
            else
            {
                //如果node 的左叶子节点不为空的时候，递归调用insert函数，参数的node改为当前node的左叶子节点
                if((retval = insert(tree, &bitree_left(*node), data, balanced)) !=0 )
                {
                    return retval;
                }
            }

            //插入完成后进行旋转和平衡因子的更新
            if(!(*balanced))
            {
                switch (((AvlNode *)bitree_data(*node))->factor)
                {
                    //执行LR或者LL旋转
                    case AVL_LFT_HEAVY:
                        rotate_left(node);
                        *balanced = 1;
                        break;
                    case AVL_BALANCED:
                        ((AvlNode *)bitree_data(*node))->factor = AVL_LFT_HEAVY;
                        break;
                    case AVL_RGT_HEAVY:
                        ((AvlNode *)bitree_data(*node))->factor = AVL_BALANCED;
                        *balanced = 1;
                        break;

                }
            }
        }
        //需要向node的右叶子节点插入数据的时候
        else if(cmpval > 0)
        {
            if(bitree_is_eob(bitree_right(*node)))
            {
                if((avl_data = (AvlNode *)malloc(sizeof(AvlNode))) == NULL)
                    return -1;
                avl_data->data = (void *)data;
                avl_data->factor = AVL_BALANCED;
                avl_data->hidden = 0;
                if(bitree_ins_right(tree, *node, avl_data) != 0)
                    return -1;
                *balanced = 0;
            }
            else
            {
                if((retval = insert(tree, &bitree_right(*node), data, balanced)) != 0)
                {
                    return retval;
                }
            }

            if(!(*balanced))
            {
                switch(((AvlNode *)bitree_data(*node))->factor)
                {
                    case AVL_LFT_HEAVY:
                        ((AvlNode *)bitree_data(*node))->factor = AVL_BALANCED;
                        *balanced = 1;
                        break;
                    case AVL_BALANCED:
                        ((AvlNode *)bitree_data(*node))->factor = AVL_RGT_HEAVY;
                        break;
                    case AVL_RGT_HEAVY:
                        rotate_right(node);
                        *balanced = 1;
                }
            }
        }
        //如果数据已经存在，则判断数据是否被惰性删除了，删除的话恢复，存在的话报错
        else
        {
            if(!((AvlNode *)bitree_data(*node))->hidden)
                return 1;
            else
            {
                //如果数据已经存在，则直接进行替换
                if(tree->destroy != NULL)
                {
                    tree->destroy(((AvlNode *)bitree_data(*node))->data);
                }
                ((AvlNode *)bitree_data(*node))->data = (void *)data;
                ((AvlNode *)bitree_data(*node))->hidden = 0;
                *balanced = 1;
            }
        }
    }
    return 0;
}


static int hide(BisTree *tree, BiTreeNode *node, const void *data)
{
    int cmpval, retval;

    //当需要删除的节点是空的时候报错
    if(bitree_is_eob(node))
    {
        return -1;
    }

    cmpval = tree->cpmpare(data, ((AvlNode *)bitree_data(node))->data);
    if(cmpval < 0)
    {
        retval = hide(tree, bitree_left(node), data);
    }
    else if(cmpval > 0)
    {
        retval = hide(tree, bitree_right(node), data);
    }
    else
    {
        ((AvlNode *)bitree_data(node))->hidden = 1;
        retval = 0;
    }
    return retval;
}

//进行数据查询
static int lookup(BisTree *tree, BiTreeNode *node, void **data)
{
    int cmpval, retval;
    
    //当数据不存在的时候直接退出
    if(bitree_is_eob(node))
    {
        return -1;
    }

    cmpval = tree->cpmpare(data, ((AvlNode *)bitree_data(node))->data);
    if(cmpval < 0)
    {
        retval = lookup(tree, bitree_left(node), data);
    }
    else if(cmpval > 0)
    {
        retval = lookup(tree, bitree_right(node), data);
    }
    else
    {
        if(!((AvlNode *)bitree_data(node))->hidden)
        {
            *data = (void *)((AvlNode *)bitree_data(node))->data;
            retval = 0;
        }
        else
        {
            return -1;
        }
    }
    return retval;
}

void bistree_init(BisTree *tree, int (*compare)(const void  *key1, const void *key2),
                  void (*destroy)(void *data))
{
    bitree_init(tree, destroy);
    tree->cpmpare = compare;
    return;
}

void destroy(BisTree *tree)
{
    destroy_left(tree, NULL);
    memset(tree, 0, sizeof(BisTree));
    return;
}

int bistree_insert(BisTree *tree, const void *data)
{
    int balanced = 0;
    return insert(tree, &bitree_root(tree), data, &balanced);
}

int bistree_remove(BisTree *tree, const void *data)
{
    return hide(tree, bitree_root(tree), data);
}

int bistree_lookup(BisTree *tree, void **data)
{
    return lookup(tree, bitree_root(tree), data);
}
