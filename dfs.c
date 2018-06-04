#include "makeMaze.h"

int index1[4][2] = { { -1,0 },{ 0,-1 },{ 0,1 },{ 1,0 } };

void init1(Stack**s) {
	(*s) = (Stack*)malloc(sizeof(Stack));
	(*s)->top = NULL;
}

void push1(Stack*Stack, int x, int y) {
	stackNode* newNode = (stackNode*)malloc(sizeof(stackNode));
	newNode->x = x;
	newNode->y = y;
	newNode->link = NULL;
	if (Stack->top == NULL) {
		Stack->top = newNode;
		return;
	}
	newNode->link = Stack->top;
	Stack->top = newNode;
}

void pop1(Stack*Stack) {
	if (Stack->top) {
		Stack->top = Stack->top->link;
	}
}

void printMaze(int maze[10][10]) {
	int i, j;
	for (i = 0; i < V; i++) {
		for (j = 0; j < V; j++) {
			if (maze[i][j] == 1) printf("0");
			else if (maze[i][j] == 0) printf("1");
			else printf("S");
		}
		printf("\n");
	}
}

void printSearch(int maze[10][10], Stack*s) {
	system("cls");
	int i, j;
	for (i = 0; i < V; i++) {
		for (j = 0; j < V; j++) {
			if (i == s->top->x&&j == s->top->y) printf("◎");
			else if (maze[i][j] == 0) printf("□");
			else if (maze[i][j] == 1) printf("■");
			else printf("X");
		}
		printf("\n");
	}
}


void search(int maze[][10],int**route, Stack*s) {
	while (s->top != NULL) {
		pop(s);
	}
	int x, y;
	int a, b;
	int flag;
	int i, j;
	push1(s, 0, 0);
	route[s->top->x][s->top->y] = 2;
	//1,0이 시작
	while (1) {
		for (i = 0; i < 4; i++) {

			x = s->top->x;
			y = s->top->y;
			flag = 0;
			a = index1[i][0];
			b = index1[i][1];
			if (x + a<0 || y + b<0 || x + a>size - 1 || y + b>size - 1) continue;
			if (maze[x + a][y + b] == 1 && route[x + a][y + b] == 0) {
				//0이 통로 통로이면 push
				push1(s, x + a, y + b);
				route[x + a][y + b] = 1;
				flag = 1;
				if (x+a==V-1&&y+b==V-1) {
					Sleep(500);
					printSearch(maze, s, size);
					printf("미로끝 \n");
					return;
				}
				break;
			}
		}

		if (flag == 0) {
			//통로가 하나도 없으면 pop해서 뒤로 돌아감
			route[s->top->x][s->top->y] = 2;
			pop1(s);

		}

		Sleep(300);
		printSearch(maze, s, V);

	}
}

int** routeInit() {
	int**route;
	int i,j;
	route = (int**)malloc(sizeof(int*)*V);
	for (i = 0; i < V; i++) {
		route[i] = (int*)malloc(sizeof(int)*V);
		for (j = 0; j < V; j++) {
			route[i][j] = 0;
		}
	}
	return route;
}