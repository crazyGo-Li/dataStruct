#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include "list.h"
#include "set.h"

void set_init(Set *set, int (*match)(const void *key1, const void *key2),
              void(*destroy)(void *data))
{
    list_init(set, destroy);
    set->match = match;
    return;
}

int set_insert(Set *set, const void *data)
{
    if(set_is_member(set, data))
    {
        return 1;
    }
    return list_ins_next(set, list_tail(set), data);
    return 0;
}

int set_remove(Set *set, void **data)
{
    ListElmt *member, *prev;
    prev = NULL;
    for(member = list_head(set); member != NULL; member = list_next(member))
    {
        if(set->match(*data, list_data(member)))
            break;
        prev = member;
    }

    if(member == NULL)
    {
        return -1;
    }

    return list_rem_next(set, prev, data);
}

int set_union(Set *setu, const Set *set1, const Set *set2)
{
    ListElmt *member;
    void *data;

    set_init(setu, set1->match, NULL);
    for(member = list_head(set1); member != NULL; member =list_next(member))
    {
        data = list_data(member);
        if(list_ins_next(setu, list_tail(setu), data) != 0)
        {
            set_destroy(setu);
            return -1;
        }
    }

    for(member = list_head(set2); member != NULL; member = list_next(member))
    {
        if(set_is_member(set1, list_data(member)))
        {
            continue;
        }
        else
        {
            data = list_data(member);
            if(list_ins_next(setu, list_tail(setu), data) != 0)
            {
                set_destroy(setu);
                return -1;
            }
        }
    }

    return 0;
}

int set_intersection(Set *seti, const Set *set1, const Set *set2)
{
    ListElmt member;
    void *data;

    set_init(seti, seti->match, NULL);

    return 0;
}
