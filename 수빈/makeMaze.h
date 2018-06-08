#include <stdio.h>
#include <malloc.h>
#include <Windows.h>
#include <stdlib.h>
#include <time.h>

#include <stdio.h>
#include <Windows.h>
#define V 10
#define INF 99999
#define size V*V
#define MAX 90

int index1[4][2];
int escape_x, escape_y;
int top;

typedef struct stackNode {
	struct stackNode*link;
	int x;
	int y;
}stackNode;

typedef struct stack {
	stackNode* top;

}Stack;

void printSearch(int maze[10][10], Stack*s);
void init1(Stack**s);
void push1(Stack*stack, int x, int y);
void pop1(Stack*stack);
void printMaze(int**maze);
void init();
void push(int dis);
void pop();
int minDistance();
void route();
void mazeSearch();
void dijikstra();

int** routeInit();