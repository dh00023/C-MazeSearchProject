//
//  main_h.h
//  astar
//
//  Created by dahye Jeong on 2018. 5. 29..
//  Copyright © 2018년 dahye Jeong. All rights reserved.
//

#ifndef main_h_h
#define main_h_h

#include <math.h>
#include <stdio.h>
#include <stdlib.h>

#define MAX 10
#define PATH 0              // 지나갈 수 있는 길
#define WALL 1              // 지나갈 수 없는 길 == 벽 흰색!
#define CLOSED 2
#define FINAL 3
#define EDGE 4              // 테두리

typedef struct vertex{
    int x,y;
    int g_x;
}Vertex;

typedef struct node{
    Vertex ver;
    struct node * next;
}QNode;

typedef struct que{
    QNode *front, *rear;
}Queue;

void enQueue(Queue * q,Vertex v);
void deQueue(Queue * q);
Vertex front(Queue *queue);
Vertex rear(Queue *queue);
int is_empty(Queue *queue);
QNode * new_node(Vertex v);
Queue * creat_queue(void);

void print_maze(int x, int y);
void print_weight();
int weight[MAX+2][MAX+2];
int parent[MAX+2][MAX+2];


#endif /* main_h_h */
