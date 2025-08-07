typedef struct node {
  void *data;
  struct node *next;
} Node;

typedef struct {
  int count;
  Node *head;
  Node *tail;
} Queue;

Queue *queue_create();

void queue_push(Queue *queue, void *input);

int queue_pop(Queue *queue, void **output);

int queue_size(Queue *queue);

int queue_empty(Queue *queue);

int queue_head(Queue *queue, void **output);

int queue_tail(Queue *queue, void **output);

void queue_traverse(Queue *queue, void callback(void *arg));

void queue_destroy(Queue *queue);