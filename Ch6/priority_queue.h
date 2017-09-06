#ifndef CW_PRIORITY_QUEUE
#define CW_PRIORITY_QUEUE

typedef struct 
{
    int heap_size;
    int length;
    int* data;
} priority_queue;

int priority_queue_maximum(priority_queue p);
int priority_queue_extract_max(priority_queue* p);
void priority_queue_increase_key(priority_queue* p, int index, int new_value);
void priority_queue_insert(priority_queue* p, int value);

#endif
