#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>

typedef struct Polynode
{
    int coef;
    int eap;
    Polynode *next;
} PolyNode,*PolyList;

PolyList polycreate();
void polydestroy(PolyList);

int main()
{
    return 0;
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
