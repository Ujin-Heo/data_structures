#include "linked_list_queue.h"
#include <stdlib.h>

Queue *queue_create() {
  Queue *queue = (Queue *)malloc(sizeof(Queue));
  queue->count = 0;
  queue->head = NULL;
  queue->tail = NULL;
  return queue;
};

void queue_push(Queue *queue, void *input) {
  Node *pNew = (Node *)malloc(sizeof(Node));
  pNew->data = input;
  pNew->next = NULL;

  if (queue->count == 0) {
    queue->head = pNew;
    queue->tail = pNew;
    queue->count++;
    return;
  }

  queue->tail->next = pNew;
  queue->tail = pNew;
  queue->count++;
};

int queue_pop(Queue *queue, void **output) {
  if (queue->count == 0)
    return 0;

  *output = queue->head->data;

  if (queue->count == 1) {
    free(queue->head);
    queue->head = NULL;
    queue->tail = NULL;
    queue->count--;
    return 1;
  }

  Node *temp = queue->head;
  queue->head = queue->head->next;
  free(temp);
  queue->count--;

  return 1;
};

int queue_size(Queue *queue) { return queue->count; }

int queue_empty(Queue *queue) { return queue->count == 0; }

int queue_head(Queue *queue, void **output) {
  if (queue->count == 0)
    return 0;

  *output = queue->head->data;

  return 1;
}

int queue_tail(Queue *queue, void **output) {
  if (queue->count == 0)
    return 0;

  *output = queue->tail->data;

  return 1;
}

void queue_traverse(Queue *queue, void callback(void *arg)) {
  Node *pos = queue->head;
  while (pos) {
    callback(pos->data);
    pos = pos->next;
  }
}

void queue_destroy(Queue *queue) {
  Node *pos = queue->head, *temp = NULL;
  while (pos) {
    temp = pos;
    pos = pos->next;
    free(temp);
  }
  free(queue);
}