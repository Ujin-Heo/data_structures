#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "array_stack.h"

void print_stack(void *data) { printf("%s ", (char *)data); }

int main() {

  Stack *stack = stack_create();

  char task[10];
  while (1) {
    printf("\n===============================================\n");
    printf("Please enter the task to perform:\n");
    printf("push / pop / size / empty / top / print / quit\n");

    scanf("%s", task);
    if (strcmp(task, "push") == 0) {
      char buffer[101];

      scanf("%s", buffer);
      int input_size = strlen(buffer) + 1;
      char *input = (char *)malloc(sizeof(char) * input_size);
      strcpy(input, buffer);

      stack_push(stack, input);

    } else if (strcmp(task, "pop") == 0) {
      void *output;
      if (!stack_pop(stack, &output)) {
        printf("No data left to pop\n");
        continue;
      }
      printf("Popped data: %s\n", (char *)output);
      free(output);

    } else if (strcmp(task, "size") == 0) {
      printf("Size: %d\n", stack_size(stack));

    } else if (strcmp(task, "empty") == 0) {
      stack_empty(stack) ? printf("Empty\n") : printf("Not empty\n");

    } else if (strcmp(task, "top") == 0) {
      void *output;
      if (!stack_top(stack, &output)) {
        printf("No data yet\n");
        continue;
      }
      printf("Top data: %s\n", (char *)output);

    } else if (strcmp(task, "print") == 0) {
      printf("[bottom] ");
      stack_traverse(stack, print_stack);
      printf("[top]\n");

    } else if (strcmp(task, "quit") == 0) {
      break;

    } else {
      printf("Invalid task. Check your input again.\n");
    }
  }

  free(stack->array);
  free(stack);

  return 0;
}