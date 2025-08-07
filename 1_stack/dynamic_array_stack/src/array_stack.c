#include "array_stack.h"
#include <stdlib.h>

#define ARRAY_SIZE 10

Stack *stack_create() {
  Stack *stack = (Stack *)malloc(sizeof(Stack));
  stack->count = 0;
  stack->capacity = ARRAY_SIZE;
  stack->array = (Node *)malloc(sizeof(Node) * ARRAY_SIZE);
  return stack;
};

void stack_push(Stack *stack, void *input) {
  if (stack->count == stack->capacity) {
    stack->array =
        realloc(stack->array, sizeof(Node) * (stack->capacity + ARRAY_SIZE));
  }

  stack->array[stack->count].data = input;
  stack->count++;
};

int stack_pop(Stack *stack, void **output) {
  if (stack->count == 0)
    return 0;

  stack->count--;
  *output = stack->array[stack->count].data;

  return 1;
};

int stack_size(Stack *stack) { return stack->count; }

int stack_empty(Stack *stack) { return stack->count == 0; }

int stack_top(Stack *stack, void **output) {
  if (stack->count == 0)
    return 0;

  *output = stack->array[stack->count - 1].data;

  return 1;
}

void stack_traverse(Stack *stack, void callback(void *arg)) {
  for (int i = 0; i < stack->count; i++) {
    callback(stack->array[stack->count - i - 1].data);
  }
}

void stack_destroy(Stack *stack) {
  free(stack->array);
  free(stack);
}