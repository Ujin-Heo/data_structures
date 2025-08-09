#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "linked_list_deque.h"

void print_data(void *data) { printf("%s ", (char *)data); }

char *get_input() {
  char buffer[101];
  if (!scanf("%s", buffer)) {
    fprintf(stderr, "error reading input value.");
  }

  int input_size = strlen(buffer) + 1;
  char *input = (char *)malloc(sizeof(char) * input_size);
  strcpy(input, buffer);
  return input;
}

int main() {

  Deque *deque = deque_create();

  char task[50];
  while (1) {
    printf("\n===============================================\n");
    printf("Please enter the task to perform:\n");
    printf("push_front / push_back / pop_front / pop_back / size / empty / "
           "head / tail / print / quit\n");

    if (!scanf("%s", task)) {
      fprintf(stderr, "error reading task. try again.");
      continue;
    };

    if (strcmp(task, "push_front") == 0) {
      char *input = get_input();
      deque_push_front(deque, input);

    } else if (strcmp(task, "push_back") == 0) {
      char *input = get_input();
      deque_push_back(deque, input);

    } else if (strcmp(task, "pop_front") == 0) {
      void *output;
      if (!deque_pop_front(deque, &output)) {
        printf("No data left to pop\n");
        continue;
      }
      printf("Popped data: %s\n", (char *)output);
      free(output);

    } else if (strcmp(task, "pop_back") == 0) {
      void *output;
      if (!deque_pop_back(deque, &output)) {
        printf("No data left to pop\n");
        continue;
      }
      printf("Popped data: %s\n", (char *)output);
      free(output);

    } else if (strcmp(task, "size") == 0) {
      printf("Size: %d\n", deque_size(deque));

    } else if (strcmp(task, "empty") == 0) {
      deque_empty(deque) ? printf("Empty\n") : printf("Not empty\n");

    } else if (strcmp(task, "head") == 0) {
      void *output;
      if (!deque_head(deque, &output)) {
        printf("No data yet\n");
        continue;
      }
      printf("Head data: %s\n", (char *)output);

    } else if (strcmp(task, "tail") == 0) {
      void *output;
      if (!deque_tail(deque, &output)) {
        printf("No data yet\n");
        continue;
      }
      printf("Tail data: %s\n", (char *)output);

    } else if (strcmp(task, "print") == 0) {
      printf("[head] ");
      deque_traverse(deque, print_data);
      printf("[tail]\n");

    } else if (strcmp(task, "quit") == 0) {
      break;

    } else {
      printf("Invalid task. Check your input again.\n");
    }
  }

  deque_destroy(deque);

  return 0;
}