typedef struct Node {
    int inf;
    struct Node *link;
} Node;

typedef struct Queue {
    Node *BegQ;
    Node *EndQ;
} Queue;

void init_queue(Queue *q);
void add_element(Queue *q, int inf);
int del_element(Queue *q);
int is_empty(Queue *q);
void selection_sort(Queue *q);
void read_queue(Queue *q);
void write_to_file(Queue *q, const char *filename);
void print_file_content(const char *filename);
void quick_sort(Queue *q);
void sort_queue(Queue *q, int sort_method);
