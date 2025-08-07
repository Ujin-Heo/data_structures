#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "linked_list_queue.h"

void print_data(void *data) { printf("%s ", (char *)data); }

int main() {

  Queue *stack = queue_create();

  char task[10];
  while (1) {
    printf("\n===============================================\n");
    printf("Please enter the task to perform:\n");
    printf("push / pop / size / empty / head / tail / print / quit\n");

    scanf("%s", task);
    if (strcmp(task, "push") == 0) {
      char buffer[101];

      scanf("%s", buffer);
      int input_size = strlen(buffer) + 1;
      char *input = (char *)malloc(sizeof(char) * input_size);
      strcpy(input, buffer);

      queue_push(stack, input);

    } else if (strcmp(task, "pop") == 0) {
      void *output;
      if (!queue_pop(stack, &output)) {
        printf("No data left to pop\n");
        continue;
      }
      printf("Popped data: %s\n", (char *)output);
      free(output);

    } else if (strcmp(task, "size") == 0) {
      printf("Size: %d\n", queue_size(stack));

    } else if (strcmp(task, "empty") == 0) {
      queue_empty(stack) ? printf("Empty\n") : printf("Not empty\n");

    } else if (strcmp(task, "head") == 0) {
      void *output;
      if (!queue_head(stack, &output)) {
        printf("No data yet\n");
        continue;
      }
      printf("Head data: %s\n", (char *)output);

    } else if (strcmp(task, "tail") == 0) {
      void *output;
      if (!queue_tail(stack, &output)) {
        printf("No data yet\n");
        continue;
      }
      printf("Tail data: %s\n", (char *)output);

    } else if (strcmp(task, "print") == 0) {
      printf("[head] ");
      queue_traverse(stack, print_data);
      printf("[tail]\n");

    } else if (strcmp(task, "quit") == 0) {
      break;

    } else {
      printf("Invalid task. Check your input again.\n");
    }
  }

  queue_destroy(stack);

  return 0;
}