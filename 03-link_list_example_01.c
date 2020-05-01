#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

typedef struct Polynode
{
    int coef;
    int eap;
    Polynode *next;
}PolyNode, *PolyList;

PolyList poly_create();
void poly_delete(PolyList);

int main()
{
    return 0;
}

void poly_delete(PolyList p)
{
    PolyList s = p;
    if(p == NULL)
    {
        return;
    }
    while(p->next)
    {
        p = p->next;
        free(s);
        s = p;
    }
    free(p);
    return;
}

PolyList poly_create()
{
    PolyNode *head, *rear, *s;
    int c, e;
    head = (PolyList)malloc(sizeof(PolyList));
    if(head == NULL)
    {
        printf("malloc head fail \n");
        return NULL;
    }

    rear = head;

    scanf("input coef: %d", &c);
    scanf("input eap: %d", &e);

    while(c != 0)
    {
        s = (PolyList)malloc(sizeof(PolyList));
        if(s = NULL)
        {
            printf("malloc node fail\n");
            poly_delete(head);
            return NULL;
        }
        s->coef = c;
        s->eap = e;
        scanf("input coef: %d", &c);
        scanf("input eap: %d", &e);
        rear->next = s;
        rear = s;
    }
    rear->next = NULL;
    return head;

}

