#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <error.h>

#define MAXSIZE 100

typedef struct 
{
    char data[MAXSIZE];
    int top;
}seqstack;

seqstack * init_seqstack();
int empty_seqstack(seqstack *);
int push_seqstack(seqstack *, char);
int pop_seqstack(seqstack *, char *);
char top_seqstack(seqstack *);

int main()
{
    return 0;
}


char top_seqstack(seqstack *s)
{
    char x = '\0';
    if(empty_seqstack(s) == 1)
    {
        return x;
    }
    else
    {
        return s->data[s->top];
    }
}

int pop_seqstack(seqstack *s, char *x)
{
    if(empty_seqstack(s) == 1)
    {
        return 1;
    }
    else
    {
        *x = s->data[s->top];
        s->top--;
        return 0;
    }

}

int push_seqstack(seqstack *s, char x)
{
    if(s->top == (MAXSIZE -1))
    {
        return 1;
    }
    else
    {
        s->top++;
        s->data[s->top] = x;
        return 0;
    }
}

int empty_seqstack(seqstack *s)
{
    if(s->top == -1)
        return 1;
    else
        return 0;
}

seqstack * init_seqstack()
{
    seqstack * s;
    s = (seqstack *)malloc(sizeof(seqstack));
    s->top = -1;
    return s;
}

