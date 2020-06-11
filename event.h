#ifndef EVENT_H
#define ENENT_H

#include <stdio.h>
#include "list.h"
#include "queue.h"
#include "events.h"

typedef ListElmt Event;

int receive_event(Queue *events, const Event *event);
int process_event(Queue *events, int (dispatch)(Event *event));

#endif
