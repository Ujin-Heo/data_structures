#include "linked_list_stack.h"
#include <stdlib.h>

Stack *queue_create() {
  Stack *stack = (Stack *)malloc(sizeof(Stack));
  stack->count = 0;
  stack->base = NULL;
  return stack;
};

void queue_push(Stack *stack, void *input) {
  Node *pNew = (Node *)malloc(sizeof(Node));
  pNew->data = input;
  pNew->next = stack->base;

  stack->base = pNew;
  stack->count++;
};

int queue_pop(Stack *stack, void **output) {
  if (stack->count == 0)
    return 0;

  *output = stack->base->data;

  Node *temp = stack->base;
  stack->base = stack->base->next;
  free(temp);
  stack->count--;

  return 1;
};

int queue_size(Stack *stack) { return stack->count; }

int queue_empty(Stack *stack) { return stack->count == 0; }

int queue_top(Stack *stack, void **output) {
  if (stack->count == 0)
    return 0;

  *output = stack->base->data;

  return 1;
}

void queue_traverse(Stack *stack, void callback(void *arg)) {
  Node *pos = stack->base;
  while (pos) {
    callback(pos->data);
    pos = pos->next;
  }
}

void queue_destroy(Stack *stack) {
  Node *pos = stack->base, *temp = NULL;
  while (pos) {
    temp = pos;
    pos = pos->next;
    free(temp);
  }
  free(stack);
}