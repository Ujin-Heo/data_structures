typedef struct node {
  void *data;
  struct node *next;
} Node;

typedef struct {
  int count;
  Node *base;
} Stack;

Stack *queue_create();

void queue_push(Stack *stack, void *input);

int queue_pop(Stack *stack, void **output);

int queue_size(Stack *stack);

int queue_empty(Stack *stack);

int queue_top(Stack *stack, void **output);

void queue_traverse(Stack *stack, void callback(void *arg));

void queue_destroy(Stack *stack);