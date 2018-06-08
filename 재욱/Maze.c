#include <stdio.h>
#include "stack.h"
#include "position.h"
#include "queue.h"
#pragma comment(lib, "ws2_32.lib")

#define MAX 10
#define PATH 0
#define WALL 1
#define VISITED 2
#define BACKTRACKED 3

typedef enum { false, true } bool;

int maze[MAX][MAX] =
{
	{ 4,4,4,4,4,4,4,4,4,4 },
	{ 4,0,0,0,0,0,0,0,1,4 },
	{ 4,0,1,1,0,1,1,0,1,4 },
	{ 4,0,0,0,1,0,0,0,1,4 },
	{ 4,0,1,0,0,1,1,0,0,4 },
	{ 4,0,1,1,1,0,0,1,1,4 },
	{ 4,0,1,0,0,0,1,0,1,4 },
	{ 4,0,0,0,1,0,0,0,1,4 },
	{ 4,0,1,1,1,0,1,0,0,4 },
	{ 4,4,4,4,4,4,4,4,4,4 }
};

void print_maze(int x, int y) {

	for (int i = 0; i < MAX ; i++) {
		for (int j = 0; j < MAX ; j++) {
			switch (maze[i][j]) {
			case 0:
				printf("□");
				break;
			case 1:
				printf("■");
				break;
			case 2:
				printf("◈");
				break;
			case 3:
				printf("◆");
				break;
			case 4:
				printf("＊");
				break;
		
			}
		}
		printf("\n");
	}
}
bool movable (Position pos, int dir) {	// (0,0) , 0 1 2 3
	Position tmp = move_to(pos, dir);		// tmp = next
	
	print_maze(tmp.x, tmp.y);
	printf("maze[%d][%d]=%d\n", tmp.x, tmp.y, maze[tmp.x][tmp.y]);		

	if (tmp.x<1 || tmp.x>MAX-2) {
		printf("out of range\n");
		return false;
	}
	if (tmp.y<1 || tmp.y>MAX-2) {
		printf("out of range\n");
		return false;
	}
	switch (maze[tmp.x][tmp.y]) {
	case 0:
		printf("It is a way to go.\n");
		return true;
	case 1:
		printf("No path exists.\n");
		return false;
	case 2:
		printf("It has already been visited.\n");
		return false;
	case 4:
		printf("Bounds\n");
		return false;
	}
}

void final_path(Position pos) {

	Position cur = pos;
	Position next;

	int offset[4][2] = {
		{ -1,0 },{ 0,1 },{ 1,0 },{ 0,-1 }
	};
	int num = maze[cur.x][cur.y] + 1;

	
	while (1) {
		for (int i = 0;i<4;i++) {
			next.x = cur.x + offset[i][0];
			next.y = cur.y + offset[i][1];
			if (maze[next.x][next.y] == num) {
				
				cur = next;
				num++;
				break;
			}
		}
		if (cur.x == 1 && cur.y == 1)break;
	}
	
}

void stack_dfs() {

	Position cur;
	cur.x = 1;
	cur.y = 1;
	Stack *s = new_stack_node(cur);
	int dir;
	int x, y;
	bool forwarded;


	printf("Start searching for the maze\n");

	while (!is_empty_stack(s)) {
		maze[cur.x][cur.y] = VISITED;		// cur.x,y 값이 이상함
		x = cur.x;
		y = cur.y;
		if (maze[cur.x][cur.y] == maze[MAX][MAX]) {
			printf("Find the path!\n");
			break;
		}

		forwarded = false;
		for (dir = 0; dir < 4; dir++) {
			cur = move_to(cur, dir);
			if (!movable)
				break;
			if (movable(cur, dir)) {
				push(s, cur);
				forwarded = true;
				break;
			}
			
		}

		if (!forwarded) {
			maze[cur.x][cur.y] = BACKTRACKED;
			if (is_empty_stack(s)) {
				printf("No path exists\n");
				break;
			}
			pop(s);
			cur = peek(s);
		}
		
	}

}

void queue_bfs() {

	Queue *q = creat_queue();

	Position cur;
	cur.x = 1;
	cur.y = 1;

	enQueue(q, cur);

	maze[1][1] = -1;
	int found = 0;

	printf("Start searching for the maze\n");

	while (!is_empty_queue(q)) {
		Position cur = front(q);
		deQueue(q);
		for (int dir = 0;dir<4;dir++) {

			if (movable(cur, dir)) {
				Position pos = move_to(cur, dir);
				maze[pos.x][pos.y] = maze[cur.x][cur.y] - 1;

				if (pos.x == MAX-2 && pos.y == MAX-2) {
					printf("Find the path!\n");
					final_path(pos);
					found = 1;
					exit(0);
				}
				enQueue(q, pos);
			}
		}
	}

	return ;
}


void main() {
	stack_dfs();
	//queue_bfs();
}