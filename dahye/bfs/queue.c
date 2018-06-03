//
//  queue.c
//  maze_queue
//
//  Created by dahye Jeong on 2018. 5. 20..
//  Copyright © 2018년 dahye Jeong. All rights reserved.
//

#include "queue.h"

QNode * new_node(Position pos){
    QNode * new = (QNode *)malloc(sizeof(QNode));
    new->pos.x = pos.x;
    new->pos.y = pos.y;
    new->next=NULL;
    return new;
}

Queue * creat_queue(void){
    Queue * new = (Queue *)malloc(sizeof(Queue));
    new->front = new->rear= NULL;
    return new;
}


Position front(Queue *q){
    return q->front->pos;
}

Position rear(Queue *q){
    return q->rear->pos;
}

int is_empty(Queue * q){
    return (q->front==NULL && q->rear==NULL);
}

//front 포인터는 삭제,  rear 포인터는 삽입할 때 사용
void enQueue(Queue * q,Position pos){
    QNode * tmp = new_node(pos);
    
    if(is_empty(q)){
        q->front = q->rear = tmp;
        return;
    }
    q->rear->next= tmp;
    q->rear=tmp;
}

void deQueue(Queue * q){
    if(q->front==NULL){
        return;
    }
    q->front = q->front->next;
    if(q->front==NULL) q->rear=NULL;
}
