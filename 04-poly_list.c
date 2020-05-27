#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>

typedef struct Polynode
{
    int coef;
    int eap;
    struct Polynode *next;
} PolyNode,*PolyList;

PolyList polycreate();
void polydestroy(PolyList);
void polyscan(PolyList);
void addpoly(PolyList, PolyList);

int main()
{
    return 0;
}

void addpoly(PolyList polya, PolyList polyb)
{
    PolyList p, q, tail, s;
    int sum;
    p = polya->next;
    q = polyb->next;
    tail = polya;
    while(p != NULL && q != NULL)
    {
        if(p->eap < q->eap)
        {
            tail->next = p;
            tail = p;
            p = p->next;
        }
        else if(p->eap > q->eap)
        {
            tail->next = q;
            tail = q;
            q = q->next;
        }
        else
        {
            sum = p->coef + q->coef;
            if(sum != 0)
            {
                p->coef = sum;
                tail->next = p;
                tail = p;
                s = q;
                q = q->next;
                free(s);
            }
            else
            {
                s = p;
                p = p->next;
                free(s);
                s = q;
                q = q->next;
                free(s);
            }

        }
    }

}

void polyscan(PolyList head)
{
    PolyList tmp_node;
    tmp_node = head;
    while(tmp_node->next)
    {
        tmp_node= tmp_node->next;
        printf("coef: %d, eap: %d\n", tmp_node->coef, tmp_node->eap);
    }
    tmp_node = NULL;
    return;
}

PolyList polycreate()
{
    PolyNode *head, *rear, *s;
    int c, e;
    head = (PolyList)malloc(sizeof(PolyNode));
    if(head == NULL)
    {
        printf("malloc head fail %s\n", strerror(errno));
        return NULL;
    }
    head->next = NULL;
    rear = head;
    printf("input coef and eap, end coed = 0: ");
    scanf("%d %d", &c, &e);
    while(c != 0)
    {
       s = (PolyList)malloc(sizeof(PolyNode));
       if(s == NULL)
       {
            printf("malloc s fail %s\n", strerror(errno));
            polydestroy(head);
            return NULL;
       }

       s->coef = c;
       s->eap = e;
       rear->next = s;
       rear = s;
       printf("input coef and eap, end coed = 0: ");
       scanf("%d %d", &c, &e);

    }
    rear->next = NULL;
    return head;
}

void polydestroy(PolyList head)
{
    PolyNode * tmp = head;
    while(tmp)
    {
        tmp = head->next;
        free(head);
        head = tmp;
    }
    return;
}
