#include <stdio.h>
#include <string.h>
#include <errno.h>
#include <unistd.h>
#include <stdlib.h>
#include "event.h"
#include "events.h"
#include "queue.h"
#include "list.h"

int receive_event(Queue *events, const Event *event)
{
    Event *new_event;
    new_event = (Event *)malloc(sizeof(Event));
    if(new_event == NULL)
    {
        return -1;
    }

    memcpy(new_event, event, sizeof(Event));

    if(queue_enqueue(events, new_event) != 0)
    {
        return -1;
    }
    return 0;
}

int process_event(Queue *events, int(*dispatch)(Event *event))
{
    Event *event;
    if(queue_size(events) == 0)
    {
        return -1;
    }
    else
    {   
        if((queue_dequeue(events,(void **)&event)) != 0)
        {
            return -1;
        }
        else
        {
            dispatch(event);

        }
        free(event);
    }
    return 0;
}

