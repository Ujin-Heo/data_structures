#include "linked_list_queue.h"
#include <stdlib.h>

int queue_size(Queue *queue) { return queue->count; }

int queue_empty(Queue *queue) { return queue->count == 0; }
