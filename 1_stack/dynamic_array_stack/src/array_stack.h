typedef struct {
  void *data;
} Node;

typedef struct {
  int count;
  int capacity;
  Node *array;
} Stack;

Stack *stack_create();

void stack_push(Stack *stack, void *input);

int stack_pop(Stack *stack, void **output);

int stack_size(Stack *stack);

int stack_empty(Stack *stack);

int stack_top(Stack *stack, void **output);

void stack_traverse(Stack *stack, void callback(void *arg));

void stack_destroy(Stack *stack);