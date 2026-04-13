#include <stdio.h>
#include <stdbool.h>

#define MAX_PEOPLE 50

typedef struct {
    int id;
} People;

typedef struct {
    People data[MAX_PEOPLE];
    int head;   // 队头：出队位置
    int tail;   // 队尾：入队位置
    int count;  // 当前元素个数
} Queue;

void queue_init(Queue *q) {
    q->head = 0;
    q->tail = 0;
    q->count = 0;
}

void queue_push(Queue *q, People p) {
    q->data[q->tail] = p;
    q->tail = (q->tail + 1) % MAX_PEOPLE;
    q->count++;
}

People queue_pop(Queue *q) {
    People p = q->data[q->head];
    q->head = (q->head + 1) % MAX_PEOPLE;
    q->count--;
    return p;
}

int main() {
    Queue q;
    int total_people = 50;
    int report_interval = 5;

    queue_init(&q);

    for(int i = 1; i <= total_people; i ++){
        queue_push(&q, (People){i});
    }

    int count = 1;
    while(q.count > 1){
        People p = queue_pop(&q);
        if(count == report_interval){
            printf("淘汰: %d\n", p.id);
            count = 1;
        }else {
            queue_push(&q, p);
            count++;
        }
    }
    People last = queue_pop(&q);
    printf("最后剩下的人是: %d\n", last.id);

    return 0;
}