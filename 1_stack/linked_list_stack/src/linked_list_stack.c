#include "linked_list_stack.h"
#include <stdlib.h>

Stack *stack_create() {
  Stack *stack = (Stack *)malloc(sizeof(Stack));
  stack->count = 0;
  stack->base = NULL;
  return stack;
};

void stack_push(Stack *stack, void *input) {
  Node *pNew = (Node *)malloc(sizeof(Node));
  pNew->data = input;
  pNew->next = stack->base;

  stack->base = pNew;
  stack->count++;
};

int stack_pop(Stack *stack, void **output) {
  if (stack->count == 0)
    return 0;

  *output = stack->base->data;

  Node *temp = stack->base;
  stack->base = stack->base->next;
  free(temp);
  stack->count--;

  return 1;
};

int stack_size(Stack *stack) { return stack->count; }

int stack_empty(Stack *stack) { return stack->count == 0; }

int stack_top(Stack *stack, void **output) {
  if (stack->count == 0)
    return 0;

  *output = stack->base->data;

  return 1;
}

void stack_traverse(Stack *stack, void callback(void *arg)) {
  Node *pos = stack->base;
  while (pos) {
    callback(pos->data);
    pos = pos->next;
  }
}

void stack_destroy(Stack *stack) {
  Node *pos = stack->base, *temp = NULL;
  while (pos) {
    temp = pos;
    pos = pos->next;
    free(temp);
  }
  free(stack);
}