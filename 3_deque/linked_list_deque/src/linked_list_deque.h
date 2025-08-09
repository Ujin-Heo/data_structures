typedef struct node {
  void *data;
  struct node *next;
} Node;

typedef struct {
  int count;
  Node *head;
  Node *tail;
} Deque;

Deque *deque_create();

void deque_push_front(Deque *deque, void *input);

void deque_push_back(Deque *deque, void *input);

int deque_pop_front(Deque *deque, void **output);

int deque_pop_back(Deque *deque, void **output);

int deque_size(Deque *deque);

int deque_empty(Deque *deque);

int deque_head(Deque *deque, void **output);

int deque_tail(Deque *deque, void **output);

void deque_traverse(Deque *deque, void callback(void *arg));

void deque_destroy(Deque *deque);