//
//  queue.h
//  maze_queue
//
//  Created by dahye Jeong on 2018. 5. 20..
//  Copyright © 2018년 dahye Jeong. All rights reserved.
//

#ifndef queue_h
#define queue_h

#include <stdio.h>
#include <stdlib.h>
#include "position.h"

typedef struct node{
    Position pos;
    struct node * next;
}QNode;

typedef struct que{
    QNode *front, *rear;
}Queue;

void enQueue(Queue * q,Position pos);
void deQueue(Queue * q);
Position front(Queue *queue);
Position rear(Queue *queue);
int is_empty(Queue *queue);
QNode * new_node(Position pos);
Queue * creat_queue(void);

#endif /* queue_h */
