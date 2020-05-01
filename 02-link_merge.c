#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

typedef struct node
{
    int i_data;
    struct node * next;
}LNode, *LinkList;

LinkList Create_LinkList();

int Delete_LinkList(LinkList);

void Scan_LinkList(LinkList);
void Tail_Insert_LinkLisk(LinkList, int);
void Head_Insert_LinkLisk(LinkList, int);

int main()
{
    LinkList L1 = NULL;
    LinkList L2 = NULL;

    L1 = Create_LinkList();
    L2 = Create_LinkList();
    if(L1 == NULL || L2 == NULL)
    {
        Delete_LinkList(L1);
        Delete_LinkList(L1);
        return -1;
    }

    //Tail_Insert_LinkLisk(L1, 2);
    Head_Insert_LinkLisk(L1,2);

    printf("*****************L1**************\n");
    Scan_LinkList(L1);

    printf("*****************L2**************\n");
    Scan_LinkList(L2);

    Delete_LinkList(L1);
    Delete_LinkList(L2);

    return 0;
}

void Head_Insert_LinkLisk(LinkList L, int x)
{
    LinkList tmp = NULL;

    tmp = (LinkList)malloc(sizeof(LinkList));
    if(tmp == NULL)
    {
        printf("malloc fail \n");
        return;
    }
    else
    {
        tmp->next = L;
        tmp->i_data = x;

    }

    L = tmp;
    tmp = NULL;
    return;
}

void Tail_Insert_LinkLisk(LinkList L, int x)
{
    LinkList p = L;
    LinkList tmp = NULL;

    tmp = (LinkList)malloc(sizeof(LinkList));
    if(tmp == NULL)
    {
        printf("malloc fail \n");
        return;
    }
    else
    {
        tmp->next = NULL;
        tmp->i_data = x;

    }
    if(L == NULL)
    {
        L = tmp;
        tmp = NULL;
        return;
    }
    while(p->next)
    {
        p = p->next;
    }
    p->next = tmp;
    p = NULL;
    tmp = NULL;

    return;
}

void Scan_LinkList(LinkList L)
{
    LinkList p = L;
    int i = 1;
    while(p)
    {
        printf("id: %d, data: %d\n", i, p->i_data);
        i++;
        p = p->next;
    }
    p = NULL;
}

int Delete_LinkList(LinkList L)
{
    LinkList p = NULL;
    while(L)
    {
        p = L;
        L = p->next;
        free(p);
    }
    p = NULL;
    return 0;
}

LinkList Create_LinkList()
{
    LinkList L = NULL;
    LNode *s = NULL;
    int x;
    scanf("%d", &x);
    while(x != 99)
    {
        s = (LNode *) malloc(sizeof(LinkList));
        if(NULL == s)
        {
            printf("create link fail\n");
            return NULL;
        }
        s->i_data = x;
        s->next = L;
        L = s;
        scanf("%d", &x);
    }
    return L;

}

