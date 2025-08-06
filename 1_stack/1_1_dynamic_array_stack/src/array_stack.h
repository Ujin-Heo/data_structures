typedef struct {
  void *data;
} Node;

typedef struct {
  int count;
  int capacity;
  Node *array;
} Stack;

Stack *create_stack();

void push(Stack *stack, void *input);

int pop(Stack *stack, void **output);