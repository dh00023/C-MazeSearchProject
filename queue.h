#include <stdio.h>
#include <stdlib.h>
#include "position.h"
#pragma comment(lib, "ws2_32.lib")



typedef struct node {
	Position pos;
	struct node * next;
}QNode;

typedef struct queue {
	QNode *front, *rear;
}Queue;

void enQueue(Queue * q, Position pos);
void deQueue(Queue * q);
int is_empty_queue(Queue * q);
Position front(Queue *queue);
Position rear(Queue *queue);
QNode * new_queue_node(Position pos);
Queue * creat_queue(void);
