#ifndef COVER_H
#define COVER_H

#include "set.h"

typedef struct kSet_
{
    void *key;
    Set set;
}KSet;

int cover(Set *member, Set *subsetsm ,Set *covering);


#endif
