#include "doubly_linked_list_deque.h"
#include <stdlib.h>

static Node *_create_node(void *input);

///////////////////////////////////////////////////////////////
Deque *deque_create() {
  Deque *deque = (Deque *)malloc(sizeof(Deque));
  deque->count = 0;
  deque->head = NULL;
  deque->tail = NULL;
  return deque;
}

void deque_push_front(Deque *deque, void *input) {
  Node *pNew = _create_node(input);

  if (deque->count == 0) {
    deque->head = pNew;
    deque->tail = pNew;
    deque->count++;
    return;
  }

  pNew->next = deque->head;
  deque->head->prev = pNew;

  deque->head = pNew;

  deque->count++;
  return;
}

void deque_push_back(Deque *deque, void *input) {
  Node *pNew = _create_node(input);

  if (deque->count == 0) {
    deque->head = pNew;
    deque->tail = pNew;
    deque->count++;
    return;
  }

  pNew->prev = deque->tail;
  deque->tail->next = pNew;

  deque->tail = pNew;

  deque->count++;
  return;
}

int deque_pop_front(Deque *deque, void **output) {
  if (deque->count == 0)
    return 0;

  *output = deque->head->data;

  if (deque->count == 1) {
    Node *temp = deque->head;
    deque->head = NULL;
    deque->tail = NULL;
    free(temp);

    deque->count--;
    return 1;
  }

  Node *temp = deque->head;
  deque->head = deque->head->next;
  deque->head->prev = NULL;
  free(temp);

  deque->count--;
  return 1;
}

int deque_pop_back(Deque *deque, void **output) {
  if (deque->count == 0)
    return 0;

  *output = deque->tail->data;

  if (deque->count == 1) {
    Node *temp = deque->tail;
    deque->tail = NULL;
    deque->head = NULL;
    free(temp);

    deque->count--;
    return 1;
  }

  Node *temp = deque->tail;
  deque->tail = deque->tail->prev;
  deque->tail->next = NULL;
  free(temp);

  deque->count--;
  return 1;
}

int deque_size(Deque *deque) { return deque->count; }

int deque_empty(Deque *deque) { return deque->count == 0; }

int deque_head(Deque *deque, void **output) {
  if (deque->count == 0) {
    return 0;
  }

  *output = deque->head->data;
  return 1;
}

int deque_tail(Deque *deque, void **output) {
  if (deque->count == 0) {
    return 0;
  }

  *output = deque->tail->data;
  return 1;
}

void deque_traverse(Deque *deque, void callback(void *arg)) {
  Node *pos = deque->head;
  while (pos) {
    callback(pos->data);
    pos = pos->next;
  }
}

void deque_traverse_reverse(Deque *deque, void callback(void *arg)) {
  Node *pos = deque->tail;
  while (pos) {
    callback(pos->data);
    pos = pos->prev;
  }
}

void deque_destroy(Deque *deque) { free(deque); }

/////////////////////////////////////////////////////////////////
static Node *_create_node(void *input) {
  Node *pNew = (Node *)malloc(sizeof(Node));
  pNew->data = input;
  pNew->prev = NULL;
  pNew->next = NULL;
  return pNew;
}
