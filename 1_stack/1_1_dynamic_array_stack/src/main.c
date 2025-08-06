#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "array_stack.h"

int main() {

  Stack *stack = create_stack();

  char task[10];
  while (1) {
    printf("===============================================\n");
    printf("Please enter the task to perform:\n");
    printf("push / pop / size / empty / top / print / quit\n");

    scanf("%s", task);
    if (strcmp(task, "push") == 0) {
      char buffer[101];

      scanf("%s", buffer);
      int input_size = strlen(buffer) + 1;
      char *input = (char *)malloc(sizeof(char) * input_size);
      strcpy(input, buffer);

      push(stack, input);

    } else if (strcmp(task, "pop") == 0) {
      void *output;
      int success = pop(stack, &output);
      if (!success) {
        printf("no data left to pop in the stack\n");
        continue;
      }
      printf("%s\n", (char *)output);
      free(output);

    } else if (strcmp(task, "size") == 0) {
      printf("size of the stack: %d\n", stack->count);

    } else if (strcmp(task, "empty") == 0) {
      (stack->count == 0) ? printf("the stack is empty\n")
                          : printf("the stack is not empty\n");

    } else if (strcmp(task, "top") == 0) {
      if (stack->count == 0) {
        printf("there is no data in the stack yet\n");
        continue;
      }
      printf("top data: %s\n", (char *)stack->array[stack->count - 1].data);

    } else if (strcmp(task, "print") == 0) {
      printf("[bottom] ");
      for (int i = 0; i < stack->count; i++) {
        printf("%s ", (char *)stack->array[i].data);
      }
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